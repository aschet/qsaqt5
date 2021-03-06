/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech AS. All rights reserved.
**
** This file is part of the QSA of the Qt Toolkit.
**
** For QSA Commercial License Holders (non-open source):
** 
** Licensees holding a valid Qt Script for Applications (QSA) License Agreement
** may use this file in accordance with the rights, responsibilities and
** obligations contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of the Licensing Agreement are
** not clear to you.
** 
** Further information about QSA licensing is available at:
** http://www.trolltech.com/products/qsa/licensing.html or by contacting
** info@trolltech.com.
** 
** 
** For Open Source Edition:  
** 
** This file may be used under the terms of the GNU General Public License
** version 2 as published by the Free Software Foundation and appearing in the
** file LICENSE.GPL included in the packaging of this file.  Please review the
** following information to ensure GNU General Public Licensing requirements
** will be met:  http://www.trolltech.com/products/qt/opensource.html 
** 
** If you are unsure which license is appropriate for your use, please review
** the following information:
** http://www.trolltech.com/products/qsa/licensing.html or contact the 
** sales department at sales@trolltech.com.

**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QSINPUTDIALOGFACTORY_P_H
#define QSINPUTDIALOGFACTORY_P_H

#include "qsinputdialogfactory.h"
#include "qsinterpreter.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtCore/QVariant>
#include <QtCore/QDateTime>
#include <QtWidgets/QDialog>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtGui/QValidator>
#include <QtWidgets/QToolTip>

#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QButtonGroup>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
extern bool qsa_is_non_gui_thread();


/*!
  \class QSInputDialogFactory qsinputdialogfactory.h

  \brief The QSInputDialogFactory class extends QSA with a basic and
  easy-to-use input dialog framework.

  To extend the interpreter with the Input Dialog Framework you need
  to create an instance of the QSInputDialogFactory and add it to the
  interpreter using the function
  QSInterpreter::addObjectFactory(). For example:

  \code
  QSProject proj;
  QSInterpreter *ip = proj->interpreter();
  ip->addObjectFactory(new QSInputDialogFactory);
  \endcode

  The script extensions provided by the QSInputDialogFramework are
  described in detail in \l {QSA Input Dialog Framework}.

  Note on threading; If the Input Dialog Factory is used with an
  interpreter running in the non GUI thread, all functionality is
  disabled.
*/


/*!
  \fn QSInputDialogFactory::QSInputDialogFactory()

  Creates the input dialog factory. Use the function
  QSInterpreter::addObjectFactory to make the objects this factory
  represents to an interpreter.
*/


/*!
  \fn QObject *QSInputDialogFactory::create(const QString &,
  const QVariantList &, QObject *)
  \internal
*/


class QSInput : public QObject
{
    Q_OBJECT
    Q_OVERRIDE(QCString name SCRIPTABLE false)
public:
    QSInput() : QObject(0)
    {
        setObjectName(QLatin1String("Input"));
    }

public slots:
    QVariant getText(const QString &label = QString(),
		     const QString &text = QString(),
		     const QString &title = QString(),
		     QWidget *parent = 0);
    QVariant getNumber(const QString &label = QString(),
		       double value = 0,
		       int decimals = 0,
		       double minValue = -2147483647,
		       double maxValue = 2147483647,
		       const QString &title = QString(),
		       QWidget *parent = 0);
    QVariant getItem(const QString &label,
		     const QStringList &itemList,
		     const QString &currentItem = QString(),
		     bool editable = false,
		     const QString &title = QString(),
		     QWidget *parent = 0);
    QVariant getItem(const QStringList &itemList,
		      const QString &currentItem = QString(),
		      bool editable = false,
		      QWidget *parent = 0) {
	return getItem(QString(), itemList, currentItem, editable, QString(), parent);
    }
};


class QSFileDialog : public QObject
{
    Q_OBJECT
    Q_OVERRIDE(QCString name SCRIPTABLE false)

public:
    QSFileDialog() : QObject(0)
    {
        setObjectName(QLatin1String("FileDialog"));
    }

public slots:
    QVariant getOpenFileName(const QString &filter = QString(),
			      const QString &title = QString(),
			      QWidget *parent = 0);
    QVariant getSaveFileName(const QString &filter = QString(),
			      const QString &title = QString(),
			      QWidget *parent = 0);
    QVariant getExistingDirectory(const QString &dir = QString(),
				   const QString &title = QString(),
				   QWidget *parent = 0);
    QStringList getOpenFileNames(const QString &dir = QString(),
				  const QString &filter = QString(),
				  const QString &title = QString(),
				  QWidget *parent = 0);
private:
    QString cap;
};


class QSMessageBox : public QObject
{
    Q_OBJECT
    Q_OVERRIDE(QCString name SCRIPTABLE false)
    Q_ENUMS(ButtonType)
public:
    enum ButtonType { NoButton, Ok, Cancel, Yes, No, Abort,
		      Retry, Ignore };

    QSMessageBox() : QObject(0)
    {
        setObjectName(QLatin1String("MessageBox"));
    }

public slots:
    int information(const QString &text,
		     ButtonType button0 = Ok,
		     ButtonType button1 = NoButton,
		     ButtonType button2 = NoButton,
		     const QString &title = QString(),
		     QWidget *parent = 0);
// QMessageBox::question is not part of Qt 3.1
/*
    QSMessageBox::ButtonType question(const QString &text,
				       ButtonType button0 = Yes,
				       ButtonType button1 = No,
				       ButtonType button2 = NoButton);
*/
    int warning(const QString &text,
		 ButtonType button0 = Retry,
		 ButtonType button1 = Abort,
		 ButtonType button2 = NoButton,
		 const QString &title = QString(),
		 QWidget *parent = 0);

    int critical(const QString &text,
		  ButtonType button0 = Retry,
		  ButtonType button1 = NoButton,
		  ButtonType button2 = NoButton,
		  const QString &title = QString(),
		  QWidget *parent = 0);

private:
    QString cap;
};


class QSWidget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis)
    Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip)
    Q_OVERRIDE(QCString name SCRIPTABLE false)
public:
    QSWidget(QWidget *w = 0) : widget(w) {}
    QWidget *widget;
    QString whatsThis() const;
    void setWhatsThis(const QString &text) const;
    QString toolTip() const;
    void setToolTip(const QString &text) const;
};

#define QS_WIDGET(Class) \
 inline Q##Class *d() const { return (Q##Class*)widget; }


class QSLabel : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    inline QLabel *d() const { return (QLabel *) widget; }
public:
    QSLabel() : QSWidget(new QLabel(0)) {}
    QString text() const
    { return d()->text(); }
    void setText(const QString &txt)
    { d()->setText(txt); }
};

class QSLabeled : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)
public:
    QSLabeled(const QString& label, QWidget *w);
    inline QString label() const { return labelWidget->text(); }
    void setLabel(const QString &txt);
    QLabel *labelWidget;
};

class QSLineEdit : public QSLabeled
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    QS_WIDGET(LineEdit)
public:
    QSLineEdit() : QSLabeled(QSInput::tr("Text:"),  new QLineEdit(0)) {}
    QString text() const
    { return d()->text(); }
    void setText(const QString &txt)
    { d()->setText(txt); }
};

class QSNumberEdit : public QSLabeled
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(double decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    QS_WIDGET(LineEdit)
public:
    QSNumberEdit() : QSLabeled(QSInput::tr("Value:"), new QLineEdit(0)), validator(new QDoubleValidator(widget))
    {
	d()->setValidator(validator);
	validator->setDecimals(0);
    }
    double value() const
    { return d()->text().toDouble(); }
    void setValue(double val)
    { d()->setText(QString::number(val)); }
    double decimals() const
    { return validator->decimals(); }
    void setDecimals(double decimals)
    { validator->setDecimals(int(decimals)); }
    double minimum() const
    { return validator->bottom(); }
    void setMinimum(double minimum)
    { validator->setBottom(minimum); }
    double maximum() const
    { return validator->top(); }
    void setMaximum(double maximum)
    { validator->setBottom(maximum); }
private:
    QDoubleValidator *validator;
};


class QSDateEditEnums : public QObject
{
    Q_OBJECT
    Q_ENUMS(Order)
    Q_OVERRIDE(QCString name SCRIPTABLE false)
public:
    enum Order { DMY, MDY, YMD, YDM };
};


class QSDateEdit : public QSLabeled
{
    Q_OBJECT
    Q_ENUMS(Order)
    Q_PROPERTY(int order READ order WRITE setOrder)
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(QDate minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(QDate maximum READ maximum WRITE setMaximum)
    QS_WIDGET(DateEdit)
public:
    enum Order { DMY, MDY, YMD, YDM };
    QSDateEdit() : QSLabeled(tr("Date:"), new QDateEdit(0))
    { }

    int order() const
    {
        QString format = d()->displayFormat();
        if (format == "dd.MM.yyyy") return DMY;
        else if (format == "MM.dd.yyyy") return MDY;
        else if (format == "yyyy.MM.dd") return YMD;
        else if (format == "yyyy.dd.MM") return YDM;
        return -1;;
    }

    void setOrder(int order)
    {
        if (order == DMY) d()->setDisplayFormat("dd.MM.yyyy");
        else if (order == MDY) d()->setDisplayFormat("MM.dd.yyyy");
        else if (order == YMD) d()->setDisplayFormat("yyyy.MM.dd");
        else if (order == YDM) d()->setDisplayFormat("yyyy.dd.MM");
    }

    QDate date() const { return d()->date(); }
    void setDate(QDate date) { d()->setDate(date); }
    QDate minimum() const { return d()->minimumDate(); }
    void setMinimum(const QDate &minimum) { d()->setMinimumDate(minimum); }
    QDate maximum() const { return d()->maximumDate(); }
    void setMaximum(const QDate &maximum) { d()->setMaximumDate(maximum); }
};

class QSTimeEdit : public QSLabeled
{
    Q_OBJECT
    Q_PROPERTY(bool showSeconds READ seconds WRITE setSeconds)
    Q_PROPERTY(bool showAMPM READ ampm WRITE setAmpm)
    Q_PROPERTY(QTime time READ time WRITE setTime)
    Q_PROPERTY(QTime minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(QTime maximum READ maximum WRITE setMaximum)
    QS_WIDGET(TimeEdit)
public:
    QSTimeEdit() : QSLabeled(tr("Time:"), new QTimeEdit(0))
    { }

    void updateDisplayFormat(bool ampm, bool secs)
    {
        QString baseFormat = "HH::mm";
        if (ampm)
            baseFormat = "AP" + baseFormat;
        if (secs)
            baseFormat += ":ss";
        d()->setDisplayFormat(baseFormat);
    }

    bool seconds() const { return d()->displayFormat().contains("ss"); }
    void setSeconds(bool b) { updateDisplayFormat(ampm(), b); }

    bool ampm() const { return d()->displayFormat().toLower().contains("ap"); }
    void setAmpm(bool b) { updateDisplayFormat(b, seconds()); }

    QTime time() const { return d()->time(); }
    void setTime(QTime time) { d()->setTime(time); }

    QTime minimum() const { return d()->minimumTime(); }
    void setMinimum(const QTime &minimum) { d()->setMinimumTime(minimum); }

    QTime maximum() const { return d()->maximumTime(); }
    void setMaximum(const QTime &maximum) { d()->setMaximumTime(maximum); }
};

class QSTextEdit : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    QS_WIDGET(TextEdit)
public:
    QSTextEdit() : QSWidget(new QTextEdit(0))
    { }
    QString text() const
    { return d()->toPlainText(); }
    void setText(const QString &txt)
    { d()->setPlainText(txt); }
};

class QSSpinBox : public QSLabeled
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    QS_WIDGET(SpinBox)
public:
    QSSpinBox() : QSLabeled(QSInput::tr("Value:"), new QSpinBox(0)) {}
    int value() const
    { return d()->value(); }
    void setValue(int val)
    { d()->setValue(val); }
    int minimum() const
    { return d()->value(); }
    void setMinimum(int minimum)
    { d()->setMinimum(minimum); }
    int maximum() const
    { return d()->value(); }
    void setMaximum(int maximum)
    { d()->setMaximum(maximum); }
};

class QSCheckBox : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    QS_WIDGET(CheckBox)
public:
    QSCheckBox() : QSWidget(new QCheckBox(0)) {}
    QString text() const
    { return d()->text(); }
    void setText(const QString &txt)
    { d()->setText(txt); }

    bool isChecked() const
    { return d()->isChecked(); }
    void setChecked(bool b)
    { d()->setChecked(b); }
};


class QSRadioButton : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    QS_WIDGET(RadioButton)
public:
    QSRadioButton() : QSWidget(new QRadioButton(0)) {}
    QString text() const
    { return d()->text(); }
    void setText(const QString &txt)
    { d()->setText(txt); }

    bool isChecked() const
    { return d()->isChecked(); }
    void setChecked(bool b)
    { d()->setChecked(b); }
};

class QSComboBox : public QSLabeled
{
    Q_OBJECT
    Q_PROPERTY(QStringList itemList READ itemList WRITE setItemList)
    Q_PROPERTY(QString currentItem READ currentItem WRITE setCurrentItem)
    Q_PROPERTY(bool editable READ isEditable WRITE setEditable)
    QS_WIDGET(ComboBox)
public:
    QSComboBox() : QSLabeled(QSInput::tr("Item:"), new QComboBox(0))
    {
        setEditable(false);
    }
    QString currentItem() const
    { return d()->currentText(); }
    void setCurrentItem(const QString &txt)
    {
        int idx = d()->findText(txt);
        if (idx >= 0)
            d()->setCurrentIndex(idx);
    }
    bool isEditable() const
    { return d()->isEditable(); }
    void setEditable(bool b)
    { d()->setEditable(b); }
    QStringList itemList() const;
    void setItemList(const QStringList &l)
    {
	d()->clear();
	d()->insertItems(0, l);
    }
};


class QSGroupBox : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    QS_WIDGET(GroupBox)
public:
    QSGroupBox();
    QString title() const
    { return d()->title(); }
    void setTitle(const QString &title)
    { d()->setTitle(title); }
public slots:
    void add(QSWidget *widget);
    void newColumn();
    void addSpace(int space);
private:
    QButtonGroup *invisibleButtonGroup;
    QHBoxLayout *hbox;
    QGridLayout *grid;
};

class QSDialogPrivate;
class QSDialog : public QSWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(QString okButtonText READ okButtonText WRITE setOkButtonText)
    Q_PROPERTY(QString cancelButtonText READ cancelButtonText WRITE setCancelButtonText)
    QSDialogPrivate *d;
public:
    QSDialog(const QString &caption = QString(), QWidget *parent=0);
    ~QSDialog();

    void setTitle(const QString &title);
    QString title() const;

    void setWidth(int width);
    int width() const;

    void setOkButtonText(const QString &text);
    QString okButtonText() const;

    void setCancelButtonText(const QString &text);
    QString cancelButtonText() const;

public slots:
    void newTab(const QString &label);
    void newColumn();
    void addSpace(int space);
    void add(QSWidget *widget);
    bool exec();

};

class QSDialogPrivate : public QDialog
{
public:
    QSDialogPrivate(QWidget *parent=0);
    int width;
    QSize sizeHint() const { return QDialog::sizeHint().expandedTo(QSize(width, 0)); }
    QWidget *lastWidget;

    QHBoxLayout *hbox;
    QGridLayout *grid;

    QButtonGroup *invisibleButtonGroup;
    QTabWidget *tabWidget;
    QGroupBox *groupBox;

    QHBoxLayout *buttonRow;
    void fixTabOrder();

    QPushButton *okButton, *cancelButton;
    QWidget *parent;

    void addSpace(int space);
    void add(QSWidget *widget);
};

#endif
