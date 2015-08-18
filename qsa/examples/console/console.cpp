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

#include "console.h"

#include <qsinputdialogfactory.h>
#include <qsutilfactory.h>

#include <QtCore/QEvent>
#include <QtWidgets/QApplication>
#include <QtCore/QMetaObject>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QMessageBox>
#ifndef QSA_NEW_EDITOR
// TODO: QSAQt5 - fix Qt3 usage
#   include <Q3TextEdit>
#endif

#include <stdio.h>
#include <stdlib.h>

static QTextEdit *debugoutput = 0;

void debugMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString s(msg);

    if (type != QtFatalMsg) {
        if (debugoutput)
            debugoutput->append(s + "\n");
    } else {
        fprintf(stderr, "%s", msg.toLatin1().constData());
        abort();
    }

    qApp->flush();
}

Console::Console(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    interpreter = new QSInterpreter(this);
    interpreter->setErrorMode(QSInterpreter::Nothing);

    editInput->setInterpreter(interpreter);

    // grant access to low level Qt API for demonstration purposes
    interpreter->addObjectFactory(new QSInputDialogFactory);
    interpreter->addObjectFactory(new QSUtilFactory);

    QWidget *w = editInput->textEdit();
    w->installEventFilter(this);
#if defined(QSA_NEW_EDITOR)
    static_cast<QTextEdit *>(w)->viewport()->installEventFilter(this);
#else
    static_cast<Q3TextEdit *>(w)->viewport()->installEventFilter(this);
#endif
    w->setFocus(Qt::OtherFocusReason);
    index = 0;
    debugoutput = output;
	qInstallMessageHandler(debugMessageOutput);
    connect(interpreter, SIGNAL(error(const QString &, const QString &, int)),
            this, SLOT(error(const QString &, const QString &, int)));
}

bool Console::eventFilter( QObject *o, QEvent *e )
{
    if (o != editInput->textEdit() && o != editInput->textEdit()->viewport())
        return false;

    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        switch (ke->key()) {
            case Qt::Key_Return:
            case Qt::Key_Enter:
				if (ke->modifiers() & Qt::ControlModifier) {
					editInput->textEdit()->setText(editInput->textEdit()->toPlainText() + "\n\r");

                    // This is a hack to place the cursor at the end of the text edit
                    // and just use the public API for QSEditor.
                    editInput->selectAll();
                    editInput->cut();
                    editInput->paste();
                } else {
                    QString code = editInput->text();
                    if (code.length() > 1 && code.at(0) == QLatin1Char('?'))
                        code = "debug(" + code.mid(1) + ");";

                    if (!interpreter->checkSyntax(code)) {
                    editInput->textEdit()->setText(editInput->textEdit()->toPlainText() + "\n\r");

                    // This is a hack to place the cursor at the end of the text edit
                    // and just use the public API for QSEditor.
                    editInput->selectAll();
                    editInput->cut();
                    editInput->paste();
#if !defined(QSA_NEW_EDITOR)
                        return true;
#endif
                    }
                    QVariant value = interpreter->evaluate(code);
                    QString tn;
                    switch(value.type()) {
                        case QMetaType::QObjectStar:
                            tn = QString("%1 [%2]").arg((qvariant_cast<QObject *>(value))->objectName())
                                                   .arg((qvariant_cast<QObject *>(value))->metaObject()->className());
                            break;
                        case QMetaType::VoidStar:
                            tn = QString("0x%1 [void*]").arg((ulong) qvariant_cast<void *>(value), 16);
                            break;
                        case QVariant::Invalid:
                            break;
                        default:
                            if (!value.toString().isEmpty())
                                tn = value.toString() + " ["
                                    + (value.type() == QVariant::Double ? "Number" :value.typeName())
                                    + "]";
                            break;
                    }

                    if(!tn.isEmpty())
                        debugoutput->append(tn);
                    history.append(editInput->text());
                    index = history.count();
                    historyView->append(editInput->text());
                    editInput->setText("");
                }
                return true;
            case Qt::Key_Up:
				if (ke->modifiers() & Qt::ControlModifier) {
                    if (index > 0) {
                        index--;
                        editInput->setText(history.at(index));
                    }
                    return true;
                }
                break;
            case Qt::Key_Down:
				if (ke->modifiers() & Qt::ControlModifier) {
                    if (index < history.count() - 1) {
                        index++;
                        editInput->setText(history.at(index));
                    } else {
                        editInput->setText("");
                    }
                    return true;
                }
                break;
            case Qt::Key_Escape:
                ke->ignore();
                return true;
        }
    }
    return false;
}


void Console::error( const QString &msg, const QString &, int line )
{
    debugoutput->append("<b>Error in line " + QString::number(line) + ":</b><pre><font color=red>" + msg + "</font></pre>");
}
