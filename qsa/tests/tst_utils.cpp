#include <qsinterpreter.h>
#include <qsutilfactory.h>

#include <QtTest/QtTest>

class tst_Utils : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void fileStatics();
    void fileWriteAndRead();
    void fileLines();
    void fileBytes();
    void fileProperties();
    void fileOpenFlags();
    void dirExistsAndMkdir();
    void fileRemove();
    void dirCreateAndList();
    void dirRename();
    void dirStatics();
    void processExecute();
    void processOutput();
    void processInstance();
    void processStartFailure();
    void processSignalsExist();
    void disabledUtilities();
    void invalidClassName();

private:
    // slots return their bool results to scripts as numbers
    bool truth(const QString &code) { return ip->evaluate(code).toBool(); }
    QString eval(const QString &code) { return ip->evaluate(code).toString(); }
    QString path(const QString &name) const { return dir->filePath(name); }
    // script string literal of a native path
    QString quoted(const QString &name) const { return "'" + path(name) + "'"; }

    QSInterpreter *ip = nullptr;
    QTemporaryDir *dir = nullptr;
};

void tst_Utils::init()
{
    dir = new QTemporaryDir;
    QVERIFY(dir->isValid());
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
    ip->addObjectFactory(new QSUtilFactory);
}

void tst_Utils::cleanup()
{
    delete ip;
    delete dir;
    ip = nullptr;
    dir = nullptr;
}

void tst_Utils::fileStatics()
{
    const QString file = quoted("static.txt");
    QVERIFY(!truth("File.exists(" + file + ")"));
    eval("File.write(" + file + ", 'content')");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QVERIFY(truth("File.exists(" + file + ")"));
    QVERIFY(truth("File.isFile(" + file + ")"));
    QVERIFY(!truth("File.isDir(" + file + ")"));
    QCOMPARE(eval("File.read(" + file + ")"), QString("content"));
    QVERIFY(truth("File.isDir('" + dir->path() + "')"));
    eval("File.remove(" + file + ")");
    QVERIFY(!truth("File.exists(" + file + ")"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::fileWriteAndRead()
{
    const QString file = quoted("rw.txt");
    eval("var f = new File(" + file + "); f.open(File.WriteOnly); f.write('hello '); f.write('world'); f.close();");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));

    QFile check(path("rw.txt"));
    QVERIFY(check.open(QIODevice::ReadOnly));
    QCOMPARE(check.readAll(), QByteArray("hello world"));
    check.close();

    QCOMPARE(eval("var r = new File(" + file + "); r.open(File.ReadOnly); var text = r.read(); r.close(); text"),
             QString("hello world"));
    eval("var a = new File(" + file + "); a.open(File.Append); a.write('!'); a.close();");
    QCOMPARE(eval("File.read(" + file + ")"), QString("hello world!"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::fileLines()
{
    const QString file = quoted("lines.txt");
    eval("var f = new File(" + file + "); f.open(File.WriteOnly); f.writeLine('one'); f.writeLine('two'); f.writeLine('three'); f.close();");
    QCOMPARE(eval("var r = new File(" + file + "); r.open(File.ReadOnly); var l = r.readLines(); r.close(); l[1]"), QString("two"));
    QCOMPARE(eval("var r2 = new File(" + file + "); r2.open(File.ReadOnly); var first = r2.readLine(); r2.close(); first"),
             QString("one\n"));
    QCOMPARE(eval("var r3 = new File(" + file + "); r3.open(File.ReadOnly); var all = r3.readLines(); r3.close(); all[2]"),
                 QString("three"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::fileBytes()
{
    const QString file = quoted("bytes.bin");
    eval("var f = new File(" + file + "); f.open(File.WriteOnly); f.writeByte(65); f.writeByte(66); f.close();");
    QCOMPARE(eval("var r = new File(" + file + "); r.open(File.ReadOnly); var b = r.readByte() * 1000 + r.readByte(); r.close(); b"),
             QString("65066"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::fileProperties()
{
    QFile out(path("props.txt"));
    QVERIFY(out.open(QIODevice::WriteOnly));
    out.write("12345");
    out.close();

    const QString file = quoted("props.txt");
    QCOMPARE(eval("new File(" + file + ").name"), QString("props.txt"));
    QCOMPARE(eval("new File(" + file + ").baseName"), QString("props"));
    QCOMPARE(eval("new File(" + file + ").extension"), QString("txt"));
    QCOMPARE(eval("new File(" + file + ").size"), QString("5"));
    QCOMPARE(eval("new File(" + file + ").exists"), QString("true"));
    QCOMPARE(eval("new File(" + file + ").readable"), QString("true"));
    QCOMPARE(eval("new File(" + quoted("absent.txt") + ").exists"), QString("false"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::fileOpenFlags()
{
    const QString file = quoted("flags.txt");
    eval("var f = new File(" + file + "); f.open(File.WriteOnly | File.Translate); f.writeLine('text'); f.close();");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("File.read(" + file + ")").trimmed(), QString("text"));
    eval("var g = new File(" + file + "); g.open(File.ReadWrite); var content = g.read(); g.close();");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("content").trimmed(), QString("text"));
    QCOMPARE(eval("File.WriteOnly | File.Translate"), QString::number(int(QIODevice::WriteOnly | QIODevice::Text)));
}

void tst_Utils::dirExistsAndMkdir()
{
    eval("var d = new Dir(" + quoted("created") + "); var before = d.exists; if (!d.exists) d.mkdir(); var after = d.exists;");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("before"), QString("false"));
    QCOMPARE(eval("after"), QString("true"));
    QVERIFY(QFileInfo(path("created")).isDir());
}

void tst_Utils::fileRemove()
{
    QFile out(path("gone.txt"));
    QVERIFY(out.open(QIODevice::WriteOnly));
    out.close();
    eval("new File(" + quoted("gone.txt") + ").remove()");
    QVERIFY(!QFileInfo::exists(path("gone.txt")));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::dirCreateAndList()
{
    const QString base = quoted("tree");
    eval("var d = new Dir(" + quoted("") + "); d.mkdirs('tree/a/b');");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QVERIFY(QFileInfo(path("tree/a/b")).isDir());

    QFile one(path("tree/one.txt")), two(path("tree/two.log"));
    QVERIFY(one.open(QIODevice::WriteOnly));
    QVERIFY(two.open(QIODevice::WriteOnly));
    one.close();
    two.close();

    QCOMPARE(eval("var t = new Dir(" + base + "); t.exists"), QString("true"));
    QCOMPARE(eval("t.entryList('*.txt').join(',')"), QString("one.txt"));
    QCOMPARE(eval("t.entryList('*', Dir.Files, Dir.Name).join(',')"), QString("one.txt,two.log"));
    QCOMPARE(eval("t.entryList('*', Dir.Dirs, Dir.Name).join(',')").contains("a"), true);
    QVERIFY(truth("t.fileExists('one.txt')"));
    QVERIFY(!truth("t.fileExists('three.txt')"));
    QCOMPARE(eval("t.name"), QString("tree"));

    eval("t.remove('one.txt')");
    QVERIFY(!QFileInfo::exists(path("tree/one.txt")));
    eval("var leaf = new Dir(" + quoted("tree/a") + "); leaf.rmdirs('b');");
    QVERIFY(!QFileInfo::exists(path("tree/a/b")));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::dirRename()
{
    QVERIFY(QDir(dir->path()).mkdir("before"));
    QFile file(path("before/file.txt"));
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.close();
    eval("var d = new Dir(" + quoted("before") + "); d.rename('file.txt', 'moved.txt');");
    QVERIFY(QFileInfo::exists(path("before/moved.txt")));
    QVERIFY(!QFileInfo::exists(path("before/file.txt")));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::dirStatics()
{
    QCOMPARE(eval("Dir.current"), QDir::currentPath());
    QCOMPARE(eval("Dir.home"), QDir::homePath());
    QCOMPARE(eval("Dir.root"), QDir::rootPath());
    QCOMPARE(eval("Dir.cleanDirPath('/a/b/../c/./d')"), QString("/a/c/d"));
    QCOMPARE(eval("Dir.drives.length > 0"), QString("true"));

    const QString previous = QDir::currentPath();
    eval("Dir.current = " + quoted(""));
    QCOMPARE(QDir::currentPath(), QDir(dir->path()).absolutePath());
    QVERIFY(QDir::setCurrent(previous));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::processExecute()
{
    const QString cmake = QString::fromUtf8(QSA_TEST_CMAKE);
    QCOMPARE(ip->evaluate("Process.execute(['" + cmake + "', '--version'])").toInt(), 0);
    QVERIFY(eval("Process.stdout").contains("cmake"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::processOutput()
{
    const QString cmake = QString::fromUtf8(QSA_TEST_CMAKE);
    ip->evaluate("Process.execute(['" + cmake + "', '-E', 'echo', 'from the process'])");
    QCOMPARE(eval("Process.stdout").trimmed(), QString("from the process"));
    QVERIFY(ip->evaluate("Process.execute(['" + cmake + "', '-E', 'false'])").toInt() != 0);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Utils::processInstance()
{
    const QString cmake = QString::fromUtf8(QSA_TEST_CMAKE);
    eval("var p = new Process(); p.arguments = ['" + cmake + "', '-E', 'echo', 'instance']; p.start();");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QTRY_COMPARE_WITH_TIMEOUT(eval("p.running"), QString("false"), 10000);
    QCOMPARE(eval("p.exitStatus"), QString("0"));
    // the output arrives through the event loop, reading it consumes it
    QString output;
    QTRY_VERIFY_WITH_TIMEOUT((output += eval("p.readStdout()"), output.contains("instance")), 10000);
}

void tst_Utils::processStartFailure()
{
    const QString program = "qsa_no_such_program_xyz";
    ip->evaluate("Process.execute(['" + program + "'])");
    QVERIFY(ip->hadError());
    QVERIFY2(ip->errorMessage().contains(program), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("1 + 1"), QString("2"));

    eval("var p = new Process(); p.arguments = ['" + program + "']; p.start();");
    QVERIFY(ip->hadError());
}

static QStringList collectedWarnings;
static void collectWarnings(QtMsgType type, const QMessageLogContext &, const QString &message)
{
    if (type == QtWarningMsg)
        collectedWarnings << message;
}

void tst_Utils::processSignalsExist()
{
    // all signals the process wrappers connect to have to exist, a missing one is only reported as a warning
    collectedWarnings.clear();
    const QtMessageHandler previous = qInstallMessageHandler(collectWarnings);
    const QString cmake = QString::fromUtf8(QSA_TEST_CMAKE);
    ip->evaluate("Process.execute(['" + cmake + "', '--version'])");
    eval("var p = new Process(); p.arguments = ['" + cmake + "', '--version']; p.start();");
    QTRY_COMPARE_WITH_TIMEOUT(eval("p.running"), QString("false"), 10000);
    qInstallMessageHandler(previous);
    QVERIFY2(collectedWarnings.filter("No such signal").isEmpty(), qPrintable(collectedWarnings.join("\n")));
    QVERIFY2(collectedWarnings.filter("No such slot").isEmpty(), qPrintable(collectedWarnings.join("\n")));
}

void tst_Utils::disabledUtilities()
{
    QSInterpreter other;
    other.setErrorMode(QSInterpreter::Nothing);
    other.addObjectFactory(new QSUtilFactory(QSUtilFactory::File));
    QVERIFY(other.evaluate("File.exists('.')").toBool());
    other.evaluate("new Dir('.')");
    QVERIFY(other.hadError());
}

void tst_Utils::invalidClassName()
{
    ip->evaluate("new DoesNotExist()");
    QVERIFY(ip->hadError());
}

QTEST_MAIN(tst_Utils)

#include "tst_utils.moc"
