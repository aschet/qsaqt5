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
#ifndef SHEETINTERFACE_H
#define SHEETINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QRect>

class SpreadSheet;
class QTableWidget;
class QTableWidgetItem ;

class SheetInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int numSelections READ numSelections )
    Q_PROPERTY( int currentRow READ currentRow WRITE setCurrentRow )
    Q_PROPERTY( int currentColumn READ currentColumn WRITE setCurrentColumn )
    Q_PROPERTY( int numRows READ numRows )
    Q_PROPERTY( int numCols READ numCols )

public:
    SheetInterface( QTableWidget *t, SpreadSheet *s, const char *name );

    int numSelections() const;
    void setCurrentRow( int r );
    void setCurrentColumn( int c );
    int currentRow() const;
    int currentColumn() const;
    int numRows() const;
    int numCols() const;

public slots:
    void setText( int row, int col, const QString &val );
    QString text( int row, int col ) const;
    QRect selection( int num ) const;
    void itemChanged(QTableWidgetItem *);


signals:
    void currentChanged(int row, int col);

private:
    QTableWidget *sheet;
    SpreadSheet *spreadSheet;

};

#endif
