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
#include "playfield.h"
#include "gamewindow.h"
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QKeyEvent>
#include <QtGui/QPaintEvent>

PlayField::PlayField( QWidget *parent, const char *name )
    : QWidget(parent)
{
    setObjectName(QLatin1String(name));
    left = false;
    right = false;
    up = false;
    down = false;
    space = false;
    setFocusPolicy( Qt::StrongFocus );
    setFixedSize( 500, 400 );
    mode = None;
}

PlayField::~PlayField()
{
}

int PlayField::addItem( const QPixmap &pm )
{
    items.append( PlayFieldItem(pm) );
    return items.count()-1;
}

void PlayField::moveItem( int id, int x, int y )
{
    PlayFieldItem &it = items[id];
    it.x = x;
    it.y = y;
}

void PlayField::enableItem( int id, bool enable )
{
    PlayFieldItem &it = items[id];
    it.enabled = enable;
}

void PlayField::paintEvent( QPaintEvent * )
{
    QPixmap pm( size() );
    QPainter p;
    p.begin(&pm);
    p.setBrush( Qt::black );
    p.drawRect( 0, 0, width(), height() );
    if ( mode==None ) {
	ItemListConstIterator it = items.begin();
	while( it!=items.end() ) {
	    const PlayFieldItem item = *it;
	    if( item.enabled )
		p.drawPixmap( item.x, item.y, item.pixmap );
	    it++;
	}
    } else {
	p.setPen( Qt::white );
	p.setFont( QFont( "serif", 20 ) );
	QString s = mode==Win ? "You won!!" : "Game over";
	QRect r = p.boundingRect( QRect(), 0, s );
	p.drawText( width()/2-r.width()/2, height()/2-r.height()/2, s );
    }
    p.end();
    
    QPainter(this).drawPixmap(0, 0, pm);
}

void PlayField::gameOver( bool success )
{
    mode = success ? Win : Lose;
    emit gameCompleted();
}

void PlayField::clear()
{
    items.clear();
    mode = None;
}

void PlayField::keyPressEvent( QKeyEvent *ev )
{
    switch( ev->key() )
	{
	case Qt::Key_Left: left = true; break;
	case Qt::Key_Right: right = true; break;
	case Qt::Key_Up: up = true; break;
	case Qt::Key_Down: down = true; break;
	case Qt::Key_Space: space = true; break;
	}
}

void PlayField::keyReleaseEvent( QKeyEvent *ev )
{
    switch( ev->key() )
	{
	case Qt::Key_Left: left = false; break;
	case Qt::Key_Right: right = false; break;
	case Qt::Key_Up: up = false; break;
	case Qt::Key_Down: down = false; break;
	case Qt::Key_Space: space = false; break;
	}
}

