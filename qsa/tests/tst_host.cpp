#include <qsinputdialogfactory.h>
#include <qsinterpreter.h>
#include <qsobjectfactory.h>
#include <qsproject.h>
#include <qsutilfactory.h>

#include <QtTest/QtTest>
#include <QtWidgets/QApplication>

#include <cmath>
#include <stdexcept>

// This suite embeds QSA the way an application with a larger set of wrapper classes does. The classes
// below are small stand-ins that exercise the same mechanisms:
//   - a base class with slots, a virtual slot and error reporting through the interpreter
//   - derived classes whose objects are passed where a base class pointer is expected
//   - properties with custom getters, class enumerations and slots with default arguments
//   - pointers to other wrapper classes as input and as output parameters
//   - singleton instances that are registered together with the class
//   - overloads, containers, global objects and scripts that load other scripts

class WrapperBase : public QObject
{
    Q_OBJECT
public:
    explicit WrapperBase(QObject *parent = nullptr) : QObject(parent) {}
    void setInterpreter(QSInterpreter *i) { interpreter = i; }

    static int resets;

public slots:
    virtual void reset() { ++resets; }
    void fail(const QString &message) { raise(message); }

protected:
    void raise(const QString &message)
    {
        if (interpreter)
            interpreter->throwError(message);
    }

    QSInterpreter *interpreter = nullptr;
};

int WrapperBase::resets = 0;

class Measure : public WrapperBase
{
    Q_OBJECT
public:
    explicit Measure(QObject *parent = nullptr) : WrapperBase(parent) {}
    virtual double value() const { return 0; }

public slots:
    double compare(Measure *other) { return other ? value() - other->value() : value(); }
    virtual QString kind() { return "measure"; }
};

class Length : public Measure
{
    Q_OBJECT
    Q_PROPERTY(double meters READ getMeters WRITE setMeters SCRIPTABLE true)
    Q_ENUMS(Unit)

public:
    enum Unit { METERS = 1, FEET = 2, INCHES = 3 };
    static const char *ReferenceName;

    explicit Length(QObject *parent = nullptr) : Measure(parent) {}

    double getMeters() const { return meters; }
    void setMeters(double m) { meters = m; }
    double value() const override { return meters; }

    static double factor(Unit unit) { return unit == FEET ? 0.3048 : unit == INCHES ? 0.0254 : 1.0; }

public slots:
    void set(double amount, Unit unit = METERS) { meters = amount * factor(unit); }
    double expressedIn(Unit unit = METERS) { return meters / factor(unit); }
    QString describe(Unit unit = METERS, int digits = 2)
    {
        const char *suffix = unit == FEET ? " ft" : unit == INCHES ? " in" : " m";
        return QString::number(expressedIn(unit), 'f', digits) + suffix;
    }
    bool add(Length *other, Length *result)
    {
        if (!other || !result)
            return false;
        result->meters = meters + other->meters;
        return true;
    }
    void scaleInto(double scale, Length *result) { result->meters = meters * scale; }
    bool isLongerThan(Length *other) { return other && meters > other->meters; }
    QString kind() override { return "length"; }

private:
    double meters = 0;
};

const char *Length::ReferenceName = "Length";

class LengthList : public Measure
{
    Q_OBJECT
    Q_PROPERTY(int size READ size SCRIPTABLE true)

public:
    static const char *ReferenceName;
    explicit LengthList(QObject *parent = nullptr) : Measure(parent) {}
    int size() const { return items.size(); }
    double value() const override
    {
        double sum = 0;
        for (double d : items)
            sum += d;
        return sum;
    }

public slots:
    void append(Length *length) { items.append(length->getMeters()); }
    void fetch(int index, Length *out) { out->setMeters(items.at(index)); }
    void total(Length *sum) { sum->setMeters(value()); }
    void shortest(Length *out)
    {
        double best = items.value(0);
        for (double d : items)
            best = std::min(best, d);
        out->setMeters(best);
    }
    QString kind() override { return "list"; }

private:
    QList<double> items;
};

const char *LengthList::ReferenceName = "LengthList";

class Tally : public WrapperBase
{
    Q_OBJECT
public:
    static const char *ReferenceName;
    static QStringList entries;
    explicit Tally(QObject *parent = nullptr) : WrapperBase(parent) {}

public slots:
    void count(const QString &what, int amount = 1) { entries << what + "=" + QString::number(amount); }
};

const char *Tally::ReferenceName = "Tally";
QStringList Tally::entries;

class Shelf : public WrapperBase
{
    Q_OBJECT
public:
    static const char *ReferenceName;
    explicit Shelf(QObject *parent = nullptr) : WrapperBase(parent) {}

public slots:
    void put(const QString &group, const QString &key, LengthList *list)
    {
        sizes.insert(group + "/" + key, list->size());
    }
    bool take(const QString &group, const QString &key, LengthList *into)
    {
        const QString name = group + "/" + key;
        if (!sizes.contains(name))
            return false;
        Length item;
        for (int i = 0; i < sizes.value(name); ++i) {
            item.setMeters(i + 0.5);
            into->append(&item);
        }
        return true;
    }
    void discard(const QString &group) { discarded << group; }

public:
    QMap<QString, int> sizes;
    QStringList discarded;
};

const char *Shelf::ReferenceName = "g_shelf";

class HostUtils : public WrapperBase
{
    Q_OBJECT
    Q_ENUMS(Level)

public:
    enum Level { LOW = 0, MEDIUM = 1, HIGH = 2 };
    static const char *ReferenceName;

    explicit HostUtils(QObject *parent = nullptr) : WrapperBase(parent) {}
    QSInterpreter *host = nullptr;
    QMap<QString, QString> files;
    QStringList included;

public slots:
    int keyCode() { return 13; }
    QString programName() { return "Demo"; }
    int versionNumber() { return 306; }
    QString check(const QString &module) { return module + ":none"; }
    QString check(const QString &module, const QString &code) { return module + ":" + code; }
    void processMessages() { QCoreApplication::processEvents(); }
    void sleep(int milliSeconds) { QTest::qWait(milliSeconds); }
    // evaluates another script while a script is running
    void include(const QString &name)
    {
        if (included.contains(name))
            return;
        included << name;
        if (!files.contains(name))
            raise("Script file not found: " + name);
        else
            host->evaluate(files.value(name), 0, name);
    }
};

const char *HostUtils::ReferenceName = "g_utils";

class MeasureFactory : public QSObjectFactory
{
public:
    MeasureFactory()
    {
        registerClass(Length::ReferenceName, &Length::staticMetaObject, new Length);
        registerClass(LengthList::ReferenceName, &LengthList::staticMetaObject, new LengthList);
    }

    QObject *create(const QString &className, const QVariantList &, QObject *) override
    {
        WrapperBase *result = nullptr;
        if (className == Length::ReferenceName)
            result = new Length;
        else if (className == LengthList::ReferenceName)
            result = new LengthList;
        if (result)
            result->setInterpreter(interpreter());
        return result;
    }
};

class ServiceFactory : public QSObjectFactory
{
public:
    ServiceFactory()
    {
        registerClass(Tally::ReferenceName, &Tally::staticMetaObject, new Tally);
    }

    QObject *create(const QString &className, const QVariantList &, QObject *) override
    {
        return className == Tally::ReferenceName ? new Tally : nullptr;
    }
};

// the scripting host of the application
class Host : public QObject
{
    Q_OBJECT
public:
    explicit Host(bool threadAware) : threadAware(threadAware)
    {
        if (!threadAware) {
            project = new QSProject(this);
            script = project->createScript("main");
            interpreter = project->interpreter();
        } else {
            interpreter = new QSInterpreter(this);
        }
        interpreter->setErrorMode(QSInterpreter::Nothing);

        utils = new HostUtils;
        utils->setObjectName(HostUtils::ReferenceName);
        utils->host = interpreter;
        utils->setInterpreter(interpreter);
        shelf = new Shelf;
        shelf->setObjectName(Shelf::ReferenceName);
        shelf->setInterpreter(interpreter);
        objects << utils << shelf;
        for (QObject *o : objects)
            o->setParent(this);
        addGlobalObjects();

        installFactory(new QSUtilFactory);
        installFactory(new MeasureFactory);
        installFactory(new ServiceFactory);
        // objects of the interpreter without a project are removed when a factory is added
        addGlobalObjects();

        connect(interpreter, SIGNAL(error(const QString&, const QString&, int)),
                this, SLOT(catchError(const QString&, const QString&, int)));
    }

    void addGlobalObjects()
    {
        if (!project) {
            for (QObject *o : objects)
                interpreter->addTransientObject(o);
        } else if (project->objects().isEmpty()) {
            for (QObject *o : objects)
                project->addObject(o);
        }
    }

    void installFactory(QSObjectFactory *factory)
    {
        interpreter->addObjectFactory(factory);
        const QMap<QString, QString> found = factory->instanceDescriptors();
        for (auto it = found.begin(); it != found.end(); ++it)
            types << it.key();
        types.sort();
    }

    QString code() const { return script ? script->code() : plainCode; }
    void setCode(const QString &c)
    {
        if (script)
            script->setCode(c);
        else
            plainCode = c;
    }

    // runs code and turns C++ exceptions of wrappers into an error of the host
    bool exec(const QString &c, QVariant *result = nullptr)
    {
        bool errorOccurred = false;
        QString message;
        clearErrorState();
        try {
            if (result)
                *result = interpreter->evaluate(c);
            else
                interpreter->evaluate(c);
        } catch (const std::exception &e) {
            errorOccurred = true;
            message = QString::fromUtf8(e.what());
        }
        if (errorOccurred) {
            // evaluates the code again to reset the running state of the interpreter
            interpreter->evaluate(code());
            interpreter->clear();
            error = message;
            hasError = true;
        }
        return !hasError;
    }

    bool execFunc(const QString &name, QVariant *result, const QVariantList &args)
    {
        clearErrorState();
        if (result)
            *result = interpreter->call(name, args);
        else
            interpreter->call(name, args);
        return !hasError;
    }

    // the functions without parameters can be started from a list
    QStringList paramlessFunctions() const
    {
        const QStringList all = interpreter->functions(QSInterpreter::FunctionSignatures);
        QRegularExpression expression(QRegularExpression::anchoredPattern("([a-zA-Z_$][a-zA-Z0-9_$]*)\\(\\)"));
        QStringList result;
        for (const QString &signature : all)
            if (expression.match(signature).hasMatch())
                result << signature.left(signature.length() - 2);
        return result;
    }

    void clearErrorState()
    {
        hasError = false;
        error.clear();
        errorTrace.clear();
        errorLine = -1;
    }

    bool threadAware;
    QSProject *project = nullptr;
    QSScript *script = nullptr;
    QSInterpreter *interpreter = nullptr;
    HostUtils *utils = nullptr;
    Shelf *shelf = nullptr;
    QObjectList objects;
    QStringList types;
    QString plainCode;

    bool hasError = false;
    QString error, errorTrace, errorScript;
    int errorLine = -1;
    int errorSignals = 0;

public slots:
    // the first error is kept and the script is stopped
    void catchError(const QString &message, const QString &scriptName, int lineNumber)
    {
        ++errorSignals;
        if (!hasError) {
            error = message;
            errorTrace = interpreter->stackTraceString();
            errorScript = scriptName;
            errorLine = lineNumber;
            hasError = true;
        }
        interpreter->stopExecution();
    }
};

class Thrower : public QObject
{
    Q_OBJECT
public slots:
    void failHard() { throw std::runtime_error("hard failure"); }
    int value() { return 7; }
};

class tst_Host : public QObject
{
    Q_OBJECT

public:
    explicit tst_Host(bool threadAware) : threadAware(threadAware) {}

private slots:
    void init();
    void cleanup();

    void globalObjects();
    void factoryTypes();
    void createWrappers();
    void properties();
    void enumerations();
    void defaultArguments();
    void outParameters();
    void containers();
    void inheritance();
    void staticInstances();
    void shelf();
    void overloadsByArgumentCount();
    void callFromScriptToScript();
    void includes();
    void includeNotFound();
    void scriptErrors();
    void errorHandlerStopsScript();
    void errorInTryCatch();
    void stackTrace();
    void cppExceptions();
    void repeatedCppExceptions();
    void functionsAndSignatures();
    void checkSyntax();
    void execFunction();
    void idioms_data();
    void idioms();
    void virtualSlots();
    void clearKeepsFactories();
    void sleepAndProcessMessages();
    void projectMode();
    void threadAwareExecution();
    void interruptFromOtherThread();
    void concurrentHosts();

private:
    QString eval(const QString &code)
    {
        QVariant result;
        host->exec(code, &result);
        return result.toString();
    }
    bool isTrue(const QString &code) { return host->interpreter->evaluate(code).toBool(); }

    bool threadAware;
    Host *host = nullptr;
};

void tst_Host::init()
{
    host = new Host(threadAware);
    Tally::entries.clear();
    WrapperBase::resets = 0;
}

void tst_Host::cleanup()
{
    delete host;
    host = nullptr;
}

void tst_Host::globalObjects()
{
    QCOMPARE(eval("g_utils.programName()"), QString("Demo"));
    QCOMPARE(eval("g_utils.versionNumber() + 1"), QString("307"));
    QCOMPARE(eval("g_utils.keyCode()"), QString("13"));
    QCOMPARE(eval("g_utils.HIGH"), QString("2"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::factoryTypes()
{
    QVERIFY(host->types.contains("Length"));
    QVERIFY(host->types.contains("LengthList"));
    QVERIFY(host->types.contains("Tally"));
    QVERIFY(host->types.contains("File"));
    QVERIFY(host->types.contains("Dir"));
    QVERIFY(host->types.contains("Process"));
}

void tst_Host::createWrappers()
{
    // classes are created with and without parentheses, variables may be implicit globals
    QCOMPARE(eval("var a = new Length(); a.set(2); a.meters"), QString("2"));
    QCOMPARE(eval("b = new Length; b.set(4); b.meters"), QString("4"));
    QCOMPARE(eval("typeof b"), QString("object"));
    QCOMPARE(eval("var l = new LengthList; l.size"), QString("0"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::properties()
{
    QCOMPARE(eval("var p = new Length; p.meters = 1.5; p.meters * 2"), QString("3"));
    QCOMPARE(eval("p.meters = p.meters + 1e3; p.meters"), QString("1001.5"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::enumerations()
{
    // enumerations are reachable through the class (static instance) and through instances
    QCOMPARE(eval("Length.METERS"), QString("1"));
    QCOMPARE(eval("Length.FEET"), QString("2"));
    QCOMPARE(eval("var p = new Length; p.INCHES"), QString("3"));
    QCOMPARE(eval("p.set(10, Length.FEET); Math.round(p.meters * 10000)"), QString("30480"));
    QCOMPARE(eval("Math.round(p.expressedIn(Length.FEET))"), QString("10"));
    QCOMPARE(eval("p.set(12, p.INCHES); Math.round(p.expressedIn(Length.INCHES))"), QString("12"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::defaultArguments()
{
    QCOMPARE(eval("var p = new Length; p.set(3); p.expressedIn()"), QString("3"));
    QCOMPARE(eval("p.set(2.4); p.describe()"), QString("2.40 m"));
    QCOMPARE(eval("p.describe(Length.METERS, 0)"), QString("2 m"));
    QCOMPARE(eval("p.set(3.048); p.describe(Length.FEET, 1)"), QString("10.0 ft"));
    QCOMPARE(eval("p.describe(p.INCHES)"), QString("120.00 in"));
    QCOMPARE(eval("Tally.count('x'); Tally.count('y', 5); 1"), QString("1"));
    QCOMPARE(Tally::entries, QStringList() << "x=1" << "y=5");
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::outParameters()
{
    QCOMPARE(eval("var a = new Length; a.set(1.5); var b = new Length; b.set(2); var r = new Length;"
                  "var ok = a.add(b, r); r.meters"),
             QString("3.5"));
    QCOMPARE(eval("ok ? 'yes' : 'no'"), QString("yes"));
    QCOMPARE(eval("a.add(null, r) ? 'yes' : 'no'"), QString("no"));
    QCOMPARE(eval("var s = new Length; a.scaleInto(4, s); s.meters"), QString("6"));
    // the same object can be used again and again as the target
    QCOMPARE(eval("var sum = 0; for (var i = 1; i <= 3; i++) { a.set(i); a.scaleInto(2, s); sum += s.meters; } sum"),
             QString("12"));
    QCOMPARE(eval("b.isLongerThan(a) ? 'longer' : 'shorter'"), QString("shorter"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::containers()
{
    const QString fill =
        "var list = new LengthList; var item = new Length;"
        "for (var i = 1; i <= 4; i++) { item.set(i); list.append(item); }";
    QCOMPARE(eval(fill + "list.size"), QString("4"));
    QCOMPARE(eval("var out = new Length; list.fetch(2, out); out.meters"), QString("3"));
    QCOMPARE(eval("var sum = new Length; list.total(sum); sum.meters"), QString("10"));
    QCOMPARE(eval("var low = new Length; list.shortest(low); low.meters"), QString("1"));
    // the list keeps copies of what was appended
    QCOMPARE(eval("item.set(100); list.fetch(0, out); out.meters"), QString("1"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::inheritance()
{
    // slots of the base class work on derived objects and a derived object is accepted as base pointer
    QCOMPARE(eval("var a = new Length; a.set(5); var b = new Length; b.set(3); a.compare(b)"), QString("2"));
    QCOMPARE(eval("var list = new LengthList; list.append(a); list.append(b); list.compare(a)"), QString("3"));
    QCOMPARE(eval("a.compare(list)"), QString("-3"));
    QCOMPARE(eval("a.compare(null)"), QString("5"));
    QCOMPARE(eval("a.reset(); list.reset(); 1"), QString("1"));
    QCOMPARE(WrapperBase::resets, 2);
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::virtualSlots()
{
    QCOMPARE(eval("var a = new Length; var l = new LengthList; a.kind() + ',' + l.kind()"), QString("length,list"));
    QCOMPARE(eval("a.compare(l)"), QString("0"));
}

void tst_Host::staticInstances()
{
    QCOMPARE(eval("Tally.count('a'); Tally.count('b', 2)"), QString());
    QCOMPARE(Tally::entries.size(), 2);
    QCOMPARE(Tally::entries.at(0), QString("a=1"));
    QCOMPARE(eval("var t = new Tally; t.count('c', 3); Tally.count('d')"), QString());
    QCOMPARE(Tally::entries.size(), 4);
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::shelf()
{
    const QString code =
        "var list = new LengthList; var item = new Length;"
        "for (var i = 0; i < 3; i++) { item.set(i); list.append(item); }"
        "g_shelf.put('group', 'key_' + 1, list); var back = new LengthList;";
    eval(code);
    QVERIFY2(!host->hasError, qPrintable(host->error));
    QCOMPARE(host->shelf->sizes.value("group/key_1"), 3);
    QVERIFY(isTrue("g_shelf.take('group', 'key_1', back)"));
    QCOMPARE(eval("back.size"), QString("3"));
    QVERIFY(!isTrue("g_shelf.take('group', 'unknown', back)"));
    eval("g_shelf.discard('group')");
    QCOMPARE(host->shelf->discarded, QStringList() << "group");
}

void tst_Host::overloadsByArgumentCount()
{
    QCOMPARE(eval("g_utils.check('module')"), QString("module:none"));
    QCOMPARE(eval("g_utils.check('module', 'abc')"), QString("module:abc"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::callFromScriptToScript()
{
    QCOMPARE(eval("function twice(p) { return p * 2; } function useWrapper(n) { var v = new Length; v.set(n); return twice(v.meters); } useWrapper(21)"),
             QString("42"));
    QVariant result;
    QVERIFY(host->execFunc("useWrapper", &result, QVariantList() << 5));
    QCOMPARE(result.toInt(), 10);
}

void tst_Host::includes()
{
    host->utils->files["helpers.qs"] =
        "function conditional(c, a, b) { if (c) return a; return b; }"
        "var included_marker = 42;";
    host->utils->files["nested.qs"] =
        "g_utils.include('helpers.qs');"
        "function viaNested() { return conditional(true, 'nested', 'none'); }";
    QCOMPARE(eval("g_utils.include('helpers.qs'); conditional(false, 1, 2) + included_marker"), QString("44"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
    QCOMPARE(eval("g_utils.include('nested.qs'); viaNested()"), QString("nested"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
    // includes inside a function that was called by the script
    host->utils->included.clear();
    QCOMPARE(eval("function load() { g_utils.include('helpers.qs'); return conditional(true, 'in', 'out'); } load()"),
             QString("in"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::includeNotFound()
{
    eval("g_utils.include('missing.qs'); 1");
    QVERIFY(host->hasError);
    QVERIFY2(host->error.contains("missing.qs"), qPrintable(host->error));
    QCOMPARE(eval("1 + 1"), QString("2"));
}

void tst_Host::scriptErrors()
{
    // errors of the script and errors raised by wrappers are reported through the error signal
    eval("var a = 1;\nvar b = undefinedThing;");
    QVERIFY(host->hasError);
    QCOMPARE(host->errorSignals, 1);
    QCOMPARE(host->errorLine, 2);
    QVERIFY(!host->error.isEmpty());

    host->errorSignals = 0;
    eval("var p = new Length;\np.fail('raised by the wrapper');");
    QVERIFY(host->hasError);
    QVERIFY2(host->error.contains("raised by the wrapper"), qPrintable(host->error));
    QCOMPARE(host->errorLine, 2);

    // the next run starts clean
    QCOMPARE(eval("2 * 21"), QString("42"));
    QVERIFY(!host->hasError);
}

void tst_Host::errorHandlerStopsScript()
{
    eval("var counter = 0; function step() { counter++; var q = new Length; q.fail('stop here'); counter += 100; }"
         "step(); counter += 1000;");
    QVERIFY(host->hasError);
    QCOMPARE(host->interpreter->variable("counter").toInt(), 1);
    QVERIFY(!host->interpreter->isRunning());
}

void tst_Host::errorInTryCatch()
{
    // throwing from the script and catching it works, the thrown value arrives as a text
    QCOMPARE(eval("var r = ''; try { throw 'scripted failure'; } catch (e) { r = 'caught ' + e; } r"),
             QString("caught Error: scripted failure"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
    QCOMPARE(eval("function f() { try { throw 'x'; } finally { g_utils.processMessages(); } } var done = 'no'; try { f(); } catch (e) { done = 'yes'; } done"),
             QString("yes"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::stackTrace()
{
    eval("function inner() { var p = new Length; p.fail('deep'); }\nfunction middle() { inner(); }\nfunction outer() { middle(); }\nouter();");
    QVERIFY(host->hasError);
    QVERIFY2(host->errorTrace.contains("inner"), qPrintable(host->errorTrace));
    QVERIFY2(host->errorTrace.contains("outer"), qPrintable(host->errorTrace));
}

void tst_Host::cppExceptions()
{
    Thrower thrower;
    thrower.setObjectName("thrower");
    host->interpreter->addTransientObject(&thrower);
    if (host->project)
        host->project->addObject(&thrower);

    QVERIFY(!host->exec("thrower.failHard();"));
    QCOMPARE(host->error, QString("hard failure"));
    QVERIFY(!host->interpreter->isRunning());
    // the interpreter has to be usable after the exception, objects of the project are kept
    host->interpreter->addTransientObject(&thrower);
    QCOMPARE(eval("thrower.value() + 1"), QString("8"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::repeatedCppExceptions()
{
    Thrower thrower;
    thrower.setObjectName("thrower");
    if (host->project)
        host->project->addObject(&thrower);
    for (int i = 0; i < 20; ++i) {
        host->interpreter->addTransientObject(&thrower);
        QVERIFY(!host->exec("thrower.failHard();"));
        host->interpreter->addTransientObject(&thrower);
        QCOMPARE(eval("thrower.value()"), QString("7"));
    }
}

void tst_Host::functionsAndSignatures()
{
    eval("function alpha() { } function beta(a) { } function gamma(a, b) { } function delta_1() { } function $dollar() { }");
    const QStringList free = host->paramlessFunctions();
    QVERIFY2(free.contains("alpha"), qPrintable(free.join(",")));
    QVERIFY2(free.contains("delta_1"), qPrintable(free.join(",")));
    QVERIFY(!free.contains("beta"));
    QVERIFY(!free.contains("gamma"));
    const QStringList names = host->interpreter->functions();
    QVERIFY(names.contains("beta"));
    QVERIFY(host->interpreter->hasFunction("gamma"));
    QVERIFY(!host->interpreter->hasFunction("epsilon"));
}

void tst_Host::checkSyntax()
{
    QVERIFY(host->interpreter->checkSyntax("function f() { return new Length; }"));
    QVERIFY(!host->interpreter->checkSyntax("function f() { return new Length; "));
    QVERIFY(host->interpreter->checkSyntax("class A { function f() { return 1; } }"));
    QVERIFY(host->interpreter->checkSyntax(""));
    // checking does not execute anything
    QVERIFY(host->interpreter->checkSyntax("Tally.count('never')"));
    QVERIFY(Tally::entries.isEmpty());
}

void tst_Host::execFunction()
{
    eval("function sum(a, b) { return a + b; } function text(s, n) { return s + ':' + n; } function nothing() { }"
         "function useObject(o) { return o.programName(); } function maxOf(list) { return Math.max(list[0], list[1]); }");
    QVariant result;
    QVERIFY(host->execFunc("sum", &result, QVariantList() << 1.5 << 2.5));
    QCOMPARE(result.toDouble(), 4.0);
    QVERIFY(host->execFunc("text", &result, QVariantList() << "n" << 7));
    QCOMPARE(result.toString(), QString("n:7"));
    QVERIFY(host->execFunc("nothing", &result, QVariantList()));
    QVERIFY(host->execFunc("useObject", &result, QVariantList() << QVariant::fromValue(static_cast<QObject *>(host->utils))));
    QCOMPARE(result.toString(), QString("Demo"));
    QVERIFY(host->execFunc("maxOf", &result, QVariantList() << QVariant(QVariantList() << 3 << 9)));
    QCOMPARE(result.toInt(), 9);
    QVERIFY(!host->hasError);
}

void tst_Host::idioms_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("implicit global") << "implicitValue = 4; implicitValue * 2" << "8";
    QTest::newRow("new without parentheses") << "var d = new Date; typeof d.getTime()" << "number";
    QTest::newRow("typeof wrapper") << "var p = new Length; typeof p" << "object";
    QTest::newRow("typeof undefined") << "typeof notDefinedAnywhere" << "undefined";
    QTest::newRow("typeof string") << "var t = 'x'; (typeof t) == 'string' ? 'yes' : 'no'" << "yes";
    QTest::newRow("delete wrapper") << "var p = new Length; delete p; 1" << "1";
    QTest::newRow("string numbers") << "'value ' + 1 + 2 + ' ' + (1 + 2)" << "value 12 3";
    QTest::newRow("arg decimals") << "'%1'.argDec(3.14159, 0, 'f', 2)" << "3.14";
    QTest::newRow("arg decimals chained") << "'%1 / %2'.argDec(1.5, 0, 'f', 1).argDec(2.25, 0, 'f', 2)" << "1.5 / 2.25";
    QTest::newRow("arg text") << "'%1 and %2'.arg('a').arg('b')" << "a and b";
    QTest::newRow("round") << "Math.round(2.5) + Math.round(-2.4) + Math.abs(-3)" << "4";
    QTest::newRow("math") << "Math.sqrt(16) + Math.atan(0) + Math.sin(0)" << "4";
    QTest::newRow("random range") << "var ok = true; for (var i = 0; i < 20; i++) { var r = Math.random(); if (r < 0 || r >= 1) ok = false; } ok" << "true";
    QTest::newRow("array of objects") << "var list = new Array(); for (var i = 0; i < 3; i++) { var p = new Length; p.set(i); list.push(p); } list[2].meters + list.length" << "5";
    QTest::newRow("array size") << "var a = new Array(5); a.length" << "5";
    QTest::newRow("object as map") << "var o = new Object(); o.a = 1; o['b'] = 2; o.a + o.b" << "3";
    QTest::newRow("switch on string") << "var s = 'b'; var r = ''; switch (s) { case 'a': r = '1'; break; case 'b': r = '2'; break; default: r = '3'; } r" << "2";
    QTest::newRow("regexp search") << "var re = new RegExp('([ \\t]*)var[ \\t]+x[ \\t]*=[ \\t]*.+'); '  var x = 4'.search(re)" << "0";
    QTest::newRow("regexp not found") << "'abc'.search(new RegExp('z+'))" << "-1";
    QTest::newRow("date arithmetic") << "var t1 = new Date(2020, 3, 1).getTime(); var t2 = new Date(2020, 3, 2).getTime(); (t2 - t1) / 1000" << "86400";
    QTest::newRow("class with wrapper member")
        << "class Holder { var p; function Holder() { p = new Length; p.set(4); } function doubled() { return p.meters * 2; } } new Holder().doubled()"
        << "8";
    QTest::newRow("class extends")
        << "class Base { function name() { return 'base'; } } class Derived extends Base { function more() { return name() + '+'; } } new Derived().more()"
        << "base+";
    QTest::newRow("throw string caught") << "var r = 'none'; try { throw 'boom'; } catch (e) { r = 'caught'; } r" << "caught";
    QTest::newRow("finally runs") << "var log = ''; try { log += 'a'; } finally { log += 'b'; } log" << "ab";
    QTest::newRow("nested function calls") << "function a(n) { return n + 1; } function b(n) { return a(n) * 2; } b(a(1))" << "6";
    QTest::newRow("for in") << "var o = {a: 1, b: 2, c: 3}; var n = 0; for (var k in o) n++; n" << "3";
    QTest::newRow("global constants") << "var DEBUG = false; var NAME = 'x'; DEBUG ? 'debug' : NAME" << "x";
    QTest::newRow("conditional helper") << "function conditional(c, a, b) { return c ? a : b; } conditional((typeof q) == 'undefined', 'u', 'd')" << "u";
}

void tst_Host::idioms()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!host->hasError, qPrintable(host->error));
}

void tst_Host::clearKeepsFactories()
{
    eval("var a = new Length;");
    host->interpreter->clear();
    QVERIFY(!host->interpreter->hasVariable("a"));
    // after clearing the factories are still known, project objects are evaluated again
    QCOMPARE(eval("var b = new Length; b.set(1); b.meters"), QString("1"));
    QVERIFY2(!host->hasError, qPrintable(host->error));
    if (host->project)
        QCOMPARE(eval("g_utils.programName()"), QString("Demo"));
}

void tst_Host::sleepAndProcessMessages()
{
    QElapsedTimer timer;
    timer.start();
    QCOMPARE(eval("g_utils.sleep(50); g_utils.processMessages(); 'done'"), QString("done"));
    QVERIFY(timer.elapsed() >= 40);

    // events run while the script is busy, for example the timer that interrupts it
    QTimer::singleShot(30, host->interpreter, SLOT(stopExecution()));
    timer.start();
    eval("var n = 0; while (true) { g_utils.sleep(10); n++; }");
    QVERIFY(timer.elapsed() < 10000);
    QVERIFY(!host->interpreter->isRunning());
}

void tst_Host::projectMode()
{
    if (!host->project)
        QSKIP("the interpreter of the host has no project");

    QVERIFY(host->project->objects().contains(host->utils));
    QVERIFY(host->project->objects().contains(host->shelf));
    QStringList names;
    for (QObject *o : host->project->objects())
        names << o->objectName();
    QVERIFY(names.contains("g_utils"));
    QVERIFY(names.contains("g_shelf"));

    host->setCode("function main() { return g_utils.programName() + '!'; }");
    QCOMPARE(host->script->code(), host->code());
    QCOMPARE(host->interpreter->call("main").toString(), QString("Demo!"));

#ifndef QSA_NO_EDITOR
    // the editor shows the script and its changes are committed into the project
    QSEditor *editor = host->project->createEditor(host->script);
    QVERIFY(editor);
    QCOMPARE(editor->text(), host->code());
    editor->setText("function main() { return 'edited'; }");
    host->project->commitEditorContents();
    QCOMPARE(host->script->code(), QString("function main() { return 'edited'; }"));
    QCOMPARE(host->interpreter->call("main").toString(), QString("edited"));
    delete editor;
#endif
}

void tst_Host::threadAwareExecution()
{
    if (!host->threadAware)
        QSKIP("only for the interpreter without project");

    // scripts run in a worker thread, the interpreter and its objects belong to that thread
    QString result;
    QThread *thread = QThread::create([&]() {
        Host worker(true);
        QVariant v;
        worker.exec("var p = new Length; p.set(3); p.meters + 1", &v);
        result = v.toString() + (worker.hasError ? worker.error : QString());
    });
    thread->start();
    QVERIFY(thread->wait(20000));
    delete thread;
    QCOMPARE(result, QString("4"));
}

void tst_Host::interruptFromOtherThread()
{
    if (!host->threadAware)
        QSKIP("only for the interpreter without project");

    // the interrupt of the application calls stopExecution while the script runs in another thread
    QSInterpreter *interpreter = nullptr;
    QAtomicInt started(0);
    QThread *thread = QThread::create([&]() {
        QSInterpreter local;
        local.setErrorMode(QSInterpreter::Nothing);
        interpreter = &local;
        started.storeRelease(1);
        local.evaluate("var i = 0; while (true) { i++; }");
        interpreter = nullptr;
    });
    thread->start();
    QTRY_VERIFY(started.loadAcquire() == 1);
    QTest::qWait(100);
    if (interpreter)
        interpreter->stopExecution();
    QVERIFY(thread->wait(20000));
    delete thread;
}

void tst_Host::concurrentHosts()
{
    if (!host->threadAware)
        QSKIP("only for the interpreter without project");

    QVector<QThread *> threads;
    QVector<QString> results(4);
    for (int t = 0; t < results.size(); ++t) {
        QThread *thread = QThread::create([t, &results]() {
            Host worker(true);
            QVariant v;
            worker.exec(QString("var s = 0; for (var i = 0; i < 200; i++) { var p = new Length; p.set(i); s += p.meters + %1; } s").arg(t), &v);
            results[t] = v.toString() + (worker.hasError ? worker.error : QString());
        });
        threads << thread;
        thread->start();
    }
    for (int t = 0; t < threads.size(); ++t) {
        QVERIFY(threads[t]->wait(60000));
        delete threads[t];
        QCOMPARE(results[t], QString::number(19900 + 200 * t));
    }
}

// the tests run with a project (QSA_HOST_THREAD_AWARE=0) or with a plain interpreter (QSA_HOST_THREAD_AWARE=1)
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    tst_Host test(QSA_HOST_THREAD_AWARE);
    return QTest::qExec(&test, argc, argv);
}

#include "tst_host.moc"
