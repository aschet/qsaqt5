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
#include "main.h"
#include <qsinterpreter.h>
#include <qsobjectfactory.h>
#include <qsproject.h>
#ifndef QSA_NO_IDE
#include <qsworkbench.h>
#endif
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

/* Below is a simple example that demonstrates how enums can be exported to
 * QSA. The is trivial and has no purpose other than to demonstrate the
 * required steps.
 *
 */

class Factory : public QSObjectFactory
{
public:
    Factory()
    {
        registerClass("Direction", &Direction::staticMetaObject, new DirectionStatic);
    }

    QObject *create(const QString &, const QVariantList &, QObject *)
    {
        return new Direction(interpreter());
    }
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#ifndef QSA_NO_IDE
    QSProject p;
    p.load("enums.qsa");
    QSWorkbench wb(&p);

    p.interpreter()->addObjectFactory(new Factory);

    wb.open();

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    QObject::connect(&p, SIGNAL(projectEvaluated()), &p, SLOT(save()));

    app.exec();
#else
    QMessageBox::information( 0, "Disabled feature",
			      "QSA Workbench has been disabled. Reconfigure to enable",
			      QMessageBox::Ok );
#endif
    return 0;
}
