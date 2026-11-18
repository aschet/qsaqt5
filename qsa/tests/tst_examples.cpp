#include <qsinterpreter.h>

#include <QtTest/QtTest>

class tst_Examples : public QObject
{
    Q_OBJECT

private slots:
    void scriptsHaveValidSyntax_data();
    void scriptsHaveValidSyntax();
};

void tst_Examples::scriptsHaveValidSyntax_data()
{
    QTest::addColumn<QString>("path");

    const QDir root(QSA_EXAMPLES_DIR);
    QDirIterator it(root.absolutePath(), QStringList() << "*.qs", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString path = it.next();
        QTest::newRow(qPrintable(root.relativeFilePath(path))) << path;
    }
}

void tst_Examples::scriptsHaveValidSyntax()
{
    QFETCH(QString, path);

    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), qPrintable(file.errorString()));

    QSInterpreter ip;
    ip.setErrorMode(QSInterpreter::Nothing);
    QVERIFY(ip.checkSyntax(QString::fromUtf8(file.readAll())));
}

QTEST_MAIN(tst_Examples)

#include "tst_examples.moc"
