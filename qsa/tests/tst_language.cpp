#include <qsinterpreter.h>

#include <QtTest/QtTest>

// values thrown by a script arrive in the catch block wrapped in an Error object
static const QString thrownValueText = "function msg(e) { return String(e).replace('Error: ', ''); } ";

class tst_Language : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void expressions_data();
    void expressions();
    void stringFunctions_data();
    void stringFunctions();
    void parseNumbers_data();
    void parseNumbers();
    void regExp_data();
    void regExp();
    void dateParse();
    void dates_data();
    void dates();
    void valueTypes_data();
    void valueTypes();
    void parserErrors_data();
    void parserErrors();
    void deepNesting();
    void elisions();
    void scriptScenarios_data();
    void scriptScenarios();
    void syntaxErrorCleanup_data();
    void syntaxErrorCleanup();
    void arrays_data();
    void arrays();
    void functionsAndScopes_data();
    void functionsAndScopes();
    void classes_data();
    void classes();
    void tryCatchFinally_data();
    void tryCatchFinally();
    void functionExpressionsWithTry();
    void runtimeError();
    void syntaxErrors_data();
    void syntaxErrors();
    void repeatedEvaluation();

private:
    QString eval(const QString &code) { return ip->evaluate(code).toString(); }

    QSInterpreter *ip = nullptr;
};

void tst_Language::init()
{
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
}

void tst_Language::cleanup()
{
    delete ip;
    ip = nullptr;
}

void tst_Language::expressions_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("add") << "1 + 2" << "3";
    QTest::newRow("precedence") << "2 + 3 * 4" << "14";
    QTest::newRow("parentheses") << "(2 + 3) * 4" << "20";
    QTest::newRow("division") << "7 / 2" << "3.5";
    QTest::newRow("modulo") << "7 % 4" << "3";
    QTest::newRow("shift") << "1 << 4" << "16";
    QTest::newRow("bitwise") << "(6 & 3) | 8" << "10";
    QTest::newRow("string concat") << "'a' + 'b' + 1" << "ab1";
    QTest::newRow("number plus string") << "1 + 2 + 'x'" << "3x";
    QTest::newRow("comparison") << "(3 < 4) && (4 <= 4)" << "true";
    QTest::newRow("strict equality") << "1 === '1'" << "false";
    QTest::newRow("loose equality") << "1 == '1'" << "true";
    QTest::newRow("conditional") << "5 > 3 ? 'yes' : 'no'" << "yes";
    QTest::newRow("typeof") << "typeof 'x'" << "string";
    QTest::newRow("increment") << "var i = 1; i++; ++i; i" << "3";
    QTest::newRow("compound assignment") << "var i = 10; i -= 3; i *= 2; i" << "14";
    QTest::newRow("while") << "var s = 0; var i = 0; while (i < 5) { s += i; i++; } s" << "10";
    QTest::newRow("for") << "var s = 0; for (var i = 1; i <= 4; i++) s += i; s" << "10";
    QTest::newRow("for in") << "var o = {a: 1, b: 2}; var k = ''; for (var p in o) k += p; k.length" << "2";
    QTest::newRow("do while") << "var i = 0; do { i++; } while (i < 3); i" << "3";
    QTest::newRow("switch") << "var r = ''; switch (2) { case 1: r = 'a'; break; case 2: r = 'b'; break; default: r = 'c'; } r" << "b";
    QTest::newRow("break continue") << "var s = 0; for (var i = 0; i < 10; i++) { if (i == 2) continue; if (i == 5) break; s += i; } s" << "8";
    QTest::newRow("math") << "Math.max(1, 5, 3) + Math.floor(2.7) + Math.abs(-1)" << "8";
    QTest::newRow("infinity") << "(1 / 0) == Infinity" << "true";
    QTest::newRow("nan") << "isNaN(0 / 0)" << "true";
    QTest::newRow("object literal") << "var o = {x: 4}; o.x * 2" << "8";
}

void tst_Language::expressions()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::stringFunctions_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("length") << "'hello'.length" << "5";
    QTest::newRow("toUpperCase") << "'abc'.toUpperCase()" << "ABC";
    QTest::newRow("substring") << "'abcdef'.substring(1, 3)" << "bc";
    QTest::newRow("indexOf") << "'abcabc'.indexOf('c')" << "2";
    QTest::newRow("lastIndexOf") << "'abcabc'.lastIndexOf('c')" << "5";
    QTest::newRow("charAt") << "'abc'.charAt(1)" << "b";
    QTest::newRow("split join") << "'a,b,c'.split(',').join('-')" << "a-b-c";
    QTest::newRow("replace") << "'a-b-c'.replace(/-/g, '+')" << "a+b+c";
    QTest::newRow("unicode") << QString::fromUtf8("'\xc3\xa4\xc3\xb6'.length") << "2";
    QTest::newRow("unicode upper") << QString::fromUtf8("'\xc3\xa4'.toUpperCase()") << QString::fromUtf8("\xc3\x84");
    QTest::newRow("string from number") << "String(12.5)" << "12.5";
    QTest::newRow("arg") << "'%1 and %2'.arg('a').arg(2)" << "a and 2";
    QTest::newRow("left right mid") << "'abc'.left(2) + 'abc'.right(1) + 'abc'.mid(1, 1)" << "abcb";
    QTest::newRow("empty") << "''.length" << "0";
}

void tst_Language::stringFunctions()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::parseNumbers_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("parseInt") << "parseInt('42')" << "42";
    QTest::newRow("parseInt trailing") << "parseInt('42abc')" << "42";
    QTest::newRow("parseInt negative") << "parseInt('-17')" << "-17";
    QTest::newRow("parseInt radix") << "parseInt('ff', 16)" << "255";
    QTest::newRow("parseInt hex prefix") << "parseInt('0x1f')" << "31";
    QTest::newRow("parseInt binary") << "parseInt('101', 2)" << "5";
    QTest::newRow("parseInt no digits") << "isNaN(parseInt('abc'))" << "true";
    QTest::newRow("parseInt blanks") << "parseInt('  7')" << "7";
    QTest::newRow("parseFloat") << "parseFloat('3.25xyz')" << "3.25";
    QTest::newRow("parseFloat exponent") << "parseFloat('1e3')" << "1000";
    QTest::newRow("Number") << "Number('12')" << "12";
    QTest::newRow("Number invalid") << "isNaN(Number('x'))" << "true";
}

void tst_Language::parseNumbers()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::regExp_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("search") << "/b+/.search('abbbc')" << "1";
    QTest::newRow("search no match") << "/x/.search('abc')" << "-1";
    QTest::newRow("search ignore case") << "/ABC/i.search('abc')" << "0";
    QTest::newRow("search in string") << "'abc'.search(/c/)" << "2";
    QTest::newRow("search anchors") << "/^abc$/.search('abc')" << "0";
    QTest::newRow("search alternation") << "/cat|dog/.search('hotdog')" << "3";
    QTest::newRow("capture") << "var r = /(\\d+)-(\\d+)/; r.search('10-20'); r.cap(2)" << "20";
    QTest::newRow("captured texts") << "var r = /(\\d+)-(\\d+)/; r.search('10-20'); r.capturedTexts.join('|')" << "10-20|10|20";
    QTest::newRow("matched length") << "var r = /b+/; r.search('abbbc'); r.matchedLength" << "3";
    QTest::newRow("exact match") << "/abc/.exactMatch('abc')" << "true";
    QTest::newRow("exact match fails") << "/abc/.exactMatch('abcd')" << "false";
    QTest::newRow("constructor") << "new RegExp('a.c').exactMatch('abc')" << "true";
    QTest::newRow("source") << "new RegExp('a.c').source" << "a.c";
    QTest::newRow("global flag") << "/a/g.global" << "true";
    QTest::newRow("ignore case flag") << "/a/i.ignoreCase" << "true";
    QTest::newRow("valid") << "new RegExp('a+').valid" << "true";
    QTest::newRow("invalid") << "new RegExp('(').valid" << "false";
    QTest::newRow("empty") << "new RegExp('').empty" << "true";
    QTest::newRow("not empty") << "new RegExp('a').empty" << "false";
    QTest::newRow("replace first") << "'a-b-c'.replace('-', '+')" << "a+b-c";
    QTest::newRow("replace global") << "'a-b-c'.replace(/-/g, '+')" << "a+b+c";
}

void tst_Language::regExp()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::dateParse()
{
    QCOMPARE(eval("Date.parse('2020-03-04T10:20:30Z')"), QString::number(1583317230000.0, 'f', 0));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("Date.parse('2020-03-04')"), QString::number(
                 double(QDateTime(QDate(2020, 3, 4), QTime(0, 0)).toMSecsSinceEpoch()), 'f', 0));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("var d = new Date(2021, 6, 15); d.getYear() * 10000 + d.getMonth() * 100 + d.getDate()"),
             QString("20210615"));
    QCOMPARE(eval("new Date(Date.parse('2020-03-04T10:20:30')).getHours()"), QString("10"));
    QCOMPARE(eval("new Date(0).getTime()"), QString("0"));

    // unparsable text is reported as a script error
    ip->evaluate("Date.parse('this is no date')");
    QVERIFY(ip->hadError());
}

void tst_Language::arrays_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("literal") << "[1, 2, 3].length" << "3";
    QTest::newRow("index") << "[5, 6, 7][1]" << "6";
    QTest::newRow("push pop") << "var a = [1]; a.push(2, 3); a.pop() + a.length" << "5";
    QTest::newRow("join") << "[1, 2, 3].join('+')" << "1+2+3";
    QTest::newRow("reverse") << "[1, 2, 3].reverse().join('')" << "321";
    QTest::newRow("sort") << "[3, 1, 2].sort().join('')" << "123";
    QTest::newRow("sort function") << "[3, 1, 2].sort(function (a, b) { return b - a; }).join('')" << "321";
    QTest::newRow("concat") << "[1].concat([2], [3]).join('')" << "123";
    QTest::newRow("slice") << "[1, 2, 3, 4].slice(1, 3).join('')" << "23";
    QTest::newRow("splice") << "var a = [1, 2, 3, 4]; a.splice(1, 2); a.join('')" << "14";
    QTest::newRow("shift unshift") << "var a = [2]; a.unshift(1); a.shift() + a.length" << "2";
    QTest::newRow("new Array") << "new Array(4).length" << "4";
    QTest::newRow("grow") << "var a = []; a[4] = 1; a.length" << "5";
    QTest::newRow("nested") << "[[1, 2], [3, 4]][1][0]" << "3";
}

void tst_Language::arrays()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::functionsAndScopes_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("declaration") << "function f(a, b) { return a * b; } f(6, 7)" << "42";
    QTest::newRow("recursion") << "function fac(n) { return n <= 1 ? 1 : n * fac(n - 1); } fac(6)" << "720";
    QTest::newRow("arguments") << "function f() { return arguments.length; } f(1, 2, 3)" << "3";
    QTest::newRow("missing argument") << "function f(a, b) { return typeof b; } f(1)" << "undefined";
    QTest::newRow("local shadows global") << "var x = 1; function f() { var x = 2; return x; } f() + x" << "3";
    QTest::newRow("global assigned in function") << "var x = 1; function f() { x = 5; } f(); x" << "5";
    QTest::newRow("function expression") << "var f = function (a) { return a + 1; }; f(1)" << "2";
    QTest::newRow("function as argument") << "function twice(f, v) { return f(f(v)); } twice(function (n) { return n * 3; }, 2)" << "18";
    QTest::newRow("many locals") << "function f() { var a = 1, b = 2, c = 3, d = 4; return a + b + c + d; } f()" << "10";
    QTest::newRow("function expression locals") << "var f = function () { var a = 1; var b = 2; return a + b; }; f()" << "3";
    QTest::newRow("nested function expressions") << "var f = function () { var g = function () { var k = 4; return k; }; var h = 3; return g() + h; }; f()" << "7";
    QTest::newRow("with") << "var o = {v: 9}; var r; with (o) { r = v; } r" << "9";
}

void tst_Language::functionsAndScopes()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::classes_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("class") << "class A { var v = 3; function get() { return v; } } new A().get()" << "3";
    QTest::newRow("constructor") << "class A { var v; function A(x) { v = x; } function get() { return v; } } new A(7).get()" << "7";
    QTest::newRow("extends")
        << "class A { function name() { return 'a'; } } class B extends A { function other() { return 'b'; } } var b = new B(); b.name() + b.other()"
        << "ab";
    QTest::newRow("override")
        << "class A { function name() { return 'a'; } } class B extends A { function name() { return 'b'; } } new B().name()"
        << "b";
    QTest::newRow("static")
        << "class A { static function twice(n) { return n * 2; } } A.twice(4)" << "8";
    QTest::newRow("several instances")
        << "class C { var n = 0; function inc() { n++; return n; } } var a = new C(); var b = new C(); a.inc(); a.inc(); b.inc()"
        << "1";
    QTest::newRow("deep inheritance")
        << "class A { function f() { return 1; } } class B extends A { } class C extends B { } new C().f()" << "1";
}

void tst_Language::classes()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::tryCatchFinally_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("catch") << "var r = ''; try { throw 'boom'; } catch (e) { r = msg(e); } r" << "boom";
    QTest::newRow("no throw") << "var r = 'a'; try { r += 'b'; } catch (e) { r += 'c'; } r" << "ab";
    QTest::newRow("finally after try") << "var r = ''; try { r += 't'; } finally { r += 'f'; } r" << "tf";
    QTest::newRow("finally after catch") << "var r = ''; try { throw 1; } catch (e) { r += 'c'; } finally { r += 'f'; } r" << "cf";
    QTest::newRow("return in try runs finally")
        << "var log = ''; function f() { try { return 'r'; } finally { log += 'f'; } } f() + log" << "rf";
    QTest::newRow("finally overrides return")
        << "function f() { try { return 1; } finally { return 2; } } f()" << "2";
    QTest::newRow("nested")
        << "var r = ''; try { try { throw 'x'; } finally { r += 'i'; } }         catch (e) { r += msg(e); } r" << "ix";
            QTest::newRow("rethrow") << "var r = ''; try { try { throw 'a'; } catch (e) { throw msg(e) + 'b'; } } catch (e2) { r = msg(e2); } r" << "ab";
    QTest::newRow("in loop")
        << "var n = 0; for (var i = 0; i < 4; i++) { try { if (i % 2) throw i; } catch (e) { n += parseInt(msg(e)); } finally { n += 10; } } n"
        << "44";
    QTest::newRow("break in try")
        << "var log = ''; for (var i = 0; i < 3; i++) { try { if (i == 1) break; } finally { log += i; } } log" << "01";
    QTest::newRow("error object")
        << "var r; try { throw new Error('msg'); } catch (e) { r = msg(e); } r" << "msg";
    QTest::newRow("runtime error caught")
        << "var r = 'none'; try { undefinedFunction(); } catch (e) { r = 'caught'; } r" << "caught";
}

void tst_Language::tryCatchFinally()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(thrownValueText + code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::functionExpressionsWithTry()
{
    const QString code = thrownValueText +
        "var f = function (v) {"
        "  var out = '';"
        "  try { if (v) throw 'err'; out = 'ok'; }"
        "  catch (e) { out = 'caught ' + msg(e); }"
        "  finally { out += '!'; }"
        "  return out;"
        "};"
        "f(false) + '|' + f(true)";
    QCOMPARE(eval(code), QString("ok!|caught err!"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::runtimeError()
{
    QSignalSpy spy(ip, SIGNAL(error(QString,QString,int)));
    ip->evaluate("var a = 1;\nvar b = unknownThing + 1;", 0, "errors.qs");

    QVERIFY(ip->hadError());
    QVERIFY(!ip->errorMessage().isEmpty());
    QVERIFY(!ip->stackTraceString().isNull());
    QVERIFY(!ip->isRunning());

    // the interpreter has to stay usable
    QCOMPARE(eval("1 + 1"), QString("2"));
    QVERIFY(!ip->hadError());
}

void tst_Language::syntaxErrors_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<bool>("valid");

    QTest::newRow("valid") << "var a = 1; function f(x) { return x; }" << true;
    QTest::newRow("empty") << "" << true;
    QTest::newRow("class") << "class A { function f() {} }" << true;
    QTest::newRow("missing brace") << "function f() { return 1;" << false;
    QTest::newRow("missing parenthesis") << "var a = (1 + 2;" << false;
    QTest::newRow("bad token") << "var 1a = 2;" << false;
    QTest::newRow("unterminated string") << "var s = 'abc;" << false;
    QTest::newRow("else without if") << "else { }" << false;
    QTest::newRow("many errors") << "}}}} ((( ;;; var var var" << false;
}

void tst_Language::syntaxErrors()
{
    QFETCH(QString, code);
    QFETCH(bool, valid);

    QCOMPARE(ip->checkSyntax(code), valid);

    // a syntax error must leave nothing behind that breaks the next run
    QCOMPARE(eval("21 * 2"), QString("42"));
}

void tst_Language::dates_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    // months count from 1 and weekdays from Monday = 1
    QTest::newRow("date parts") << "var d = new Date(2020, 6, 30); d.getYear() + '-' + d.getMonth() + '-' + d.getDate()" << "2020-6-30";
    QTest::newRow("january") << "new Date(2020, 1, 31).getDate()" << "31";
    QTest::newRow("december") << "new Date(2020, 12, 31).getMonth()" << "12";
    QTest::newRow("time parts") << "var d = new Date(2020, 6, 30, 12, 30, 15); d.getHours() + ':' + d.getMinutes() + ':' + d.getSeconds()" << "12:30:15";
    QTest::newRow("weekday") << "new Date(2020, 6, 30).getDay()" << "2";
    QTest::newRow("setDate") << "var d = new Date(2020, 6, 30); d.setDate(1); d.getDate()" << "1";
    QTest::newRow("setMonth") << "var d = new Date(2020, 6, 15); d.setMonth(2); d.getMonth()" << "2";
    QTest::newRow("setHours") << "var d = new Date(2020, 6, 30); d.setHours(5); d.getHours()" << "5";
    QTest::newRow("compare") << "new Date(2020, 6, 30) < new Date(2021, 1, 1)" << "true";
    QTest::newRow("epoch") << "new Date(0).getTime()" << "0";
    QTest::newRow("milliseconds") << "new Date(1500).getMilliseconds()" << "500";
    QTest::newRow("current") << "typeof new Date().getTime()" << "number";
    QTest::newRow("from number") << "new Date(86400000).getTime()" << "86400000";
}

void tst_Language::dates()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::valueTypes_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("expected");

    QTest::newRow("point") << "var p = new Point(3, 4); p.x + p.y" << "7";
    QTest::newRow("point write") << "var p = new Point(3, 4); p.x = 10; p.x" << "10";
    QTest::newRow("size") << "var s = new Size(5, 6); s.width * s.height" << "30";
    QTest::newRow("rect") << "var r = new Rect(1, 2, 30, 40); r.width + r.height" << "70";
    QTest::newRow("rect center") << "new Rect(0, 0, 30, 40).center.x" << "14";
    QTest::newRow("rect isNull") << "new Rect(1, 2, 30, 40).isNull()" << "false";
    QTest::newRow("color name") << "new Color('red').name" << "#ff0000";
    QTest::newRow("color rgb") << "var c = new Color(10, 20, 30); c.red + c.green + c.blue" << "60";
    QTest::newRow("color dark") << "new Color('red').dark().name" << "#7f0000";
    QTest::newRow("font bold") << "var f = new Font(); f.bold = true; f.bold" << "true";
    QTest::newRow("font family") << "new Font().family.length > 0" << "true";
    QTest::newRow("byte array") << "new ByteArray('abc').length" << "3";
    QTest::newRow("empty byte array") << "new ByteArray().length" << "0";
}

void tst_Language::valueTypes()
{
    QFETCH(QString, code);
    QFETCH(QString, expected);

    QCOMPARE(eval(code), expected);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::parserErrors_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<int>("line");

    QTest::newRow("binary operator") << "var a = 1 +" << 2;
    QTest::newRow("open if") << "var a = 1;\nif (" << 3;
    QTest::newRow("missing parameter") << "\n\nfunction ( { }" << 3;
    QTest::newRow("missing value") << "var a = 1;\nvar b = ;" << 2;
    QTest::newRow("two values") << "x = 1 2" << 1;
    QTest::newRow("unterminated string") << "'unterminated" << 1;
    QTest::newRow("unterminated comment") << "var a;\n/* unterminated" << 3;
    QTest::newRow("class without name") << "class extends B {}" << 1;
    QTest::newRow("empty case") << "switch (1) { case: }" << 1;
    QTest::newRow("open for") << "for (;;" << 2;
    QTest::newRow("trailing dot") << "a.b." << 2;
}

void tst_Language::parserErrors()
{
    QFETCH(QString, code);
    QFETCH(int, line);

    // errors at the end of the code are reported for the line behind it
    QSignalSpy spy(ip, SIGNAL(error(QString,QString,int)));
    ip->evaluate(code, 0, "parse.qs");
    QVERIFY(ip->hadError());
    QVERIFY2(ip->errorMessage().contains("Parse Error"), qPrintable(ip->errorMessage()));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(2).toInt(), line);
}

void tst_Language::deepNesting()
{
    const int depth = 20;
    QVERIFY(ip->checkSyntax(QString(depth, '(') + "1" + QString(depth, ')')));
    QCOMPARE(eval(QString(depth, '(') + "1" + QString(depth, ')')), QString("1"));
    QVERIFY(ip->checkSyntax(QString(depth, '[') + "1" + QString(depth, ']')));
    QVERIFY(!ip->checkSyntax(QString(depth, '[') + "1"));

    // the parser stack has a fixed size, deeper nesting is refused without overflowing it
    for (int huge : {300, 5000, 50000})
        QVERIFY(!ip->checkSyntax(QString(huge, '(') + "1" + QString(huge, ')')));
    QCOMPARE(eval("1 + 1"), QString("2"));
}

void tst_Language::elisions()
{
    QCOMPARE(eval("[1, , 3].length"), QString("3"));
    QCOMPARE(eval("[, , ].length"), QString("2"));
    QCOMPARE(eval("[1, , 3][2]"), QString("3"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Language::scriptScenarios_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("function in function")
        << "function outer(a) { var x = a; function inner(b) { var y = b; return x + y; } return inner(1); } outer(2)";
    QTest::newRow("class with function expressions")
        << "class A { var f = function (a) { var t = a; try { return t; } finally { t = 0; } }; function m() { return f(1); } } new A().m()";
    QTest::newRow("class extends in sequence")
        << "class A { function a() { return 1; } } class B extends A { function b() { return 2; } } class C extends B { function c() { return a() + b(); } } new C().c()";
    QTest::newRow("closures")
        << "function make(n) { var c = n; return function () { return c++; }; } var m = make(1); m(); m()";
    QTest::newRow("array of functions")
        << "var fs = []; for (var i = 0; i < 5; i++) fs[i] = function (x) { return x + 1; }; fs[4](1)";
    QTest::newRow("nested try")
        << "function f() { try { try { throw 'a'; } finally { var x = 1; } } catch (e) { return 'c'; } finally { var y = 2; } } f()";
    QTest::newRow("switch in loop")
        << "var s = ''; for (var i = 0; i < 4; i++) { switch (i % 2) { case 0: s += 'e'; break; default: s += 'o'; } } s";
    QTest::newRow("labelled loops")
        << "var n = 0; outer: for (var i = 0; i < 3; i++) { for (var j = 0; j < 3; j++) { if (j == 1) continue outer; n++; } } n";
    QTest::newRow("with and objects")
        << "var o = {a: {b: 1}}; var r = 0; with (o.a) { r = b; } r";
    QTest::newRow("string building")
        << "var s = ''; for (var i = 0; i < 50; i++) s += 'x' + i; s.length";
}

void tst_Language::scriptScenarios()
{
    QFETCH(QString, code);

    // the scenarios free the syntax tree of functions, classes and nested scopes, which a memory checker
    // verifies when the tests run under a sanitizer
    for (int i = 0; i < 50; ++i) {
        ip->evaluate(code);
        QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
        ip->clear();
    }
}

void tst_Language::syntaxErrorCleanup_data()
{
    QTest::addColumn<QString>("code");

    QTest::newRow("function body") << "function f(a, b) { var x = [1, 2, {a: 1}; }";
    QTest::newRow("class body") << "class A { var v = (1 + ; function f() {} }";
    QTest::newRow("call arguments") << "f(1, 2, g(3, h(4, ), 5);";
    QTest::newRow("object literal") << "var o = {a: 1, b: {c: [1, 2}, d: 3};";
    QTest::newRow("statement list") << "var a = 1; var b = 2; if (a) { b++; } else { ) }";
    QTest::newRow("try") << "try { f(); } catch (e { }";
    QTest::newRow("switch") << "switch (a) { case 1: x(); case : y(); }";
    QTest::newRow("long garbage") << QString("} ( ; var ").repeated(200);
}

void tst_Language::syntaxErrorCleanup()
{
    QFETCH(QString, code);

    // the nodes the parser already created have to be released
    for (int i = 0; i < 100; ++i)
        QVERIFY(!ip->checkSyntax(code));
    ip->evaluate(code);
    QVERIFY(ip->hadError());
    QCOMPARE(eval("1 + 1"), QString("2"));
}

void tst_Language::repeatedEvaluation()
{
    for (int i = 0; i < 200; ++i) {
        QCOMPARE(eval(QString("function f%1(a) { try { return a + %1; } finally { a = 0; } } f%1(1)").arg(i)),
                 QString::number(1 + i));
        QVERIFY(ip->checkSyntax("class A { var v = 1; function f() { return v; } } class B extends A {}"));
    }
}

QTEST_MAIN(tst_Language)

#include "tst_language.moc"
