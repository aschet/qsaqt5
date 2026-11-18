#include <qsinterpreter.h>

#include <QtTest/QtTest>

class tst_Interpreter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void errorSignal();
    void errorModeNothingKeepsQuiet();
    void errorMessageAndLine();
    void stackTrace();
    void transientVariables();
    void evaluateInContext();
    void clearRemovesDefinitions();
    void definitionLists();
    void timeout();
    void defaultInterpreter();
    void independentInterpreters();

private:
    QSInterpreter *ip = nullptr;
};

void tst_Interpreter::init()
{
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
}

void tst_Interpreter::cleanup()
{
    delete ip;
    ip = nullptr;
}

void tst_Interpreter::errorSignal()
{
    qRegisterMetaType<QSInterpreter *>();
    QSignalSpy spy(ip, SIGNAL(error(QString,QString,int)));
    ip->evaluate("var a = 1;\nvar b = a + missing;", 0, "errors.qs");

    QVERIFY(ip->hadError());
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(1).toString(), QString("errors.qs"));
    QCOMPARE(spy.first().at(2).toInt(), 2);
    QVERIFY(!spy.first().at(0).toString().isEmpty());
}

void tst_Interpreter::errorModeNothingKeepsQuiet()
{
    QCOMPARE(ip->errorMode(), QSInterpreter::Nothing);
    ip->evaluate("throw 'plain';");
    QVERIFY(ip->hadError());
    ip->evaluate("1 + 1");
    QVERIFY(!ip->hadError());
}

void tst_Interpreter::errorMessageAndLine()
{
    ip->evaluate("function f() {\n  return nothingHere;\n}\nf();", 0, "lines.qs");
    QVERIFY(ip->hadError());
    QVERIFY(ip->errorMessage().contains("nothingHere"));
}

void tst_Interpreter::stackTrace()
{
    ip->evaluate("function inner() { return missing; }\nfunction outer() { return inner(); }\nouter();", 0, "trace.qs");
    QVERIFY(ip->hadError());
    const QSStackTrace trace = ip->stackTrace();
    QVERIFY(!trace.isEmpty());
    QVERIFY(ip->stackTraceString().contains("inner"));
}

void tst_Interpreter::transientVariables()
{
    ip->addTransientVariable("answer", 42);
    ip->addTransientVariable("greeting", QString("hi"));
    QCOMPARE(ip->evaluate("answer + 1").toInt(), 43);
    QCOMPARE(ip->evaluate("greeting + '!'").toString(), QString("hi!"));
    QCOMPARE(ip->variable("answer").toInt(), 42);

    ip->evaluate("var fromScript = 'set'");
    QCOMPARE(ip->variable("fromScript").toString(), QString("set"));
}

void tst_Interpreter::evaluateInContext()
{
    QObject context;
    context.setObjectName("ctx");
    ip->evaluate("var local = 5; function get() { return local; }", &context);
    QCOMPARE(ip->call("get", QVariantList(), &context).toInt(), 5);
    QVERIFY(ip->variables(&context).contains("local"));
    QVERIFY(!ip->hasVariable("local"));
}

void tst_Interpreter::clearRemovesDefinitions()
{
    ip->evaluate("var v = 1; function f() {}");
    QVERIFY(ip->hasVariable("v"));
    ip->clear();
    QVERIFY(!ip->hasVariable("v"));
    QVERIFY(!ip->hasFunction("f"));
    QCOMPARE(ip->evaluate("2 * 2").toInt(), 4);
}

void tst_Interpreter::definitionLists()
{
    ip->evaluate("var alpha = 1; function beta(a, b) {} class Gamma { function m() {} }");
    QVERIFY(ip->variables().contains("alpha"));
    QVERIFY(ip->hasVariable("alpha"));
    QVERIFY(ip->functions().contains("beta"));
    QCOMPARE(ip->functions(QSInterpreter::FunctionSignatures), QStringList() << "beta( a, b )");
    QVERIFY(ip->classes().contains("Gamma"));
    QVERIFY(ip->hasClass("Gamma"));
    QVERIFY(!ip->hasClass("Delta"));
}

void tst_Interpreter::timeout()
{
    ip->setTimeoutInterval(100);
    QCOMPARE(ip->timeoutInterval(), 100);
    // the timeout signal only reports, the handler has to stop the script
    connect(ip, SIGNAL(timeout(int)), ip, SLOT(stopExecution()));
    QSignalSpy spy(ip, SIGNAL(timeout(int)));
    QElapsedTimer timer;
    timer.start();
    ip->evaluate("var i = 0; while (true) { i++; }");
    QVERIFY(timer.elapsed() < 20000);
    QVERIFY(spy.count() >= 1);
    QVERIFY(!ip->isRunning());

    ip->setTimeoutInterval(-1);
    QCOMPARE(ip->evaluate("var s = 0; for (var i = 0; i < 1000; i++) s += i; s").toInt(), 499500);
}

void tst_Interpreter::defaultInterpreter()
{
    QSInterpreter *first = QSInterpreter::defaultInterpreter();
    QVERIFY(first);
    QCOMPARE(QSInterpreter::defaultInterpreter(), first);
    QVERIFY(first->checkSyntax("var a = 1;"));
}

void tst_Interpreter::independentInterpreters()
{
    QSInterpreter other;
    other.setErrorMode(QSInterpreter::Nothing);
    ip->evaluate("var shared = 1;");
    QVERIFY(ip->hasVariable("shared"));
    QVERIFY(!other.hasVariable("shared"));
    other.evaluate("var shared = 2;");
    QCOMPARE(ip->variable("shared").toInt(), 1);
    QCOMPARE(other.variable("shared").toInt(), 2);
}

QTEST_MAIN(tst_Interpreter)

#include "tst_interpreter.moc"
