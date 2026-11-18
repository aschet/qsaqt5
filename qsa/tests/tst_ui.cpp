#include <qsinputdialogfactory.h>
#include <qsinterpreter.h>
#include <qsobjectfactory.h>
#include <qsproject.h>
#include <qswrapperfactory.h>
#ifndef QSA_NO_IDE
#include <qsworkbench.h>
#endif

#include <QtGui/QPalette>
#include <QtTest/QtTest>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>

// the wrappers of the wrappers example
class ListViewWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ListViewWrapper(QListWidget *l) : listView(l) {}

public slots:
    QPalette palette() const { return listView->palette(); }
    void setPalette(const QPalette &palette) { listView->setPalette(palette); }

private:
    QListWidget *listView;
};

class ItemWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
public:
    explicit ItemWrapper(QListWidgetItem *i) : item(i) {}
    QString text() const { return item->text(); }
    void setText(const QString &txt) { item->setText(txt); }

private:
    QListWidgetItem *item;
};

class Wrappers : public QSWrapperFactory
{
public:
    Wrappers()
    {
        registerWrapper("QListWidget");
        registerWrapper("QListWidgetItem");
    }

    QObject *create(const QString &name, void *ptr) override
    {
        if (name == "QListWidget")
            return new ListViewWrapper(static_cast<QListWidget *>(ptr));
        if (name == "QListWidgetItem")
            return new ItemWrapper(static_cast<QListWidgetItem *>(ptr));
        return nullptr;
    }
};

class tst_Ui : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void buttonClick();
    void checkBoxToggle();
    void lineEditSignals();
    void sliderSignal();
    void comboBoxSignals();
    void scriptChangesWidgets();
    void wrappersExample();

    void dialogDefaults();
    void dialogAccepted();
    void dialogRejected();
    void dialogWidgets();
    void dialogLayout();
    void inputGetText();
    void inputGetNumber();
    void inputGetItem();
    void inputCancelled();
    void messageBoxes();

#ifndef QSA_NO_IDE
    void workbenchOpensAndShowsScripts();
#endif

private:
    QVariant value(const QString &code) { return ip->evaluate(code); }
    QString eval(const QString &code) { return ip->evaluate(code).toString(); }
    // runs the code of the dialog that is open while a modal event loop is running
    template <typename Handler> void whenModal(Handler handler)
    {
        QTimer::singleShot(200, this, [handler]() {
            QWidget *modal = QApplication::activeModalWidget();
            if (modal)
                handler(modal);
        });
    }

    QSInterpreter *ip = nullptr;
};

void tst_Ui::initTestCase()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                       QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/qsa-tst-ui");
}

void tst_Ui::init()
{
    ip = new QSInterpreter;
    ip->setErrorMode(QSInterpreter::Nothing);
    ip->addObjectFactory(new QSInputDialogFactory);
}

void tst_Ui::cleanup()
{
    delete ip;
    ip = nullptr;
}

void tst_Ui::buttonClick()
{
    QPushButton button("press");
    button.setObjectName("button");
    button.show();
    ip->evaluate("var clicks = 0; function onClick() { clicks++; }");
    ip->addTransientSignalHandler(&button, SIGNAL(clicked()), "onClick");

    QTest::mouseClick(&button, Qt::LeftButton);
    QTest::mouseClick(&button, Qt::LeftButton);
    QTest::keyClick(&button, Qt::Key_Space);
    QCOMPARE(ip->variable("clicks").toInt(), 3);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::checkBoxToggle()
{
    QCheckBox box("option");
    box.setObjectName("box");
    box.show();
    ip->evaluate("var states = ''; function onToggled(on) { states += on ? 'on;' : 'off;'; }");
    ip->addTransientSignalHandler(&box, SIGNAL(toggled(bool)), "onToggled");

    QTest::mouseClick(&box, Qt::LeftButton);
    QTest::mouseClick(&box, Qt::LeftButton);
    QCOMPARE(ip->variable("states").toString(), QString("on;off;"));
}

void tst_Ui::lineEditSignals()
{
    QLineEdit edit;
    edit.setObjectName("edit");
    edit.show();
    ip->evaluate("var last = ''; var count = 0; function onText(t) { last = t; count++; }");
    ip->addTransientSignalHandler(&edit, SIGNAL(textChanged(QString)), "onText");

    QTest::keyClicks(&edit, "abc");
    QCOMPARE(ip->variable("last").toString(), QString("abc"));
    QCOMPARE(ip->variable("count").toInt(), 3);
    edit.setText(QString::fromUtf8("\xc3\xa4\xe2\x82\xac"));
    QCOMPARE(ip->variable("last").toString(), QString::fromUtf8("\xc3\xa4\xe2\x82\xac"));
}

void tst_Ui::sliderSignal()
{
    QSlider slider(Qt::Horizontal);
    slider.setObjectName("slider");
    slider.setRange(0, 100);
    slider.show();
    ip->evaluate("var v = -1; function onValue(n) { v = n; }");
    ip->addTransientSignalHandler(&slider, SIGNAL(valueChanged(int)), "onValue");
    slider.setValue(42);
    QCOMPARE(ip->variable("v").toInt(), 42);
    QTest::keyClick(&slider, Qt::Key_Right);
    QCOMPARE(ip->variable("v").toInt(), 43);
}

void tst_Ui::comboBoxSignals()
{
    QComboBox combo;
    combo.setObjectName("combo");
    combo.addItems(QStringList() << "first" << "second" << "third");
    combo.show();
    ip->evaluate("var picked = ''; var index = -1; function onIndex(i) { index = i; } function onText(t) { picked = t; }");
    ip->addTransientSignalHandler(&combo, SIGNAL(currentIndexChanged(int)), "onIndex");
    ip->addTransientSignalHandler(&combo, SIGNAL(currentTextChanged(QString)), "onText");
    combo.setCurrentIndex(2);
    QCOMPARE(ip->variable("index").toInt(), 2);
    QCOMPARE(ip->variable("picked").toString(), QString("third"));
}

void tst_Ui::scriptChangesWidgets()
{
    QLineEdit edit;
    edit.setObjectName("edit");
    QCheckBox box;
    box.setObjectName("box");
    QSpinBox spin;
    spin.setObjectName("spin");
    spin.setRange(0, 1000);
    QComboBox combo;
    combo.setObjectName("combo");
    combo.addItems(QStringList() << "one" << "two");
    QPushButton button("x");
    button.setObjectName("button");
    button.setEnabled(true);
    QObjectList widgets;
    widgets << &edit << &box << &spin << &combo << &button;
    for (QObject *o : widgets)
        ip->addTransientObject(o);

    ip->evaluate("edit.text = 'from script'; box.checked = true; spin.value = 321;"
                 "combo.currentIndex = 1; button.enabled = false;");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(edit.text(), QString("from script"));
    QVERIFY(box.isChecked());
    QCOMPARE(spin.value(), 321);
    QCOMPARE(combo.currentText(), QString("two"));
    QVERIFY(!button.isEnabled());

    edit.setText("changed");
    spin.setValue(5);
    QCOMPARE(eval("edit.text + '/' + spin.value"), QString("changed/5"));
}

void tst_Ui::wrappersExample()
{
    QListWidget list;
    list.setObjectName("listView");
    list.addItems(QStringList() << "Red" << "Blue" << "Green");
    list.resize(200, 200);
    list.show();
    QVERIFY(QTest::qWaitForWindowExposed(&list));

    ip->addWrapperFactory(new Wrappers);
    ip->addTransientObject(&list);

    QFile test(QString(QSA_EXAMPLES_DIR) + "/wrappers/test.qs");
    QFile click(QString(QSA_EXAMPLES_DIR) + "/wrappers/click.qs");
    QVERIFY(test.open(QIODevice::ReadOnly));
    QVERIFY(click.open(QIODevice::ReadOnly));
    ip->evaluate(QString::fromUtf8(test.readAll()), 0, "test.qs");
    ip->evaluate(QString::fromUtf8(click.readAll()), 0, "click.qs");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));

    for (int i = 0; i < 2; ++i) {
        QListWidgetItem *item = list.item(i);
        const QString color = i == 0 ? "red" : "blue";
        const QRect rect = list.visualItemRect(item);
        QTest::mouseClick(list.viewport(), Qt::LeftButton, Qt::NoModifier, rect.center());
        QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
        QCOMPARE(item->text(), QString("Item clicked %1").arg(i));
        QCOMPARE(list.palette().color(QPalette::Active, QPalette::Base).name(), QColor(color).name());
    }
    QCOMPARE(ip->variable("clickCount").toInt(), 2);
}

void tst_Ui::dialogDefaults()
{
    eval("var dlg = new Dialog(); dlg.title = 'Title'; dlg.okButtonText = 'Go'; dlg.cancelButtonText = 'Stop'; dlg.width = 400;");
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("dlg.title"), QString("Title"));
    QCOMPARE(eval("dlg.okButtonText"), QString("Go"));
    QCOMPARE(eval("dlg.cancelButtonText"), QString("Stop"));
    QCOMPARE(eval("dlg.width"), QString("400"));
}

void tst_Ui::dialogAccepted()
{
    whenModal([](QWidget *w) { static_cast<QDialog *>(w)->accept(); });
    QVERIFY(ip->evaluate("var dlg = new Dialog(); dlg.exec()").toBool());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::dialogRejected()
{
    whenModal([](QWidget *w) { static_cast<QDialog *>(w)->reject(); });
    QVERIFY(!ip->evaluate("var dlg = new Dialog(); dlg.exec()").toBool());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::dialogWidgets()
{
    const QString build =
        "var dlg = new Dialog();"
        "dlg.title = 'Settings';"
        "var name = new LineEdit(); name.label = 'Name'; name.text = 'initial'; dlg.add(name);"
        "var amount = new NumberEdit(); amount.label = 'Amount'; amount.decimals = 2; amount.minimum = 0; amount.maximum = 100; amount.value = 12.5; dlg.add(amount);"
        "var count = new SpinBox(); count.label = 'Count'; count.minimum = 1; count.maximum = 9; count.value = 3; dlg.add(count);"
        "var flag = new CheckBox(); flag.text = 'Flag'; flag.checked = false; dlg.add(flag);"
        "var radio = new RadioButton(); radio.text = 'Radio'; radio.checked = false; dlg.add(radio);"
        "var choice = new ComboBox(); choice.label = 'Choice'; choice.itemList = ['a', 'b', 'c']; choice.currentItem = 'b'; dlg.add(choice);"
        "var notes = new TextEdit(); notes.text = 'some notes'; dlg.add(notes);"
        "var group = new GroupBox(); group.title = 'Group'; var inner = new LineEdit(); inner.text = 'in group'; group.add(inner); dlg.add(group);";
    eval(build);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));

    whenModal([](QWidget *w) {
        // the widgets of the dialog show the values the script has set
        QCOMPARE(w->findChildren<QSpinBox *>().value(0)->value(), 3);
        QVERIFY(!w->findChildren<QCheckBox *>().isEmpty());
        for (QLineEdit *edit : w->findChildren<QLineEdit *>())
            if (edit->text() == "initial")
                edit->setText("edited");
        w->findChildren<QSpinBox *>().value(0)->setValue(7);
        w->findChildren<QCheckBox *>().value(0)->setChecked(true);
        w->findChildren<QRadioButton *>().value(0)->setChecked(true);
        for (QComboBox *combo : w->findChildren<QComboBox *>())
            if (combo->findText("c") >= 0)
                combo->setCurrentText("c");
        w->findChildren<QTextEdit *>().value(0)->setPlainText("new notes");
        static_cast<QDialog *>(w)->accept();
    });
    QVERIFY(ip->evaluate("dlg.exec()").toBool());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));

    QCOMPARE(eval("name.text"), QString("edited"));
    QCOMPARE(eval("count.value"), QString("7"));
    QCOMPARE(eval("flag.checked"), QString("true"));
    QCOMPARE(eval("radio.checked"), QString("true"));
    QCOMPARE(eval("choice.currentItem"), QString("c"));
    QCOMPARE(eval("notes.text"), QString("new notes"));
    QCOMPARE(eval("inner.text"), QString("in group"));
    QCOMPARE(ip->evaluate("amount.value").toDouble(), 12.5);
}

void tst_Ui::dialogLayout()
{
    const QString build =
        "var dlg = new Dialog(); dlg.title = 'Layout';"
        "var label = new Label(); label.text = 'first line\\nsecond line'; label.toolTip = 'tip text'; dlg.add(label);"
        "var group = new GroupBox(); group.title = 'Group'; group.toolTip = 'group tip';"
        "var left = new LineEdit(); left.label = 'Left'; left.text = 'l'; group.add(left);"
        "group.newColumn();"
        "var right = new NumberEdit(); right.label = 'Right'; right.decimals = 2; right.value = 5.25; group.add(right);"
        "group.addSpace(10); dlg.add(group);"
        "dlg.newTab('Second'); dlg.addSpace(5);"
        "var day = new DateEdit(); day.label = 'Day'; day.date = new Date(2020, 3, 14); dlg.add(day);"
        "var time = new TimeEdit(); time.label = 'Time'; time.showSeconds = true; dlg.add(time);"
        "dlg.newColumn();"
        "var radioA = new RadioButton(); radioA.text = 'A'; radioA.checked = true; dlg.add(radioA);"
        "var radioB = new RadioButton(); radioB.text = 'B'; dlg.add(radioB);";
    eval(build);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(eval("label.text"), QString("first line\nsecond line"));
    QCOMPARE(eval("label.toolTip"), QString("tip text"));
    QCOMPARE(eval("group.toolTip"), QString("group tip"));
    QCOMPARE(eval("right.decimals"), QString("2"));

    whenModal([](QWidget *w) {
        QVERIFY(!w->findChildren<QLabel *>().isEmpty());
        QVERIFY(!w->findChildren<QTabWidget *>().isEmpty());
        QCOMPARE(w->findChildren<QRadioButton *>().size(), 2);
        static_cast<QDialog *>(w)->accept();
    });
    QVERIFY(ip->evaluate("dlg.exec()").toBool());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    QCOMPARE(ip->evaluate("right.value").toDouble(), 5.25);
    QCOMPARE(eval("day.date.getDate()"), QString("14"));
    QCOMPARE(eval("radioA.checked"), QString("true"));
    QCOMPARE(eval("radioB.checked"), QString("false"));
}

void tst_Ui::inputGetText()
{
    whenModal([](QWidget *w) {
        auto *dialog = qobject_cast<QInputDialog *>(w);
        QVERIFY(dialog);
        QCOMPARE(dialog->labelText(), QString("Your name"));
        QCOMPARE(dialog->textValue(), QString("preset"));
        dialog->setTextValue("typed");
        dialog->accept();
    });
    QCOMPARE(eval("Input.getText('Your name', 'preset', 'Ask')"), QString("typed"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::inputGetNumber()
{
    whenModal([](QWidget *w) {
        auto *dialog = qobject_cast<QInputDialog *>(w);
        QVERIFY(dialog);
        dialog->setDoubleValue(2.5);
        dialog->accept();
    });
    QCOMPARE(ip->evaluate("Input.getNumber('Amount', 1, 2, 0, 10, 'Number')").toDouble(), 2.5);

    whenModal([](QWidget *w) {
        auto *dialog = qobject_cast<QInputDialog *>(w);
        QVERIFY(dialog);
        dialog->setIntValue(8);
        dialog->accept();
    });
    QCOMPARE(ip->evaluate("Input.getNumber('Whole', 1, 0, 0, 10, 'Number')").toInt(), 8);
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::inputGetItem()
{
    whenModal([](QWidget *w) {
        auto *dialog = qobject_cast<QInputDialog *>(w);
        QVERIFY(dialog);
        QCOMPARE(dialog->comboBoxItems(), QStringList() << "red" << "green" << "blue");
        dialog->setTextValue("blue");
        dialog->accept();
    });
    QCOMPARE(eval("Input.getItem('Color', ['red', 'green', 'blue'], 'green', false, 'Pick')"), QString("blue"));
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::inputCancelled()
{
    whenModal([](QWidget *w) { w->close(); static_cast<QDialog *>(w)->reject(); });
    const QVariant result = value("Input.getText('Name', 'x')");
    QVERIFY(!result.isValid() || result.isNull() || result.toString().isEmpty());
    QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
}

void tst_Ui::messageBoxes()
{
    for (const char *call : {"information", "warning", "critical"}) {
        whenModal([](QWidget *w) { static_cast<QMessageBox *>(w)->accept(); });
        ip->evaluate(QString("MessageBox.%1('text', MessageBox.Ok, 0, 0, 'title')").arg(call));
        QVERIFY2(!ip->hadError(), qPrintable(ip->errorMessage()));
    }
}

#ifndef QSA_NO_IDE
void tst_Ui::workbenchOpensAndShowsScripts()
{
    QSProject project;
    project.interpreter()->setErrorMode(QSInterpreter::Nothing);
    QSScript *first = project.createScript("first.qs", "function one() { return 1; }");
    project.createScript("second.qs", "function two() { return 2; }");

    QSWorkbench workbench(&project);
    QWidget *window = workbench.widget();
    QVERIFY(window);
    QCOMPARE(workbench.project(), &project);

    workbench.open();
    QVERIFY(QTest::qWaitForWindowExposed(window));
    QVERIFY(window->isVisible());

    workbench.showScript(first);
    workbench.showFunction(project.script("second.qs"), "two");
    QVERIFY(!window->findChildren<QSEditor *>().isEmpty());
    QVERIFY(project.editors().size() >= 1);

    workbench.close();
    QVERIFY(!window->isVisible());
}
#endif

QTEST_MAIN(tst_Ui)

#include "tst_ui.moc"
