#include <qsinterpreter.h>
#include <qsproject.h>
#include <qsscript.h>

#include <QtTest/QtTest>

class Recorder : public QObject
{
    Q_OBJECT
public slots:
    void hit() { ++hits; }

public:
    int hits = 0;
};

class tst_Project : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void createScripts();
    void scriptsAreEvaluated();
    void scriptWithContext();
    void addFunction();
    void addAndSetCode();
    void objects();
    void signalHandler();
    void bundleRoundTrip();
    void textFilesRoundTrip();
    void destroyedObjectsAreForgotten();
    void destroyedContextOfScript();
    void codeChangesAreReported();
    void modifiedState();

private:
    QSProject *project = nullptr;
};

void tst_Project::init()
{
    project = new QSProject;
    project->interpreter()->setErrorMode(QSInterpreter::Nothing);
}

void tst_Project::cleanup()
{
    delete project;
    project = nullptr;
}

void tst_Project::createScripts()
{
    QVERIFY(project->scriptNames().isEmpty());
    QSScript *main = project->createScript("main.qs", "var a = 1;");
    QVERIFY(main);
    QCOMPARE(main->name(), QString("main.qs"));
    QCOMPARE(main->code(), QString("var a = 1;"));
    QCOMPARE(project->script("main.qs"), main);
    QVERIFY(project->scriptNames().contains("main.qs"));
    QCOMPARE(project->scripts().size(), 1);
    QVERIFY(!project->script("other.qs"));
}

void tst_Project::scriptsAreEvaluated()
{
    project->createScript("lib.qs", "function twice(n) { return n * 2; }");
    project->createScript("vars.qs", "var base = 20;");
    QSInterpreter *ip = project->interpreter();
    QCOMPARE(ip->evaluate("twice(base) + 2").toInt(), 42);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Project::scriptWithContext()
{
    QObject context;
    context.setObjectName("owner");
    QSScript *script = project->createScript(&context, "var own = 'mine'; function who() { return own; }");
    QVERIFY(script);
    QCOMPARE(script->context(), &context);
    QCOMPARE(project->script(&context), script);
    QCOMPARE(project->interpreter()->call("who", QVariantList(), &context).toString(), QString("mine"));
}

void tst_Project::addFunction()
{
    QSScript *script = project->createScript("funcs.qs");
    QVERIFY(script->addFunction("answer", "return 42;"));
    QCOMPARE(project->interpreter()->call("answer").toInt(), 42);
}

void tst_Project::addAndSetCode()
{
    QSScript *script = project->createScript("code.qs", "var x = 1;");
    QSignalSpy spy(script, SIGNAL(codeChanged()));
    script->addCode("var y = 2;");
    QVERIFY(script->code().contains("var x = 1;"));
    QVERIFY(script->code().contains("var y = 2;"));
    script->setCode("var z = 3;");
    QCOMPARE(script->code(), QString("var z = 3;"));
    QVERIFY(spy.count() >= 2);
    QCOMPARE(script->project(), project);
}

void tst_Project::objects()
{
    QObject first;
    first.setObjectName("first");
    project->addObject(&first);
    QVERIFY(project->objects().contains(&first));
    QCOMPARE(project->object("first"), &first);
    QCOMPARE(project->interpreter()->evaluate("first.objectName").toString(), QString("first"));

    project->removeObject(&first);
    QVERIFY(!project->objects().contains(&first));
    project->addObject(&first);
    project->clearObjects();
    QVERIFY(project->objects().isEmpty());
}

void tst_Project::signalHandler()
{
    QObject sender;
    sender.setObjectName("sender");
    Recorder recorder;
    recorder.setObjectName("recorder");
    project->addObject(&sender);
    project->addObject(&recorder);
    project->createScript("handler.qs", "function onRenamed() { recorder.hit(); }");
    project->addSignalHandler(&sender, SIGNAL(objectNameChanged(QString)), "onRenamed");
    sender.setObjectName("renamed");
    QCOMPARE(recorder.hits, 1);
    project->removeSignalHandler(&sender, SIGNAL(objectNameChanged(QString)), "onRenamed");
    sender.setObjectName("again");
    QCOMPARE(recorder.hits, 1);
}

void tst_Project::bundleRoundTrip()
{
    project->setStorageMode(QSProject::Bundle);
    QCOMPARE(project->storageMode(), QSProject::Bundle);
    project->createScript("one.qs", "function one() { return 1; }");
    project->createScript("two.qs", QString::fromUtf8("var text = '\xc3\xa4\xc3\xb6\xc3\xbc';"));

    QByteArray data;
    QVERIFY(project->saveToData(&data));
    QVERIFY(!data.isEmpty());

    QSProject other;
    other.interpreter()->setErrorMode(QSInterpreter::Nothing);
    QVERIFY(other.loadFromData(&data));
    QCOMPARE(other.scriptNames().size(), 2);
    QCOMPARE(other.script("one.qs")->code(), QString("function one() { return 1; }"));
    QCOMPARE(other.script("two.qs")->code(), QString::fromUtf8("var text = '\xc3\xa4\xc3\xb6\xc3\xbc';"));
    QCOMPARE(other.interpreter()->evaluate("one() + text.length").toInt(), 4);
}

void tst_Project::textFilesRoundTrip()
{
    // the scripts are written next to the working directory, not next to the project file
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString previous = QDir::currentPath();
    QVERIFY(QDir::setCurrent(dir.path()));
    const QString file = dir.filePath("project.qsa");

    project->setStorageMode(QSProject::TextFiles);
    project->createScript("main.qs", "function main() { return 'saved'; }");
    QVERIFY(project->save(file));
    QVERIFY(QFileInfo::exists(file));
    QVERIFY(QFileInfo::exists(dir.filePath("main.qs")));

    QSProject other;
    other.interpreter()->setErrorMode(QSInterpreter::Nothing);
    QVERIFY(other.load(file));
    QCOMPARE(other.storageMode(), QSProject::TextFiles);
    QVERIFY(other.script("main.qs"));
    QCOMPARE(other.interpreter()->call("main").toString(), QString("saved"));
    QVERIFY(!other.load(dir.filePath("does_not_exist.qsa")));

    QVERIFY(QDir::setCurrent(previous));
}

void tst_Project::destroyedObjectsAreForgotten()
{
    // the project watches the destroyed() signal of its objects
    QObject *object = new QObject;
    object->setObjectName("temporary");
    project->addObject(object);
    QVERIFY(project->objects().contains(object));
    delete object;
    QVERIFY(project->objects().isEmpty());

    // and of the sender of a signal handler
    QObject *sender = new QObject;
    sender->setObjectName("sender");
    project->addObject(sender);
    project->createScript("handler.qs", "function onRenamed() { }");
    project->addSignalHandler(sender, SIGNAL(objectNameChanged(QString)), "onRenamed");
    delete sender;
    QVERIFY(project->objects().isEmpty());
    QCOMPARE(project->interpreter()->evaluate("1 + 1").toInt(), 2);
}

void tst_Project::destroyedContextOfScript()
{
    QObject *context = new QObject;
    context->setObjectName("owner");
    QSScript *script = project->createScript(context, "var own = 1;");
    QVERIFY(script);
    QVERIFY(project->script("owner"));
    delete context;
    // the script does not keep a dangling context
    QVERIFY(!project->script("owner") || !project->script("owner")->context());
    QCOMPARE(project->interpreter()->evaluate("2 + 2").toInt(), 4);
}

void tst_Project::codeChangesAreReported()
{
    QSScript *script = project->createScript("signals.qs", "var a;");
    QSignalSpy changed(project, SIGNAL(projectChanged()));
    script->setCode("var b;");
    QVERIFY(changed.count() >= 1);
    QVERIFY(project->scriptsModified());
}

void tst_Project::modifiedState()
{
    QSScript *script = project->createScript("m.qs", "var a;");
    script->setCode("var b;");
    QVERIFY(project->scriptsModified());
}

QTEST_MAIN(tst_Project)

#include "tst_project.moc"
