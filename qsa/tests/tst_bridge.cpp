#include <qsinterpreter.h>
#include <qsobjectfactory.h>
#include <qswrapperfactory.h>

#include <QtTest/QtTest>

struct Item
{
    QString text;
    int number = 0;
};

class ItemWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int number READ number WRITE setNumber)
public:
    explicit ItemWrapper(Item *i) : item(i) {}

    QString text() const { return item->text; }
    void setText(const QString &t) { item->text = t; }
    int number() const { return item->number; }
    void setNumber(int n) { item->number = n; }

public slots:
    QString describe() const { return item->text + "#" + QString::number(item->number); }

private:
    Item *item;
};

class ItemFactory : public QSWrapperFactory
{
public:
    ItemFactory() { registerWrapper("Item"); }

    QObject *create(const QString &className, void *ptr) override
    {
        if (className == "Item")
            return new ItemWrapper(static_cast<Item *>(ptr));
        return nullptr;
    }
};

class Child : public QObject
{
    Q_OBJECT
public:
    explicit Child(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    QString who() const { return "child"; }
};

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(double ratio READ ratio WRITE setRatio)
    Q_PROPERTY(bool flag READ flag WRITE setFlag)

public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent), child_(new Child(this))
    {
        child_->setObjectName("theChild");
    }

    QString name() const { return name_; }
    void setName(const QString &n) { name_ = n; emit nameChanged(n); }
    int count() const { return count_; }
    void setCount(int c) { count_ = c; }
    double ratio() const { return ratio_; }
    void setRatio(double r) { ratio_ = r; }
    bool flag() const { return flag_; }
    void setFlag(bool f) { flag_ = f; }

    Item item;
    QString lastCall;

public slots:
    QString echo(const QString &s) { return s; }
    QString greet(const QString &who) { return "hello " + who; }
    QString emptyString() { return QString(); }
    QString unicode() { return QString::fromUtf8("\xc3\xa4\xe2\x82\xac"); }
    QString concat(const QString &a, const QString &b, int n) { return a + b + QString::number(n); }
    QVariant variantEcho(const QVariant &v) { return v; }
    QVariant variantString() { return QString("from variant"); }
    QVariant variantNumber() { return 12; }
    int sum(int a, int b) { return a + b; }
    double scale(double v, double f) { return v * f; }
    bool negate(bool b) { return !b; }
    qlonglong bigProduct(qlonglong a, qlonglong b) { return a * b; }
    qulonglong unsignedBig(qulonglong a) { return a + 1; }
    int byteCount(const QByteArray &b) { return b.size(); }
    QByteArray bytes() { return "bytes"; }
    int doubled(int *v) { return *v * 2; }
    double halved(double *v) { return *v / 2; }
    QStringList names() { return QStringList() << "a" << "b" << "c"; }
    int listSize(const QStringList &l) { return l.size(); }
    QVariantList numbers() { return QVariantList() << 1 << 2 << 3; }
    QObject *child() { return child_; }
    QObject *nothing() { return nullptr; }
    QString childName(QObject *o) { return o ? o->objectName() : QString("null"); }
    Item *itemPointer() { return &item; }
    void trigger(int v) { emit fired(v); }
    void remember(const QString &s) { lastCall = s; }
    void overloaded(int) { lastCall = "int"; }
    void overloaded(const QString &) { lastCall = "string"; }

signals:
    void fired(int value);
    void nameChanged(const QString &name);

private:
    QString name_;
    int count_ = 0;
    double ratio_ = 0;
    bool flag_ = false;
    Child *child_;
};

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    explicit Counter(int start = 0) : value_(start) {}
    int value() const { return value_; }
    void setValue(int v) { value_ = v; }

public slots:
    int increment() { return ++value_; }

private:
    int value_;
};

class CounterFactory : public QSObjectFactory
{
public:
    CounterFactory() { registerClass("Counter", &Counter::staticMetaObject); }

    QObject *create(const QString &className, const QVariantList &arguments, QObject *) override
    {
        if (className == "Counter")
            return new Counter(arguments.isEmpty() ? 0 : arguments.first().toInt());
        return nullptr;
    }
};

class tst_Bridge : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void stringResults();
    void stringParameters();
    void variantResults();
    void numbersAndBooleans();
    void wideIntegers();
    void byteArrays();
    void numberPointers();
    void stringLists();
    void objectResults();
    void objectParameters();
    void properties();
    void signalsToScript();
    void transientSignalHandler();
    void overloadedSlots();
    void callScriptFunction();
    void callScriptFunctionWithTypes();
    void wrapperFactory();
    void objectFactory();
    void objectFactoryInstances();
    void unknownMemberIsAnError();
    void wrongArgumentsAreAnError();
    void transientObjectLifetime();

private:
    QString eval(const QString &code) { return ip->evaluate(code).toString(); }

    QSInterpreter *ip = nullptr;
    Backend *backend = nullptr;
};

void tst_Bridge::init()
{
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
    ip->addWrapperFactory(new ItemFactory);
    ip->addObjectFactory(new CounterFactory);

    backend = new Backend;
    backend->setObjectName("backend");
    ip->addTransientObject(backend);
}

void tst_Bridge::cleanup()
{
    delete ip;
    delete backend;
    ip = nullptr;
    backend = nullptr;
}

void tst_Bridge::stringResults()
{
    QCOMPARE(eval("backend.echo('plain')"), QString("plain"));
    QCOMPARE(eval("backend.greet('qsa')"), QString("hello qsa"));
    QCOMPARE(eval("backend.unicode()"), QString::fromUtf8("\xc3\xa4\xe2\x82\xac"));
    QCOMPARE(eval("backend.unicode().length"), QString("2"));
    QCOMPARE(eval("backend.emptyString().length"), QString("0"));
    QCOMPARE(eval("typeof backend.greet('x')"), QString("string"));
    QCOMPARE(eval("backend.greet('a') + backend.greet('b')"), QString("hello ahello b"));
    QCOMPARE(eval("backend.greet('abc').toUpperCase()"), QString("HELLO ABC"));
    QCOMPARE(eval("backend.greet(backend.greet('x'))"), QString("hello hello x"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::stringParameters()
{
    QCOMPARE(eval("backend.concat('a', 'b', 3)"), QString("ab3"));
    QCOMPARE(eval("backend.echo(12)"), QString("12"));
    QCOMPARE(eval("backend.echo(1.5)"), QString("1.5"));
    QCOMPARE(eval("backend.echo(['x', 'y'].join(','))"), QString("x,y"));
    eval("backend.remember('stored')");
    QCOMPARE(backend->lastCall, QString("stored"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::variantResults()
{
    QCOMPARE(eval("backend.variantString()"), QString("from variant"));
    QCOMPARE(eval("backend.variantNumber() + 1"), QString("13"));
    QCOMPARE(eval("backend.variantEcho('text')"), QString("text"));
    QCOMPARE(eval("backend.variantEcho(5) * 2"), QString("10"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::numbersAndBooleans()
{
    QCOMPARE(eval("backend.sum(40, 2)"), QString("42"));
    QCOMPARE(eval("backend.scale(2.5, 4)"), QString("10"));
    QCOMPARE(eval("backend.sum(-5, 2)"), QString("-3"));
    QCOMPARE(eval("backend.negate(true) ? 'yes' : 'no'"), QString("no"));
    QCOMPARE(eval("backend.negate(false) ? 'yes' : 'no'"), QString("yes"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::wideIntegers()
{
    QCOMPARE(ip->evaluate("backend.bigProduct(100000, 100000)").toLongLong(), 10000000000LL);
    QCOMPARE(eval("backend.bigProduct(-3, 7)"), QString("-21"));
    QCOMPARE(ip->evaluate("backend.unsignedBig(5000000000)").toLongLong(), 5000000001LL);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::byteArrays()
{
    QCOMPARE(eval("backend.byteCount('abcd')"), QString("4"));
    QCOMPARE(eval("backend.bytes().length"), QString("5"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::numberPointers()
{
    QCOMPARE(eval("backend.doubled(21)"), QString("42"));
    QCOMPARE(eval("backend.halved(9)"), QString("4.5"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::stringLists()
{
    QCOMPARE(eval("backend.names().join('/')"), QString("a/b/c"));
    QCOMPARE(eval("backend.names().length"), QString("3"));
    QCOMPARE(eval("backend.listSize(['x', 'y'])"), QString("2"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::objectResults()
{
    QCOMPARE(eval("backend.child().who()"), QString("child"));
    QCOMPARE(eval("backend.child().objectName"), QString("theChild"));
    QCOMPARE(eval("backend.nothing() == null"), QString("true"));
    QCOMPARE(eval("var c = backend.child(); c.who() + c.who()"), QString("childchild"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::objectParameters()
{
    QCOMPARE(eval("backend.childName(backend.child())"), QString("theChild"));
    QCOMPARE(eval("backend.childName(backend)"), QString("backend"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::properties()
{
    eval("backend.name = 'set from script'; backend.count = 7; backend.ratio = 0.25; backend.flag = true;");
    QCOMPARE(backend->name(), QString("set from script"));
    QCOMPARE(backend->count(), 7);
    QCOMPARE(backend->ratio(), 0.25);
    QVERIFY(backend->flag());

    backend->setName("from C++");
    backend->setCount(11);
    backend->setFlag(false);
    QCOMPARE(eval("backend.name"), QString("from C++"));
    QCOMPARE(eval("backend.count + 1"), QString("12"));
    QCOMPARE(eval("backend.flag ? 'on' : 'off'"), QString("off"));
    QCOMPARE(eval("typeof backend.name"), QString("string"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::signalsToScript()
{
    eval("var received = 0; function onFired(v) { received = v; }");
    ip->addTransientSignalHandler(backend, SIGNAL(fired(int)), "onFired");
    backend->trigger(21);
    QCOMPARE(ip->variable("received").toInt(), 21);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::transientSignalHandler()
{
    eval("var names = ''; function onName(n) { names += n; }");
    ip->addTransientSignalHandler(backend, SIGNAL(nameChanged(QString)), "onName");
    backend->setName("one");
    backend->setName("two");
    QCOMPARE(ip->variable("names").toString(), QString("onetwo"));

    ip->removeTransientSignalHandler(backend, SIGNAL(nameChanged(QString)), "onName");
    backend->setName("three");
    QCOMPARE(ip->variable("names").toString(), QString("onetwo"));

    eval("backend.trigger(1)");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::overloadedSlots()
{
    eval("backend.overloaded(3)");
    QCOMPARE(backend->lastCall, QString("int"));
    eval("backend.overloaded('text')");
    QCOMPARE(backend->lastCall, QString("string"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::callScriptFunction()
{
    ip->evaluate("function add(a, b) { return a + b; } function label(s) { return 'label ' + s; }");
    QCOMPARE(ip->call("add", QVariantList() << 40 << 2).toInt(), 42);
    QCOMPARE(ip->call("label", QVariantList() << "x").toString(), QString("label x"));
    QVERIFY(ip->hasFunction("add"));
    QVERIFY(!ip->hasFunction("missing"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::callScriptFunctionWithTypes()
{
    ip->evaluate("function kind(v) { return typeof v; } function first(l) { return l[0]; } function count(l) { return l.length; }");
    QCOMPARE(ip->call("kind", QVariantList() << 1.5).toString(), QString("number"));
    QCOMPARE(ip->call("kind", QVariantList() << "s").toString(), QString("string"));
    QCOMPARE(ip->call("kind", QVariantList() << true).toString(), QString("boolean"));
    QCOMPARE(ip->call("first", QVariantList() << QVariant(QStringList() << "p" << "q")).toString(), QString("p"));
    QCOMPARE(ip->call("count", QVariantList() << QVariant(QStringList() << "p" << "q")).toInt(), 2);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::wrapperFactory()
{
    backend->item.text = "first";
    backend->item.number = 3;

    QCOMPARE(eval("backend.itemPointer().text"), QString("first"));
    QCOMPARE(eval("backend.itemPointer().number"), QString("3"));
    QCOMPARE(eval("backend.itemPointer().describe()"), QString("first#3"));

    eval("var i = backend.itemPointer(); i.text = 'second'; i.number = 4;");
    QCOMPARE(backend->item.text, QString("second"));
    QCOMPARE(backend->item.number, 4);
    QCOMPARE(eval("i.describe() + i.describe()"), QString("second#4second#4"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::objectFactory()
{
    QCOMPARE(eval("var c = new Counter(5); c.increment(); c.increment()"), QString("7"));
    QCOMPARE(eval("c.value"), QString("7"));
    QCOMPARE(eval("c.value = 1; c.increment()"), QString("2"));
    QCOMPARE(eval("new Counter().increment()"), QString("1"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::objectFactoryInstances()
{
    QCOMPARE(eval("var a = new Counter(10); var b = new Counter(20); a.increment() + b.increment()"), QString("32"));
    QCOMPARE(eval("class Derived extends Object { var c = new Counter(1); function bump() { return c.increment(); } } new Derived().bump()"),
             QString("2"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Bridge::unknownMemberIsAnError()
{
    ip->evaluate("backend.doesNotExist()");
    QVERIFY(ip->hadError());
    QCOMPARE(eval("backend.sum(1, 1)"), QString("2"));
    QVERIFY(!ip->hadError());
}

void tst_Bridge::wrongArgumentsAreAnError()
{
    ip->evaluate("backend.sum(1)");
    QVERIFY(ip->hadError());
    QCOMPARE(eval("backend.sum(1, 1)"), QString("2"));
}

void tst_Bridge::transientObjectLifetime()
{
    const int before = ip->presentObjects().size();
    {
        QObject temporary;
        temporary.setObjectName("temporary");
        ip->addTransientObject(&temporary);
        QCOMPARE(eval("temporary.objectName"), QString("temporary"));
        QVERIFY(ip->presentObjects().contains(&temporary));
    }
    QCOMPARE(ip->presentObjects().size(), before);
    QCOMPARE(eval("backend.sum(2, 2)"), QString("4"));
}

QTEST_MAIN(tst_Bridge)

#include "tst_bridge.moc"
