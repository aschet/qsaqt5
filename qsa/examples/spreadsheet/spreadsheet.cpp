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

#include "spreadsheet.h"
#include "addscriptdialog.h"
#include "sheetinterface.h"

#include <qsinputdialogfactory.h>
#include <qsproject.h>
#include <qsscript.h>
#include <qsinterpreter.h>

#ifndef QSA_NO_IDE
#include <qsworkbench.h>
#endif

#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QMetaObject>
#include <QtGui/QPixmap>
#include <QtCore/QTimer>
#include <QtCore/QList>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QHeaderView>

SpreadSheet::SpreadSheet(QWidget *parent)
: QMainWindow(parent)
{
    setupUi(this);
    connect(sheet1, &QTableWidget::currentItemChanged, this, &SpreadSheet::currentCellChanged);
    connect(sheet1, &QTableWidget::itemChanged, this, &SpreadSheet::currentValueChanged);
    init();
}

void SpreadSheet::init()
{
    inInit = true;

    project = new QSProject( this, "spreadsheet_project" );
    interpreter = project->interpreter();
#ifndef QSA_NO_GUI
	QSInputDialogFactory *fac = new QSInputDialogFactory;
    interpreter->addObjectFactory( fac );
#endif

    project->addObject( new SheetInterface( sheet1, this, "sheet1" ) );

    project->load( "spreadsheet.qsa" );
    connect( project, SIGNAL( projectEvaluated() ),
	     project, SLOT( save() ) );

    
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("&File");    
    QAction *fileExitAction = fileMenu->addAction("E&xit");
    connect(fileExitAction, SIGNAL(triggered(bool)), this, SLOT(fileExit()));

    scriptsMenu = menuBar->addMenu("&Scripts");
    QAction *scriptsNewAction = scriptsMenu->addAction(QIcon(":/images/hi22-action-run.png"), 
                                                       "&New...");
    connect(scriptsNewAction, SIGNAL(triggered(bool)), this, SLOT(addScript()));
    QAction *scriptsQSA = scriptsMenu->addAction(QIcon(":/images/hi22-action-project_open.png"), 
                                                 "QSA &Workbench");   
    connect(scriptsQSA, SIGNAL(triggered(bool)), this, SLOT(openIDE()));
    setMenuBar(menuBar);

    QToolBar *toolBar = new QToolBar("Calculation Toolbar", this);
    currentCell = new QLabel("A1", toolBar);
        toolBar->addWidget(currentCell);
    formulaEdit = new QLineEdit(toolBar);
        toolBar->addWidget(formulaEdit);
        connect(formulaEdit, SIGNAL(returnPressed()), this, SLOT(formulaEdited()));
    addToolBar(toolBar);

    scriptsToolbar = new QToolBar("Scripts Toolbar", this);
    scriptsToolbar->addAction(scriptsNewAction);
    scriptsToolbar->addAction(scriptsQSA);
    addToolBar(scriptsToolbar);        

    for (int i=0; i<sheet1->rowCount(); ++i) {
        sheet1->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i + 1)));

        for (int j=0; j<sheet1->columnCount(); ++j) {
            sheet1->setItem(i, j, new QTableWidgetItem);
            if (i == 0) {
                sheet1->setHorizontalHeaderItem(j, new QTableWidgetItem);
            }
        }
    }

    setupSheet( sheet1 );
    inInit = false;
}

void SpreadSheet::setupSheet( QTableWidget *t )
{
    int num = -1;
    static QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int ch = 0;
    QStringList headerLabels;
    for (int i = 0; i < t->columnCount(); ++i) {
        if (ch == 26) {
            ch = 0;
            num++;
        }
        QString s = QString(letters[ch]);
        if (num != -1)
            s.prepend(letters[num]);
        ch++;
        headerLabels << s;        
    }
    t->setHorizontalHeaderLabels(headerLabels);
}

void SpreadSheet::fileExit()
{
    qApp->quit();
}


void SpreadSheet::currentCellChanged(QTableWidgetItem *current, QTableWidgetItem *)
{
    if (current == 0)
        return ;

    int col = sheet1->column(current);
    int row = sheet1->row(current);

    QTableWidgetItem *horizHeader = sheet1->horizontalHeaderItem(col);
    QString horizHeaderText;
    if (col >= 0) 
        horizHeaderText = horizHeader->text();
    
    currentCell->setText(sheet1->objectName()
			  + QLatin1String(":")
			  + horizHeaderText
			  + QString::number(row + 1));
    formulaEdit->setText(current->text());    
}

void SpreadSheet::currentValueChanged(QTableWidgetItem *item)
{    
    if (inInit)
        return ;

    if (item)
        formulaEdit->setText(item->text());
    else
        formulaEdit->setText(QString());

    // We can't evaluate directly from this slot, as a parse error will
    // cause the item delegate to get a focus out and be deleted
    evaluationItems << item;
    QTimer::singleShot(0, this, SLOT(timedEvaluation()));

    QTableWidgetItem *currentItem = sheet1->currentItem();
    if (currentItem)
        formulaEdit->setText(currentItem->text());
    else
        formulaEdit->setText(QString());    
}

void SpreadSheet::timedEvaluation()
{
    for (int i=0; i<evaluationItems.size(); ++i) {
        QTableWidgetItem *item = evaluationItems[i];
        QTableWidgetItem *currentItem = sheet1->currentItem();
        sheet1->setCurrentItem(item);
        evaluate();
        sheet1->setCurrentItem(currentItem);    
    }

    evaluationItems.clear();
}

QString SpreadSheet::cellName( int row, int col )
{
    QString s;
    int i = col / 26;
    static QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if ( i > 0 ) {
	--i;
	s = QString( letters[i] );
    }
    s += letters[col % 26];
    s += QString::number( row + 1 );

    return s;
}

void SpreadSheet::evaluate()
{
    QMap<QPair<int, int>, QString> &currentMap = sheet1Map;

    currentMap[QPair<int, int>(sheet1->currentRow(),sheet1->currentColumn())] =
			formulaEdit->text();

    QMap<QPair<int, int>, QString>::ConstIterator it;
    QString vars;
    for ( it = currentMap.begin(); it != currentMap.end(); ++it ) {
        int row = it.key().first;
        int col = it.key().second;
	    QTableWidgetItem *item = sheet1->item(row, col);
        if ( !item )
	        continue;
	    bool ok = false;
	    item->text().toInt( &ok );
	    if ( !ok )
	        continue;
	    vars += "var " + cellName(row, col) + "=" + item->text() + ";\n";
    }

    for ( it = currentMap.begin(); it != currentMap.end(); ++it ) {
	    QTableWidgetItem *item = sheet1->item(it.key().first, it.key().second);
	    if ( !item )
	        continue;
	    evaluateCell( item, *it, vars );
    }
}

void SpreadSheet::evaluateCell( QTableWidgetItem *item, const QString &f, const QString &vars )
{
    QString formula( f );
    int row = sheet1->row(item);
    int col = sheet1->column(item);

    if (formula.isEmpty())
        return;

    if ( formula[0] != '=' )
	    return;
    QString cn = cellName( row, col );
    formula = vars + "\n" + cn + "=" + formula.mid(1) + ";\n" +
	          "Application." + QString(sheet1->objectName()) + 
              ".setText(" + QString::number(row) +
	          ", " + QString::number(col) + ", String(" + cn + "));";
    interpreter->evaluate( formula );
}


void SpreadSheet::formulaEdited()
{
    QTableWidgetItem *item = sheet1->item(sheet1->currentRow(), 
                                                sheet1->currentColumn());

    if (item != 0) 
        item->setText(formulaEdit->text());
    evaluate();
    sheet1->setFocus();
}

#ifndef QSA_NO_IDE
static QSWorkbench *spreadsheet_ide = 0;
#endif

void SpreadSheet::openIDE()
{
#ifndef QSA_NO_IDE
    // open the QSA Workbench
    if ( !spreadsheet_ide ) spreadsheet_ide = new QSWorkbench( project, this );
    spreadsheet_ide->open();
#else
    QMessageBox::information( this, "Disabled feature",
			      "QSA Workbench has been disabled. Reconfigure to enable",
			      QMessageBox::Ok );
#endif
}

void SpreadSheet::showFunction( QSScript *script, const QString &functionName )
{
#ifndef QSA_NO_IDE
    if ( !spreadsheet_ide ) spreadsheet_ide = new QSWorkbench( project, this );
    spreadsheet_ide->open();
    spreadsheet_ide->showFunction( script, functionName );
#endif
}

void SpreadSheet::addScript()
{
    // Let the user add a script
    AddScriptDialog dia(this);
    dia.setModal(true);
    connect( &dia, SIGNAL( newScript( const QString &, const QString &,
				      const QPixmap & ) ),
	     this, SLOT( addScript( const QString &, const QString &,
				    const QPixmap & ) ) );
    dia.exec();
}

void SpreadSheet::addScript( const QString &function, const QString &name, const QPixmap &pixmap )
{
    // Add a new action for the script
    QAction *a = new QAction(pixmap, name, this);
    scriptsToolbar->addAction(a);
    scriptsMenu->addAction(a);
    // associate the action with the function name
    scripts.insert( a, function );
    connect( a, SIGNAL( triggered(bool) ), this, SLOT( runScript() ) );
}

void SpreadSheet::runScript()
{
    // find the function which has been associated with the triggered
    // action (the action is the sender())
    QString s = *scripts.find( (QAction*)sender() );
    // and call that function

#ifndef QSA_NO_EDITOR
    project->commitEditorContents();
#endif

    interpreter->call(s);
}
