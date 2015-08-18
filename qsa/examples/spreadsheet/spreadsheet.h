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
#ifndef MSPREADSHEET_H
#define MSPREADSHEET_H

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtGui/QPixmap>

class QAction;
class QSScript;
class QSProject;
class QSInterpreter;
class QLabel;
class QLineEdit;
class QToolBar;
class QMenu;

#include <ui_spreadsheet.h>

class SpreadSheet: public QMainWindow, public Ui_SpreadSheet
{
    Q_OBJECT
public:
    SpreadSheet(QWidget *parent = 0);

public slots:
    void init();
    void setupSheet(QTableWidget *t);
    void fileExit();
    void currentCellChanged(QTableWidgetItem *, QTableWidgetItem *);
    void currentValueChanged(QTableWidgetItem *);
    QString cellName(int row, int col);
    void evaluate();
    void evaluateCell(QTableWidgetItem *item, const QString &f, const QString &vars);
    void formulaEdited();
    void openIDE();
    void addScript();
    void addScript(const QString &function, const QString &name, const QPixmap &pixmap);
    void runScript();
    void showFunction(QSScript *script, const QString &functionName);
    void timedEvaluation();

public:
    QSInterpreter *interpreter;
    QSProject *project;

private:
    QMap<QAction *, QString> scripts;
    QMap<QPair<int, int>, QString> sheet1Map;
    QMap<QPair<int, int>, QString> sheet2Map;
    QLabel *currentCell;
    QLineEdit *formulaEdit;
    QToolBar *scriptsToolbar;
    QMenu *scriptsMenu;
    bool inInit;
    QList<QTableWidgetItem *> evaluationItems;
};

#endif
