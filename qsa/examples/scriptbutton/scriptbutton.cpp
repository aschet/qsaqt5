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
#include "scriptbutton.h"

#include <qsinterpreter.h>
#include <qseditor.h>
#include <QtWidgets/QMenu>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLayout>
#include <QtGui/QContextMenuEvent>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QKeyEvent>

#ifndef QSA_NO_EDITOR

class ScriptEditor : public QDialog
{
public:
    ScriptEditor( QSProject *proj, QWidget *parent = 0, const char *name = 0 );
    void setCode( const QString &c );
    QString code() const { return ed->text(); }

protected:
    void keyPressEvent( QKeyEvent *e ) {
	if ( e->key() == Qt::Key_Escape ) { // let the editor handle the ESC key
	    e->ignore();
	    return;
	}
	QDialog::keyPressEvent( e );
    }

private:
    QSEditor *ed;
};

ScriptEditor::ScriptEditor( QSProject *proj, QWidget *parent, const char *name )
    : QDialog( parent)
{
    setObjectName(name);
    QString scName = QString( "script%1.qs" ).arg( proj->scripts().count() );
    ed = proj->createEditor( proj->createScript( scName ), this );
    QPushButton *ok = new QPushButton( "&OK" );
    QPushButton *cancel = new QPushButton( "&Cancel" );
    connect( ok, SIGNAL( clicked() ), SLOT( accept() ) );
    connect( cancel, SIGNAL( clicked() ), SLOT( reject() ) );

    QVBoxLayout *vbox = new QVBoxLayout( this);
    vbox->addWidget( ed );

    QWidget *w = new QWidget(this);
    vbox->addWidget(w);
    QHBoxLayout *hbox = new QHBoxLayout( w );
    w->setLayout(hbox);
    hbox->addWidget( ok );
    hbox->addStretch( -1 );
    hbox->addWidget( cancel );
    resize( 400, 400 );
}

void ScriptEditor::setCode( const QString &c )
{
    ed->setText( c );
}

ScriptButton::ScriptButton( QSProject *proj,
			    QWidget *parent, const char* name )
    : QPushButton(parent)
{
    setObjectName(name);
    init( proj );
}

ScriptButton::ScriptButton( QSProject *proj, const QString &text,
			    QWidget *parent, const char* name )
    : QPushButton( text, parent)
{
    setObjectName(name);
    init( proj );
}

void ScriptButton::init( QSProject *proj )
{
    project = proj;
    popup = 0;
    edit = 0;
    connect( this, SIGNAL(clicked()), this, SLOT(executeScript()) );
}

void ScriptButton::setScriptCode( const QString &c )
{
    code = c;
}

void ScriptButton::executeScript()
{
    if ( !code.isEmpty() )
	project->interpreter()->evaluate( code );
}

void ScriptButton::contextMenuEvent( QContextMenuEvent *e )
{
    if ( !popup ) {
	popup = new QMenu( this );
	popup->addAction( "Rename Button", this, SLOT(renameButton()) );
	popup->addAction( "Edit Code", this, SLOT(editCode()) );
    }
    popup->exec( e->globalPos() );
    e->accept();
}

void ScriptButton::renameButton()
{
    bool ok;
    QString n = QInputDialog::getText( this, "Script Button",
				       "Enter new button name",
				       QLineEdit::Normal,
				       text(), &ok);
    if ( ok )
	    setText( n );
}

void ScriptButton::editCode()
{
    if ( !edit ) {
	    edit = new ScriptEditor( project );
	    edit->setWindowTitle( QString( "%1 Script Code" ).arg( objectName() ) );
    }
    edit->setCode( scriptCode() );
    if ( edit->exec() == QDialog::Accepted )
	setScriptCode( edit->code() );
}

#endif // QSA_NO_EDITOR
