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
#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtCore/QSize>
#include <QtGui/QKeyEvent>
#include <QtGui/QPaintEvent>

class PlayFieldItem;

typedef QList<PlayFieldItem> ItemList;
typedef QList<PlayFieldItem>::ConstIterator ItemListConstIterator;

class PlayField : public QWidget 
{
  Q_OBJECT

  Q_PROPERTY( bool left READ isLeft )
  Q_PROPERTY( bool right READ isRight )
  Q_PROPERTY( bool up READ isUp )
  Q_PROPERTY( bool down READ isDown )
  Q_PROPERTY( bool space READ isSpace )

  enum GameMode { None, Win, Lose };

public:
  PlayField( QWidget *parent=0, const char * name=0 );
  ~PlayField();

  QSize sizeHint() const { return QSize( 500, 400 ); }
  
  bool isLeft() const { return left; }
  bool isRight() const { return right; }
  bool isUp() const { return up; }
  bool isDown() const { return down; }
  bool isSpace() const { return space; }

public slots:
  int addItem( const QPixmap &pm );
  void moveItem( int id, int x, int y );
  void enableItem( int id, bool enable );
  void gameOver( bool success );
  void clear();

signals:
  void gameCompleted();

protected:
  void paintEvent( QPaintEvent *event );
  void keyPressEvent( QKeyEvent *ev );
  void keyReleaseEvent( QKeyEvent *ev );

private:
  ItemList items;
  int left:1;
  int right:1;
  int up:1;
  int down:1;
  int space:1;
  GameMode mode;
};

class PlayFieldItem 
{
public:
  PlayFieldItem( const QPixmap &pm=QPixmap() ) 
    : pixmap( pm ), x( 0 ), y( 0 ), enabled( true ) { }
  QPixmap pixmap;
  int x;
  int y;
  bool enabled;
  
};

#endif


