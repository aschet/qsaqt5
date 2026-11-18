#include <qsinterpreter.h>
#include <qsproject.h>
#include <qsscript.h>

#include <QtTest/QtTest>
#include <QtWidgets/QTextEdit>

class tst_Editor : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void textRoundTrip();
    void scriptBinding();
    void commitAndRevert();
    void find_data();
    void find();
    void replace();
    void replaceAll();
    void gotoLine();
    void indent();
    void undoRedo();
    void errorMark();

private:
    QSProject *project = nullptr;
    QSScript *script = nullptr;
    QSEditor *editor = nullptr;
};

void tst_Editor::initTestCase()
{
    // keeps the editor preferences of the user out of the tests
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                       QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/qsa-tst-editor");
}

void tst_Editor::init()
{
    project = new QSProject;
    script = project->createScript("edit.qs", "var a = 1;\nvar b = 2;\nvar a2 = a + b;\n");
    editor = project->createEditor(script);
    QVERIFY(editor);
}

void tst_Editor::cleanup()
{
    delete editor;
    delete project;
    editor = nullptr;
    project = nullptr;
}

void tst_Editor::textRoundTrip()
{
    QCOMPARE(editor->text(), script->code());
    editor->setText("var x = 1;");
    QCOMPARE(editor->text(), QString("var x = 1;"));
    QVERIFY(editor->isModified());
}

void tst_Editor::scriptBinding()
{
    QCOMPARE(editor->script(), script);
    QCOMPARE(project->editor(script), editor);
    QVERIFY(project->editors().contains(editor));
    QCOMPARE(editor->project(), project);
}

void tst_Editor::commitAndRevert()
{
    const QString original = script->code();
    editor->setText("var changed = 1;");
    QVERIFY(project->editorsModified());
    editor->revert();
    QCOMPARE(editor->text(), original);

    editor->setText("var committed = 1;");
    editor->commit();
    QCOMPARE(script->code(), QString("var committed = 1;"));
    QVERIFY(!editor->isModified());
}

void tst_Editor::find_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<bool>("caseSensitive");
    QTest::addColumn<bool>("wholeWords");
    QTest::addColumn<bool>("forward");
    QTest::addColumn<bool>("found");

    QTest::newRow("plain") << "var b" << true << false << true << true;
    QTest::newRow("missing") << "nothing" << true << false << true << false;
    QTest::newRow("case sensitive") << "VAR" << true << false << true << false;
    QTest::newRow("case insensitive") << "VAR" << false << false << true << true;
    QTest::newRow("whole word hit") << "a" << true << true << true << true;
    QTest::newRow("whole word miss") << "a2a" << true << true << true << false;
    QTest::newRow("backward") << "var a" << true << false << false << true;
}

void tst_Editor::find()
{
    QFETCH(QString, expression);
    QFETCH(bool, caseSensitive);
    QFETCH(bool, wholeWords);
    QFETCH(bool, forward);
    QFETCH(bool, found);

    QCOMPARE(editor->find(expression, caseSensitive, wholeWords, forward, false), found);
}

void tst_Editor::replace()
{
    editor->setText("one two one");
    QVERIFY(editor->find("one", true, false, true, false));
    // continues behind the selected match
    QVERIFY(editor->replace("one", "1", true, false, true, true, false));
    QCOMPARE(editor->text(), QString("one two 1"));
    QVERIFY(!editor->replace("missing", "x", true, false, true, false, false));
}

void tst_Editor::replaceAll()
{
    editor->setText("one two one three one");
    QVERIFY(editor->replace("one", "1", true, false, true, false, true));
    QCOMPARE(editor->text(), QString("1 two 1 three 1"));
}

void tst_Editor::gotoLine()
{
    editor->gotoLine(2);
    QCOMPARE(editor->textEdit()->textCursor().blockNumber(), 1);
}

void tst_Editor::indent()
{
    editor->setText("function f() {\nvar a = 1;\nif (a) {\nreturn 1;\n}\n}\n");
    editor->textEdit()->selectAll();
    QTest::keyClick(editor->textEdit(), Qt::Key_Tab);

    const QStringList lines = editor->text().split('\n');
    QVERIFY(lines.size() >= 6);
    // a tab is eight columns wide
    auto depth = [&](int line) {
        QString text = lines.at(line);
        text.replace('\t', "        ");
        return text.size() - text.trimmed().size();
    };
    QCOMPARE(depth(0), 0);
    QVERIFY(depth(1) > depth(0));
    QCOMPARE(depth(2), depth(1));
    QVERIFY(depth(3) > depth(2));
    QCOMPARE(depth(4), depth(2));
    QCOMPARE(depth(5), 0);
}

void tst_Editor::undoRedo()
{
    editor->setText("start");
    editor->textEdit()->moveCursor(QTextCursor::End);
    editor->textEdit()->insertPlainText(" more");
    QVERIFY(editor->isUndoAvailable());
    editor->undo();
    QVERIFY(editor->isRedoAvailable());
    editor->redo();
    QCOMPARE(editor->text(), QString("start more"));
}

void tst_Editor::errorMark()
{
    editor->setErrorMark(2);
    editor->removeErrorMark();
}

QTEST_MAIN(tst_Editor)

#include "tst_editor.moc"
