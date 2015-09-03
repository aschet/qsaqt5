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

#include "qsinputdialogfactory_p.h"

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

QVariant QSInput::getText(const QString &label, const QString &text, const QString &title,
			  QWidget *parent)
{
    bool ok;
    QString lab = label;
    if (lab.isEmpty())
	lab = tr("Text:");
    QString res = QInputDialog::getText(parent ? parent : qApp->activeWindow(), title,
                                        lab, QLineEdit::Normal, text, &ok);

    return (ok ? QVariant(res) : QVariant());
}

QVariant QSInput::getNumber(const QString &label, double value,
			    int decimals, double minValue, double maxValue,
			    const QString &title, QWidget *parent)
{
    QString lab = label;
    if (lab.isEmpty())
	lab = tr("Number:");
    bool ok;
    if (decimals > 0) {
	double d = QInputDialog::getDouble(parent ? parent : qApp->activeWindow(), title, lab,
                                       value, minValue, maxValue, decimals, &ok);
	return (ok ? QVariant(d) : QVariant());
    }
    int i = QInputDialog::getInt(parent ? parent : qApp->activeWindow(), title, lab, int(value),
				      int(minValue), int(maxValue), 1, &ok);
    return (ok ? QVariant(i) : QVariant());
}


QVariant QSInput::getItem(const QString &label,
			  const QStringList &itemList,
			  const QString &currentItem,
			  bool editable,
			  const QString &title,
			  QWidget *parent)
{
    QString lab = label;
    if (lab.isEmpty())
	lab = tr("Item:");
    int idx = 0;
    if (!currentItem.isEmpty())
	idx = itemList.indexOf(currentItem);
    bool ok;
    QString res = QInputDialog::getItem(parent ? parent : qApp->activeWindow(), title,
                                        lab, itemList, qMax(idx,0), editable, &ok);
    return (ok ?  QVariant(res) : QVariant());
}


QVariant QSFileDialog::getOpenFileName(const QString &filter, const QString &title,
					QWidget *parent)
{
    QString str = QFileDialog::getOpenFileName(parent ? parent : qApp->activeWindow(), title, QString::null, filter,
						                       0);
    return str.isNull() ? QVariant() : QVariant(str);
}

QVariant QSFileDialog::getSaveFileName(const QString &filter, const QString &title,
					QWidget *parent)
{
    QString str = QFileDialog::getSaveFileName(parent ? parent : qApp->activeWindow(), title, QString::null, filter,
                                               0);
    return str.isNull() ? QVariant() : QVariant(str);
}

QVariant QSFileDialog::getExistingDirectory(const QString &dir, const QString &title,
					     QWidget *parent)
{
    QString str =  QFileDialog::getExistingDirectory(parent ? parent : qApp->activeWindow(), title, dir);
    return str.isNull() ? QVariant() : QVariant(str);
}

QStringList QSFileDialog::getOpenFileNames(const QString &dir,
					    const QString &filter,
					    const QString &title,
					    QWidget *parent)
{
    return QFileDialog::getOpenFileNames(parent ? parent : qApp->activeWindow(), title, filter, dir, 0);
}


int QSMessageBox::information(const QString &text,
			       ButtonType button0,
			       ButtonType button1,
			       ButtonType button2,
			       const QString &title,
			       QWidget *parent)
{
    return QMessageBox::information(parent ? parent : qApp->activeWindow(),
				     title, text, button0, button1, button2);
}
/*
QSMessageBox::ButtonType QSMessageBox::question(const QString &text,
						 ButtonType button0,
						 ButtonType button1,
						 ButtonType button2)
{
    return (QSMessageBox::ButtonType) QMessageBox::question(qApp->activeWindow(),
							     cap, text,
							     button0, button1, button2);
}
*/
int QSMessageBox::warning(const QString &text,
			   ButtonType button0,
			   ButtonType button1,
			   ButtonType button2,
			   const QString &title,
			   QWidget *parent)
{
    return QMessageBox::warning(parent ? parent : qApp->activeWindow(), title, text, button0, button1, button2);
}

int QSMessageBox::critical(const QString &text,
			    ButtonType button0,
			    ButtonType button1,
			    ButtonType button2,
			    const QString &title,
			    QWidget *parent)
{
    return QMessageBox::critical(parent ? parent : qApp->activeWindow(), title, text, button0, button1, button2);
}


QString QSWidget::whatsThis() const
{
    return widget->whatsThis();
}

void QSWidget::setWhatsThis(const QString &text) const
{
    widget->setWhatsThis(text);
}

QString QSWidget::toolTip() const
{
    return widget->toolTip();
}

void QSWidget::setToolTip(const QString &text) const
{
    widget->setToolTip(text);
}


void QSLabeled::setLabel(const QString &txt)
{
    labelWidget->setText(txt);
    if(txt.isEmpty())
	labelWidget->hide();
}

QSLabeled::QSLabeled(const QString& label, QWidget *w)
    : QSWidget(w), labelWidget(new QLabel(label,0))
{
    labelWidget->setBuddy(w);
}

QStringList QSComboBox::itemList() const
{
    QStringList l;
    for (int i = 0; i < d()->count(); ++i)
	l << d()->itemText(i);
    return l;
}

QSGroupBox::QSGroupBox()
    : QSWidget(new QGroupBox), invisibleButtonGroup(0)
{
    hbox = new QHBoxLayout(d());
    grid = new QGridLayout();

    hbox->addLayout(grid);
    grid->setAlignment(Qt::AlignTop);
}

void QSGroupBox::add(QSWidget *widget)
{
    QWidget *w = widget->widget;

    int row = grid->rowCount();
    if (qobject_cast<QSLabeled *>(widget)) {
	QLabel *label = ((QSLabeled*)widget)->labelWidget;
 	grid->addWidget(label, row, 0);
 	grid->addWidget(w, row, 1);
	label->setVisible(!label->text().isEmpty());
    } else {
	grid->addWidget(w, row, 0, 1, 2);
    }

    if (w && qobject_cast<QRadioButton *>(w)) {
	if (!invisibleButtonGroup)
	    invisibleButtonGroup = new QButtonGroup(d());
	invisibleButtonGroup->addButton(qobject_cast<QRadioButton *>(w));
    }

}

void QSGroupBox::addSpace(int space)
{
    QSpacerItem *spacer = new QSpacerItem(0, qMax(space,0), QSizePolicy::Fixed, QSizePolicy::Fixed);
    grid->addItem(spacer, grid->rowCount(), 1);
    invisibleButtonGroup = 0;
}

void QSGroupBox::newColumn() {
    if (grid->rowCount()) {
	hbox->addSpacing(17);
	grid = new QGridLayout;
    grid->setAlignment(Qt::AlignTop);
    hbox->addLayout(grid);
    }
}


QSDialogPrivate::QSDialogPrivate(QWidget *parent)
    : QDialog(parent),
      width(0), lastWidget(0),
     invisibleButtonGroup(0), tabWidget(0), groupBox(0)
{
    this->parent = this;

    QVBoxLayout *vbox = new QVBoxLayout(this);
    setLayout(vbox);

    hbox = new QHBoxLayout;
    vbox->addLayout(hbox);

    grid = new QGridLayout;
    hbox->addLayout(grid);
    grid->setAlignment(Qt::AlignTop);

    okButton = new QPushButton(QMessageBox::tr("OK"), this);
    okButton->setDefault(true);
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    cancelButton = new QPushButton(QMessageBox::tr("Cancel"), this);
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    buttonRow = new QHBoxLayout;
    vbox->addLayout(buttonRow);
    buttonRow->addStretch(10);
    buttonRow->addWidget(okButton);
    buttonRow->addWidget(cancelButton);
}

void QSDialogPrivate::fixTabOrder()
{
    if (lastWidget) {
	if (lastWidget) {
	    QWidget::setTabOrder(lastWidget, okButton);
	    QWidget::setTabOrder(okButton, cancelButton);
	}
	layout()->activate();
	lastWidget = 0;
    }
}

void QSDialogPrivate::addSpace(int space)
{
    QSpacerItem *spacer = new QSpacerItem(0, qMax(space,0), QSizePolicy::Fixed, QSizePolicy::Fixed);
    grid->addItem(spacer, grid->rowCount(), 1);
    invisibleButtonGroup = 0;
}

void QSDialogPrivate::add(QSWidget *widget)
{
    QWidget *w = widget->widget;

    int row = grid->rowCount();
    if (qobject_cast<QSLabeled *>(widget)) {
	QLabel *label = ((QSLabeled*)widget)->labelWidget;
	label->setVisible(!label->text().isEmpty());
 	grid->addWidget(label, row, 0);
 	grid->addWidget(w, row, 1);
    } else {
	grid->addWidget(w, row, 0,  1, 2);
    }

    if (w && qobject_cast<QRadioButton *>(w)) {
	if (!invisibleButtonGroup)
	    invisibleButtonGroup = new QButtonGroup(this);
	invisibleButtonGroup->addButton(qobject_cast<QRadioButton *>(w));
    }

    lastWidget = w;
}

QSDialog::QSDialog(const QString &title, QWidget *parent)
{
    d = new QSDialogPrivate(parent);
    widget = d;
    if (!title.isEmpty())
	setTitle(title);
}

QSDialog::~QSDialog()
{
    delete d;
}

void QSDialog::setTitle(const QString &title) { d->setWindowTitle(title); }
QString QSDialog::title() const { return d->windowTitle(); }
void QSDialog::setWidth(int width){ d->width = width; }
int QSDialog::width() const { return d->width; }
void QSDialog::setOkButtonText(const QString &text) { d->okButton->setText(text); }
QString QSDialog::okButtonText() const { return d->okButton->text(); }
void QSDialog::setCancelButtonText(const QString &text) { d->cancelButton->setText(text); }
QString QSDialog::cancelButtonText() const { return d->cancelButton->text(); }

void QSDialog::newTab(const QString &label)
{
    if (!d->tabWidget) {
	d->tabWidget = new QTabWidget(d);
	int row = d->grid->rowCount();
	d->grid->addWidget(d->tabWidget, row, 0, 1, 2);
    }
    QWidget *w = new QWidget;
    d->tabWidget->addTab(w, label);
    d->parent = w;
    d->hbox = new QHBoxLayout(w);
    d->grid = new QGridLayout(0);
    d->hbox->addLayout(d->grid);
    d->grid->setAlignment(Qt::AlignTop);
}

void QSDialog::newColumn()
{
    if (d->grid->rowCount()) {
	d->hbox->addSpacing(17);
	d->grid = new QGridLayout(0);
    d->hbox->addLayout(d->grid);
	d->grid->setAlignment(Qt::AlignTop);
    }
}

void QSDialog::addSpace(int space)
{
    d->addSpace(space);
}

void QSDialog::add(QSWidget *widget)
{
    d->add(widget);
}

bool QSDialog::exec()
{
    d->fixTabOrder();
    int res = d->exec();
    return (res == QDialog::Accepted);
}


QSInputDialogFactory::QSInputDialogFactory()
{
    if (qsa_is_non_gui_thread()) {
	qWarning("QSInputDialogfactory::QSInputDialogFactory(), "
		 "factory cannot be used in non GUI thread");
	return;
    }
    registerClass(QString::fromLatin1("Dialog"), &QSDialog::staticMetaObject);
    registerClass(QString::fromLatin1("Label"), &QSLabel::staticMetaObject);
    registerClass(QString::fromLatin1("LineEdit"), &QSLineEdit::staticMetaObject);
    registerClass(QString::fromLatin1("NumberEdit"), &QSNumberEdit::staticMetaObject);
    registerClass(QString::fromLatin1("DateEdit"), &QSDateEdit::staticMetaObject,
                  new QSDateEditEnums);
    registerClass(QString::fromLatin1("TimeEdit"), &QSTimeEdit::staticMetaObject);
    registerClass(QString::fromLatin1("TextEdit"), &QSTextEdit::staticMetaObject);
    registerClass(QString::fromLatin1("SpinBox"), &QSSpinBox::staticMetaObject);
    registerClass(QString::fromLatin1("CheckBox"), &QSCheckBox::staticMetaObject);
    registerClass(QString::fromLatin1("RadioButton"), &QSRadioButton::staticMetaObject);
    registerClass(QString::fromLatin1("ComboBox"), &QSComboBox::staticMetaObject);
    registerClass(QString::fromLatin1("GroupBox"), &QSGroupBox::staticMetaObject);
    registerClass(QString::fromLatin1("MessageBox"), 0, new QSMessageBox());
    registerClass(QString::fromLatin1("FileDialog"), 0, new QSFileDialog());
    registerClass(QString::fromLatin1("Input"), 0, new QSInput());
}

QObject *QSInputDialogFactory::create(const QString &className,
                                      const QVariantList &arguments,
                                      QObject * /*context*/)
{
    if (qsa_is_non_gui_thread()) {
	qWarning("QSInputDialogfactory::create(), "
		 "factory cannot be used in non GUI thread");
	return 0;
    }

    if (className == QString::fromLatin1("Dialog")) {
	QString title = arguments.size() >= 1 ? qvariant_cast<QString>(arguments[0]) : QString();
	QObject *obj = arguments.size() >= 2 ? qvariant_cast<QObject *>(arguments[1]) : 0;
	QWidget *widget = obj && qobject_cast<QWidget *>(obj) ? (QWidget*) obj : 0;
	return new QSDialog(title, widget);
    } else if (className == QString::fromLatin1("Label")) {
	return new QSLabel;
    } else if (className == QString::fromLatin1("LineEdit")) {
	return new QSLineEdit;
    } else if (className == QString::fromLatin1("NumberEdit")) {
	return new QSNumberEdit;
    } else if (className == QString::fromLatin1("DateEdit")) {
	return new QSDateEdit;
    } else if (className == QString::fromLatin1("TimeEdit")) {
	return new QSTimeEdit;
    } else if (className == QString::fromLatin1("TextEdit")) {
	return new QSTextEdit;
    } else if (className == QString::fromLatin1("SpinBox")) {
	return new QSSpinBox;
    } else if (className == QString::fromLatin1("CheckBox")) {
	return new QSCheckBox;
    } else if (className == QString::fromLatin1("RadioButton")) {
	return new QSRadioButton;
    } else if (className == QString::fromLatin1("ComboBox")) {
	return new QSComboBox;
    } else if (className == QString::fromLatin1("GroupBox")) {
	return new QSGroupBox;
    }
    return 0;
}
