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

#include "addscriptdialog.h"
#include <QtWidgets/QFileDialog>
#include <QtGui/QPixmap>
#include <QtWidgets/QMessageBox>
#include "spreadsheet.h"

#include <qsscript.h>
#include <qsinterpreter.h>
#include <qsproject.h>

AddScriptDialog::AddScriptDialog(QWidget *parent)
: QDialog(parent)
{
    setupUi(this);
    connect(PushButton2, &QPushButton::clicked, this, &AddScriptDialog::reject);
    connect(ToolButton1, &QToolButton::clicked, this, &AddScriptDialog::choosePixmap);
    connect(PushButton1, &QPushButton::clicked, this, &AddScriptDialog::addScript);
    init();
}

void AddScriptDialog::init()
{
    // List all global functions of the project
    QSProject *project = ( (SpreadSheet*) parent() )->project;
    comboFunction->addItems(project->interpreter()->functions());
}

void AddScriptDialog::choosePixmap()
{
    QString f = QFileDialog::getOpenFileName();
    if ( f.isEmpty() )
	    return;
    QPixmap pix( f );
    labelPixmap->setPixmap( pix );
}

void AddScriptDialog::addScript()
{
    QSInterpreter *script = ( (SpreadSheet*) parent() )->interpreter;
    QString func = comboFunction->currentText();
    if (script->functions().indexOf(func) == -1) {
	QString msg = tr( "The function <b>%1</b> doesn't exist. "
			  "Do you want to add it?" ).arg( func );
	if ( QMessageBox::information( 0, tr( "Add Function" ), msg,
				       tr( "&Yes" ), tr( "&No" ),
				       "", 0, 1 ) == 0 ) {
 	    QSScript *sc = script->project()->script( "main.qs" );
	    if( !sc )
		sc = script->project()->createScript( "main.qs" );
	    sc->addFunction( func );
	    ( (SpreadSheet*) parent() )->showFunction( sc, func );
	}
    }

    emit newScript( func, editName->text(), labelPixmap->pixmap() );
    accept();
}
