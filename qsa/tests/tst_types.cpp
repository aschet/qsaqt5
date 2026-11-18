#include <qsinterpreter.h>

#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtTest/QtTest>

class Leaf : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rank READ rank WRITE setRank)
public:
    explicit Leaf(QObject *parent = nullptr) : QObject(parent) {}
    int rank() const { return rank_; }
    void setRank(int r) { rank_ = r; }
public slots:
    QString kind() const { return "leaf"; }

private:
    int rank_ = 0;
};

class Types : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_PROPERTY(Mode mode READ mode WRITE setMode)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QPoint point READ point WRITE setPoint)
    Q_PROPERTY(QSize size READ size WRITE setSize)
    Q_PROPERTY(QRect rect READ rect WRITE setRect)
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(QStringList list READ list WRITE setList)
    Q_PROPERTY(QVariant variant READ variant WRITE setVariant)
    Q_PROPERTY(qlonglong wide READ wide WRITE setWide)

public:
    enum Mode { Off, On, Auto };

    explicit Types(QObject *parent = nullptr) : QObject(parent), leaf_(new Leaf(this))
    {
        leaf_->setObjectName("leaf");
    }

    Mode mode() const { return mode_; }
    void setMode(Mode m) { mode_ = m; }
    QColor color() const { return color_; }
    void setColor(const QColor &c) { color_ = c; }
    QPoint point() const { return point_; }
    void setPoint(const QPoint &p) { point_ = p; }
    QSize size() const { return size_; }
    void setSize(const QSize &s) { size_ = s; }
    QRect rect() const { return rect_; }
    void setRect(const QRect &r) { rect_ = r; }
    QDate date() const { return date_; }
    void setDate(const QDate &d) { date_ = d; }
    QStringList list() const { return list_; }
    void setList(const QStringList &l) { list_ = l; }
    QVariant variant() const { return variant_; }
    void setVariant(const QVariant &v) { variant_ = v; }
    qlonglong wide() const { return wide_; }
    void setWide(qlonglong w) { wide_ = w; }

    Leaf *leaf() const { return leaf_; }

public slots:
    // integral and floating point types
    bool boolEcho(bool v) { return v; }
    short shortEcho(short v) { return v; }
    ushort ushortEcho(ushort v) { return v; }
    int intEcho(int v) { return v; }
    uint uintEcho(uint v) { return v; }
    long longEcho(long v) { return v; }
    ulong ulongEcho(ulong v) { return v; }
    qlonglong longLongEcho(qlonglong v) { return v; }
    qulonglong ulongLongEcho(qulonglong v) { return v; }
    float floatEcho(float v) { return v; }
    double doubleEcho(double v) { return v; }
    int manyArguments(int a, int b, int c, int d, int e, int f, int g, int h) { return a + b + c + d + e + f + g + h; }

    // text
    QString stringEcho(QString v) { return v; }
    QString constRefEcho(const QString &v) { return v; }
    QByteArray byteArrayEcho(const QByteArray &v) { return v; }
    QChar charEcho(QChar v) { return v; }
    QString nullString() { return QString(); }
    int stringLength(const QString &v) { return v.length(); }

    // containers
    QStringList stringListEcho(const QStringList &v) { return v; }
    QVariantList variantListEcho(const QVariantList &v) { return v; }
    QVariantList variantList() { return QVariantList() << 1 << "two" << 3.5; }
    QVariant variantEcho(const QVariant &v) { return v; }
    QString variantType(const QVariant &v) { return v.typeName(); }

    // value types
    QPoint pointEcho(const QPoint &v) { return v; }
    QPoint pointSum(const QPoint &a, const QPoint &b) { return a + b; }
    QSize sizeEcho(const QSize &v) { return v; }
    QRect rectEcho(const QRect &v) { return v; }
    QColor colorEcho(const QColor &v) { return v; }
    QColor mixed() { return QColor(10, 20, 30); }
    QFont fontEcho(const QFont &v) { return v; }
    QDate dateEcho(const QDate &v) { return v; }
    QTime timeEcho(const QTime &v) { return v; }
    QDateTime dateTimeEcho(const QDateTime &v) { return v; }
    QDate fixedDate() { return QDate(2021, 3, 4); }
    QDateTime fixedDateTime() { return QDateTime(QDate(2021, 3, 4), QTime(5, 6, 7)); }
    QString describeDate(const QDate &v) { return v.toString(Qt::ISODate); }
    QString describeDateTime(const QDateTime &v) { return v.toString(Qt::ISODate); }
    QVariantList dateList() { return QVariantList() << date_ << QDateTime(date_, QTime(5, 6, 7)); }
    QVariantMap dateMap() { QVariantMap m; m["date"] = date_; return m; }

    // objects
    QObject *objectEcho(QObject *v) { return v; }
    Leaf *leafEcho(Leaf *v) { return v; }
    Leaf *theLeaf() { return leaf_; }
    QString objectKind(QObject *v) { return v ? v->metaObject()->className() : QString("null"); }
    QObject *nullObject() { return nullptr; }

    // pointers
    int intPointer(int *v) { return *v + 1; }
    uint uintPointer(uint *v) { return *v + 1; }
    qlonglong longLongPointer(qlonglong *v) { return *v + 1; }
    float floatPointer(float *v) { return *v + 1; }
    double doublePointer(double *v) { return *v + 1; }

    // enumerations
    Mode modeEcho(Mode m) { return m; }
    QString modeName(Mode m) { return m == Off ? "off" : m == On ? "on" : "auto"; }
    void setModeSlot(Mode m) { mode_ = m; }

    // no result and overloads
    void voidSlot() { ++voidCalls; }
    QString overload(int) { return "int"; }
    QString overload(const QString &) { return "string"; }
    QString overload(double, double) { return "two"; }

public:
    int voidCalls = 0;

private:
    Mode mode_ = Off;
    QColor color_;
    QPoint point_;
    QSize size_;
    QRect rect_;
    QDate date_;
    QStringList list_;
    QVariant variant_;
    qlonglong wide_ = 0;
    Leaf *leaf_;
};

class tst_Types : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void results_data();
    void results();
    void integerLimits_data();
    void integerLimits();
    void invalidNumbers();
    void nullArguments();
    void properties_data();
    void properties();
    void propertyRoundTrip();
    void dateConversions_data();
    void dateConversions();
    void enums();
    void pointers_data();
    void pointers();
    void objectIdentity();
    void objectSubclass();
    void voidResult();
    void overloads();
    void unusualCalls();
    void callWithTypes();
    void callWithObjects();
    void callResultTypes();
    void variantResultTypes();

private:
    QVariant value(const QString &code) { return ip->evaluate(code); }
    QString eval(const QString &code) { return ip->evaluate(code).toString(); }

    QSInterpreter *ip = nullptr;
    Types *types = nullptr;
};

void tst_Types::initTestCase()
{
    // classes that are not known to the interpreter would be wrapped as plain pointers
    QSInterpreter::registerMetaObject(&Leaf::staticMetaObject);
}

void tst_Types::init()
{
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
    types = new Types;
    types->setObjectName("t");
    ip->addTransientObject(types);
}

void tst_Types::cleanup()
{
    delete ip;
    delete types;
    ip = nullptr;
    types = nullptr;
}

void tst_Types::results_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("bool true") << "t.boolEcho(true) == true" << "true";
    QTest::newRow("short") << "t.shortEcho(-123)" << "-123";
    QTest::newRow("ushort") << "t.ushortEcho(60000)" << "60000";
    QTest::newRow("int") << "t.intEcho(-70000)" << "-70000";
    QTest::newRow("uint") << "t.uintEcho(3000000000) == 3000000000" << "true";
    QTest::newRow("long") << "t.longEcho(-5)" << "-5";
    QTest::newRow("ulong") << "t.ulongEcho(7)" << "7";
    QTest::newRow("float") << "t.floatEcho(1.5)" << "1.5";
    QTest::newRow("double") << "t.doubleEcho(0.1) + t.doubleEcho(0.2) == 0.1 + 0.2" << "true";
    QTest::newRow("double negative") << "t.doubleEcho(-2.25)" << "-2.25";
    QTest::newRow("many arguments") << "t.manyArguments(1, 2, 3, 4, 5, 6, 7, 8)" << "36";
    QTest::newRow("string") << "t.stringEcho('abc')" << "abc";
    QTest::newRow("const ref string") << "t.constRefEcho('xyz')" << "xyz";
    QTest::newRow("string number") << "t.stringEcho(42)" << "42";
    QTest::newRow("string unicode") << QString::fromUtf8("t.stringEcho('\xc3\xa4\xc3\xb6\xc3\xbc')") << QString::fromUtf8("\xc3\xa4\xc3\xb6\xc3\xbc");
    QTest::newRow("string length") << QString::fromUtf8("t.stringLength('\xe2\x82\xac\xe2\x82\xac')") << "2";
    QTest::newRow("long string") << "t.stringLength('x'.arg(1) + 'abcdefghij'.arg(1))" << "11";
    QTest::newRow("null string") << "t.nullString().length" << "0";
    QTest::newRow("null string empty") << "t.nullString() == ''" << "true";
    QTest::newRow("byte array") << "t.byteArrayEcho('bytes')" << "bytes";
    QTest::newRow("char") << "t.charEcho('x')" << "x";
    QTest::newRow("string list") << "t.stringListEcho(['a', 'b']).join('+')" << "a+b";
    QTest::newRow("string list length") << "t.stringListEcho(['a', 'b', 'c']).length" << "3";
    QTest::newRow("variant list") << "t.variantList()[1]" << "two";
    QTest::newRow("variant list number") << "t.variantList()[0] + 1" << "2";
    QTest::newRow("variant list echo") << "t.variantListEcho([1, 'x']).length" << "2";
    QTest::newRow("variant string") << "t.variantEcho('str')" << "str";
    QTest::newRow("variant number") << "t.variantEcho(2.5) * 2" << "5";
    QTest::newRow("variant bool") << "t.variantEcho(true)" << "true";
    QTest::newRow("variant type string") << "t.variantType('s')" << "QString";
    QTest::newRow("variant type number") << "t.variantType(1.5)" << "double";
    QTest::newRow("variant type bool") << "t.variantType(true)" << "bool";
    QTest::newRow("point") << "var p = t.pointEcho(new Point(3, 4)); p.x * 10 + p.y" << "34";
    QTest::newRow("point sum") << "var p = t.pointSum(new Point(1, 2), new Point(10, 20)); p.x + ',' + p.y" << "11,22";
    QTest::newRow("size") << "var s = t.sizeEcho(new Size(5, 6)); s.width * 10 + s.height" << "56";
    QTest::newRow("rect") << "var r = t.rectEcho(new Rect(1, 2, 30, 40)); r.x + r.y + r.width + r.height" << "73";
    QTest::newRow("color") << "t.colorEcho(new Color('blue')).name" << "#0000ff";
    QTest::newRow("color result") << "t.mixed().green" << "20";
    QTest::newRow("font") << "t.fontEcho(new Font()).family.length > 0" << "true";
    QTest::newRow("date result") << "var d = t.fixedDate(); d.getYear() * 10000 + d.getMonth() * 100 + d.getDate()" << "20210304";
    QTest::newRow("datetime result") << "var d = t.fixedDateTime(); d.getHours() * 10000 + d.getMinutes() * 100 + d.getSeconds()" << "50607";
    QTest::newRow("date round trip") << "t.dateEcho(new Date(2022, 7, 9)).getDate()" << "9";
    QTest::newRow("datetime round trip") << "t.dateTimeEcho(new Date(2022, 7, 9, 10, 11, 12)).getMinutes()" << "11";
    QTest::newRow("time round trip") << "t.timeEcho(new Date(2022, 7, 9, 10, 11, 12)).getHours()" << "10";
}

void tst_Types::results()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::integerLimits_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<qlonglong>("expected");

    QTest::newRow("int max") << "t.intEcho(2147483647)" << qlonglong(2147483647);
    QTest::newRow("int min") << "t.intEcho(-2147483647)" << qlonglong(-2147483647);
    QTest::newRow("uint max") << "t.uintEcho(4294967295)" << qlonglong(4294967295u);
    QTest::newRow("qlonglong big") << "t.longLongEcho(10000000000)" << 10000000000LL;
    QTest::newRow("qlonglong negative") << "t.longLongEcho(-10000000000)" << -10000000000LL;
    QTest::newRow("qlonglong 2^52") << "t.longLongEcho(4503599627370496)" << 4503599627370496LL;
    QTest::newRow("qulonglong big") << "t.ulongLongEcho(5000000000)" << 5000000000LL;
    QTest::newRow("qlonglong property") << "t.wide = 8000000000; t.wide" << 8000000000LL;
}

void tst_Types::integerLimits()
{
    QFETCH(QString, code);
    QFETCH(qlonglong, expected);

    QCOMPARE(value(code).toLongLong(), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::invalidNumbers()
{
    // a number that cannot be converted is reported, the interpreter keeps working
    ip->evaluate("t.intEcho(0 / 0)");
    ip->evaluate("t.doubleEcho('not a number')");
    ip->evaluate("t.intEcho(new Point(1, 2))");
    QCOMPARE(eval("t.intEcho(3)"), QString("3"));
    QVERIFY(!ip->hadError());
}

void tst_Types::nullArguments()
{
    QCOMPARE(eval("t.objectKind(null)"), QString("null"));
    QCOMPARE(eval("t.objectEcho(null) == null"), QString("true"));
    QCOMPARE(eval("t.nullObject() == null"), QString("true"));
    QCOMPARE(eval("t.stringLength('')"), QString("0"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::properties_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("color") << "t.color = new Color('red'); t.color.name" << "#ff0000";
    QTest::newRow("point") << "t.point = new Point(3, 4); t.point.x + t.point.y" << "7";
    QTest::newRow("size") << "t.size = new Size(7, 8); t.size.width" << "7";
    QTest::newRow("rect") << "t.rect = new Rect(1, 2, 3, 4); t.rect.height" << "4";
    QTest::newRow("date") << "t.date = new Date(2020, 7, 8); t.date.getDate()" << "8";
    QTest::newRow("string list") << "t.list = ['p', 'q']; t.list.join('-')" << "p-q";
    QTest::newRow("variant") << "t.variant = 'text'; t.variant" << "text";
    QTest::newRow("variant number") << "t.variant = 5; t.variant + 1" << "6";
}

void tst_Types::properties()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::dateConversions_data()
{
    QTest::addColumn<QDate>("date");

    QTest::newRow("march") << QDate(2021, 3, 4);
    QTest::newRow("january") << QDate(2020, 1, 31);
    QTest::newRow("december") << QDate(2020, 12, 31);
    QTest::newRow("leap day") << QDate(2020, 2, 29);
}

void tst_Types::dateConversions()
{
    // months count from 1 in every direction, as in the Date constructor
    QFETCH(QDate, date);
    types->setDate(date);
    const QString y = QString::number(date.year()), m = QString::number(date.month()), d = QString::number(date.day());
    const QString expected = y + "-" + m + "-" + d;
    const QString iso = date.toString(Qt::ISODate);
    const QString parts = "%1.getYear() + '-' + %1.getMonth() + '-' + %1.getDate()";

    QCOMPARE(eval(parts.arg("t.date")), expected);
    QCOMPARE(eval(parts.arg("t.dateEcho(t.date)")), expected);
    QCOMPARE(eval(parts.arg("t.dateList()[0]")), expected);
    QCOMPARE(eval(parts.arg("t.dateList()[1]")), expected);
    QCOMPARE(eval(parts.arg("t.dateMap().date")), expected);
    QCOMPARE(eval("t.describeDate(t.date)"), iso);
    QCOMPARE(eval(QString("t.describeDate(new Date(%1, %2, %3))").arg(y, m, d)), iso);
    QCOMPARE(eval(QString("t.describeDateTime(new Date(%1, %2, %3, 5, 6, 7))").arg(y, m, d)), iso + "T05:06:07");
    QCOMPARE(eval(parts.arg(QString("t.dateEcho(new Date(%1, %2, %3))").arg(y, m, d))), expected);
    eval(QString("t.date = new Date(%1, %2, %3)").arg(y, m, d));
    QCOMPARE(types->date(), date);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::propertyRoundTrip()
{
    eval("t.color = new Color(1, 2, 3); t.point = new Point(5, 6); t.size = new Size(7, 8); t.list = ['x', 'y', 'z'];");
    QCOMPARE(types->color(), QColor(1, 2, 3));
    QCOMPARE(types->point(), QPoint(5, 6));
    QCOMPARE(types->size(), QSize(7, 8));
    QCOMPARE(types->list(), QStringList() << "x" << "y" << "z");

    types->setColor(QColor(200, 100, 50));
    types->setRect(QRect(1, 2, 3, 4));
    types->setDate(QDate(2019, 12, 24));
    QCOMPARE(eval("t.color.red"), QString("200"));
    QCOMPARE(eval("t.rect.width"), QString("3"));
    QCOMPARE(eval("t.date.getMonth()"), QString("12"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::enums()
{
    QCOMPARE(eval("t.modeName(t.On)"), QString("on"));
    QCOMPARE(eval("t.modeName(t.Auto)"), QString("auto"));
    QCOMPARE(eval("t.modeEcho(t.Auto)"), QString("2"));
    eval("t.setModeSlot(t.On)");
    QCOMPARE(types->mode(), Types::On);
    eval("t.mode = t.Auto");
    QCOMPARE(types->mode(), Types::Auto);
    types->setMode(Types::Off);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("typeof t.mode"), QString("number"));
    QCOMPARE(eval("t.mode == t.Off"), QString("true"));
    QCOMPARE(eval("t.mode + 0"), QString("0"));
    types->setMode(Types::Auto);
    QCOMPARE(eval("t.mode"), QString("2"));
}

void tst_Types::pointers_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("int") << "t.intPointer(41)" << "42";
    QTest::newRow("int negative") << "t.intPointer(-10)" << "-9";
    QTest::newRow("uint") << "t.uintPointer(9)" << "10";
    QTest::newRow("qlonglong") << "t.longLongPointer(99)" << "100";
    QTest::newRow("float") << "t.floatPointer(1.5)" << "2.5";
    QTest::newRow("double") << "t.doublePointer(2.25)" << "3.25";
}

void tst_Types::pointers()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::objectIdentity()
{
    QCOMPARE(eval("t.theLeaf().kind()"), QString("leaf"));
    QCOMPARE(eval("t.objectEcho(t.theLeaf()).kind()"), QString("leaf"));
    QCOMPARE(eval("t.objectKind(t.theLeaf())"), QString("Leaf"));
    QCOMPARE(eval("t.objectKind(t)"), QString("Types"));
    QCOMPARE(eval("t.theLeaf() == t.theLeaf()"), QString("true"));
    QCOMPARE(eval("t.theLeaf().rank = 5; t.theLeaf().rank"), QString("5"));
    QCOMPARE(types->leaf()->rank(), 5);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::objectSubclass()
{
    QCOMPARE(eval("t.leafEcho(t.theLeaf()).kind()"), QString("leaf"));
    QCOMPARE(eval("var l = t.leafEcho(t.theLeaf()); l.rank = 3; l.rank"), QString("3"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::voidResult()
{
    eval("t.voidSlot(); t.voidSlot();");
    QCOMPARE(types->voidCalls, 2);
    QCOMPARE(eval("typeof t.voidSlot()"), QString("undefined"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::overloads()
{
    QCOMPARE(eval("t.overload(1)"), QString("int"));
    QCOMPARE(eval("t.overload('s')"), QString("string"));
    QCOMPARE(eval("t.overload(1, 2)"), QString("two"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::unusualCalls()
{
    ip->evaluate("t.noSuchSlot(1)");
    QVERIFY(ip->hadError());
    ip->evaluate("t.intEcho()");
    QVERIFY(ip->hadError());
    ip->evaluate("t.intEcho(1, 2, 3, 4)");
    QCOMPARE(eval("t.intEcho(9)"), QString("9"));
    QVERIFY(!ip->hadError());
}

void tst_Types::callWithTypes()
{
    ip->evaluate("function describe(v) { return typeof v + ':' + v; }"
                 "function first(l) { return l[0]; }"
                 "function xy(p) { return p.x + ',' + p.y; }"
                 "function wh(s) { return s.width + 'x' + s.height; }"
                 "function colorName(c) { return c.name; }"
                 "function year(d) { return d.getYear(); }");
    QCOMPARE(ip->call("describe", QVariantList() << 5).toString(), QString("number:5"));
    QCOMPARE(ip->call("describe", QVariantList() << 1.5).toString(), QString("number:1.5"));
    QCOMPARE(ip->call("describe", QVariantList() << QString("s")).toString(), QString("string:s"));
    QCOMPARE(ip->call("describe", QVariantList() << true).toString(), QString("boolean:true"));
    QCOMPARE(ip->call("first", QVariantList() << QVariant(QVariantList() << 4 << 5)).toInt(), 4);
    QCOMPARE(ip->call("xy", QVariantList() << QPoint(3, 4)).toString(), QString("3,4"));
    QCOMPARE(ip->call("wh", QVariantList() << QSize(5, 6)).toString(), QString("5x6"));
    QCOMPARE(ip->call("colorName", QVariantList() << QColor(255, 0, 0)).toString(), QString("#ff0000"));
    QCOMPARE(ip->call("year", QVariantList() << QDate(2024, 2, 29)).toInt(), 2024);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::callWithObjects()
{
    ip->evaluate("function kindOf(o) { return o.kind(); } function rankOf(o) { return o.rank; }");
    QCOMPARE(ip->call("kindOf", QVariantList() << QVariant::fromValue(static_cast<QObject *>(types->leaf()))).toString(),
             QString("leaf"));
    types->leaf()->setRank(12);
    QCOMPARE(ip->call("rankOf", QVariantList() << QVariant::fromValue(static_cast<QObject *>(types->leaf()))).toInt(), 12);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::callResultTypes()
{
    ip->evaluate("function num() { return 12.5; } function str() { return 'text'; } function bool() { return true; }"
                 "function arr() { return [1, 2, 3]; } function nothing() { }");
    QCOMPARE(ip->call("num").toDouble(), 12.5);
    QCOMPARE(ip->call("str").toString(), QString("text"));
    QCOMPARE(ip->call("bool").toBool(), true);
    QVERIFY(!ip->call("nothing").isValid() || ip->call("nothing").isNull() || ip->call("nothing").toString().isEmpty());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Types::variantResultTypes()
{
    QCOMPARE(value("5").userType(), int(QMetaType::Double));
    QCOMPARE(value("'s'").userType(), int(QMetaType::QString));
    QCOMPARE(value("true").userType(), int(QMetaType::Bool));
    QCOMPARE(value("new Point(1, 2)").value<QPoint>(), QPoint(1, 2));
    QCOMPARE(value("new Size(3, 4)").value<QSize>(), QSize(3, 4));
    QCOMPARE(value("new Color(1, 2, 3)").value<QColor>(), QColor(1, 2, 3));
    QCOMPARE(value("new Date(2020, 7, 8)").toDate(), QDate(2020, 7, 8));
}

QTEST_MAIN(tst_Types)

#include "tst_types.moc"
