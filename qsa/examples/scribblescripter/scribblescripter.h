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

#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include <qsinterpreter.h>
#ifndef QSA_NO_IDE
#include <qsworkbench.h>
#endif

#include <QtGui/QPen>
#include <QtWidgets/QMainWindow>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <QtGui/QPolygon>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QVBoxLayout>

class QToolButton;
class QSpinBox;

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas( QWidget *parent = 0, const char *name = 0 );

    void setPenColor( const QColor &c )
    { pen.setColor(c); }

    void setPenWidth( int w )
    { pen.setWidth( w ); }

    QColor penColor()
    { return pen.color(); }

    int penWidth()
    { return pen.width(); }

    QPixmap& pixmap()
    { return buffer; }

    void setPixmap(QPixmap &pixmap)
    { buffer = pixmap; }

    void save( const QString &filename, const QString &format );
    void clearScreen();

protected:
    void mousePressEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *e );

    QPen pen;
    QPolygon polyline;

    bool mousePressed;
    QPixmap buffer;
};


static const char * function_xpm[] = {
"16 16 14 1",
"       c None",
".      c #000000",
"+      c #FCFC80",
"@      c #E0BC38",
"#      c #F0DC5C",
"$      c #585858",
"%      c #FFFF85",
"&      c #FFFF00",
"*      c #FFFFDE",
"=      c #C0C000",
"-      c #DEDEB6",
";      c #C1C10A",
">      c #FFFFC0",
",      c #FFFFFF",
"         ..     ",
"        .++..   ",
"       .+++++.  ",
"      .+++++@.  ",
"   .. .##++@@.  ",
"  .++..###@@@.  ",
" .+++++.##@@.   ",
".+++++@..#$%    ",
".##++@@$%.$&*$% ",
".###@@@.$&=&=&- ",
".###@@.  ;>%>=$.",
" ..#@. %&&%,%&&%",
"   ..  ..=>%>=..",
"        .&=&=&  ",
"       .% .& .% ",
"          .%    "};

static const char * class_xpm[] = {
"16 16 19 1",
"       c None",
".      c #000000",
"+      c #A4E8FC",
"@      c #24D0FC",
"#      c #001CD0",
"$      c #0080E8",
"%      c #C0FFFF",
"&      c #00FFFF",
"*      c #008080",
"=      c #00C0C0",
"-      c #585858",
";      c #FFFF85",
">      c #FFFF00",
",      c #FFFFDE",
"'      c #C0C000",
")      c #DEDEB6",
"!      c #C1C10A",
"~      c #FFFFC0",
"{      c #FFFFFF",
"     ..         ",
"    .++..       ",
"   .+++@@.      ",
"  .@@@@@#...    ",
"  .$$@@##.%%..  ",
"  .$$$##.%%%&&. ",
"  .$$$#.&&&&&*. ",
"   ...#.==-;**. ",
"   .++.-;=->,-; ",
"  .+++@@->'>'>) ",
" .@@@@@#.!~;~'-.",
" .$$@@#;>>;{;>>;",
" .$$$##..'~;~'..",
" .$$$##..>'>'>  ",
"  ..$#..; .> .; ",
"    ..    .;    "};

static const char * variable_xpm[] = {
"16 16 14 1",
"       c None",
".      c #000000",
"+      c #ACB4C0",
"@      c #8C748C",
"#      c #9C94A4",
"$      c #585858",
"%      c #FFFF85",
"&      c #FFFF00",
"*      c #FFFFDE",
"=      c #C0C000",
"-      c #DEDEB6",
";      c #C1C10A",
">      c #FFFFC0",
",      c #FFFFFF",
"                ",
"                ",
"                ",
"      ..        ",
"     .++..      ",
"    .+++++.     ",
"   .+++++@.     ",
"   .##++@@$%    ",
"   .###$%@$&*$% ",
"   .###@$&=&=&- ",
"    ..#@.;>%>=$.",
"      .%&&%,%&&%",
"       ..=>%>=..",
"        .&=&=&  ",
"       .% .& .% ",
"          .%    "};

class ScriptView : public QDockWidget
{
    Q_OBJECT
public:
    ScriptView( QSInterpreter *ip, bool floating = false,
        QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = Qt::WindowFlags() )
        : QDockWidget( parent, f )
    {
        setObjectName(QLatin1String(name));
        setFloating(floating);
        interpreter = ip;
#ifndef QSA_NO_IDE
        ide = new QSWorkbench( interpreter->project(), this );
#endif
        classPixmap = new QPixmap( class_xpm );
        varPixmap = new QPixmap( variable_xpm );
        funcPixmap = new QPixmap( function_xpm );

        QWidget *w = new QWidget(this);
        QVBoxLayout *l = new QVBoxLayout;
        w->setLayout(l);

        l->addWidget(view = new QTreeWidget(w));
        view->setObjectName("Script List");
        view->setColumnCount(1);

        globals = new QTreeWidgetItem(view);
        classes = new QTreeWidgetItem(view);

        globals->setFlags(Qt::ItemIsEnabled);
        classes->setFlags(Qt::ItemIsEnabled);

        view->header()->setVisible(false);                          // since we hide it...
        view->setRootIsDecorated(true);
        view->setMinimumSize(QSize(130, 10));
        view->adjustSize();

        globals->setIcon(0, QIcon(*classPixmap));
        classes->setIcon(0, QIcon(*classPixmap));
        globals->setText(0, "Global");
        classes->setText(0, "Classes");

        l->addWidget(edit = new QPushButton("Edit Scripts"));
        l->addWidget(update = new QPushButton("Update"));

        connect( edit, SIGNAL(clicked()), this, SLOT( openIDE() ) );
        connect( update, SIGNAL(clicked()), this, SLOT(updateScripts()) );
        connect( view, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(runScript(QTreeWidgetItem *)) );
        updateScripts();
        setWidget( w );
    }

    ~ScriptView()
    {
	    delete classPixmap;
	    delete varPixmap;
	    delete funcPixmap;
    }

private slots:
    void updateScripts();
    void runScript( QTreeWidgetItem *item );
    void openIDE();

private:
    QSInterpreter *interpreter;
#ifndef QSA_NO_IDE
    QSWorkbench *ide;
#endif
    QTreeWidget *view;
    QPushButton *update, *edit;
    QTreeWidgetItem *globals, *classes;
    QPixmap *varPixmap;
    QPixmap *classPixmap;
    QPixmap *funcPixmap;
};


class Scribble : public QMainWindow
{
    Q_OBJECT

public:
    Scribble( QWidget *parent = 0, const char *name = 0 );

protected:
    QSProject *project;
    QSInterpreter *interpreter;
    Canvas* canvas;

    QSpinBox *bPWidth;
    QAction *bPColor, *bSave, *bClear;
    ScriptView *selector;
    QToolBar *tools;

protected slots:
    void slotSave();
    void slotColor();
    void slotWidth( int );
    void slotClear();
};


// ------------------------------------------------------------------------------


class PixmapInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QColor color READ penColor WRITE setPenColor )
    Q_PROPERTY( QColor background READ backgroundColor WRITE setBackgroundColor )
    Q_PROPERTY( int penWidth READ penWidth WRITE setPenWidth )

public:
    PixmapInterface( QPixmap &pixmap, QObject *parent = 0, const char *name = 0 )
	: QObject(parent)
    {
        setObjectName(QLatin1String(name));
	    setBuffer( pixmap );
	    pen.setColor( Qt::black );
    }

    // Not slots, since scriptuser should not access these...
    QPixmap& buffer()
    {
	    p.end();
	    return pix;
    }

    void setBuffer( QPixmap &pixmap )
    {
	pix = pixmap;
        p.begin( &pix );
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen( pen );
    }

    QColor penColor() const
    { return pen.color(); }

    void setPenColor( const QColor& colo )
    {
	    color = colo;
	    pen.setColor( color );
    }

    const QColor &backgroundColor() const
    { return p.background().color(); }

    void setBackgroundColor( const QColor& colo  )
    { p.setBackground(colo); }

    void setPenWidth( int w )
    { pen.setWidth( (uint)w ); }

    int penWidth() const
    { return pen.width(); }

public slots:
    PixmapInterface* pixmap()
    { return new PixmapInterface( pix ); }

    void setPixmap( PixmapInterface *Pixmap )
    { pix = Pixmap->buffer(); }

    void clear()
    { p.fillRect(0, 0, pix.width(), pix.height(), p.background().color()); }

    void fillRect( int x, int y, int w, int h )
    { p.fillRect( x, y, w, h, color ); }

    void scale( double sx, double sy )
    { p.scale( sx, sy ); }

    void shear( double sh, double sv )
    { p.shear( sh, sv ); }

    void rotate( double val ) { p.rotate( val ); }

    void translate( double dx, double dy )
    { p.translate( dx, dy ); }

    void drawPoint( int x, int y )
    { p.drawPoint( x, y ); }

    void moveTo( int x, int y )
    { current_point = QPoint(x, y); }

    void lineTo( int x, int y )
    {
        p.drawLine(current_point, QPoint(x, y));
        current_point = QPoint(x, y);
    }

    void drawLine( int x1, int y1, int x2, int y2 )
    { p.drawLine( x1, y1, x2, y2 ); }

    void drawRect( int x, int y, int w, int h )
    { p.drawRect( x, y, w, h ); }

    void drawRoundRect( int x, int y, int w, int h, int xRnd = 25, int yRnd = 25)
    { p.drawRoundedRect( x, y, w, h, xRnd, yRnd, Qt::RelativeSize ); }

    void drawEllipse( int x, int y, int w, int h )
    { p.drawEllipse( x, y, w, h ); }

    void drawArc( int x, int y, int w, int h, int a, int alen )
    { p.drawArc( x, y, w, h, a, alen ); }

    void drawPie( int x, int y, int w, int h, int a, int alen )
    {
	p.setPen( Qt::NoPen );
	p.setBrush( color );
	p.drawPie( x, y, w, h, a, alen );
	p.setBrush( Qt::NoBrush );
	p.setPen( color );
    }

    void drawChord( int x, int y, int w, int h, int a, int alen )
    { p.drawChord( x, y, w, h, a, alen ); }

    void drawText( QString text, int x, int y )
    { p.drawText( x, y, text); }

    void eraseRect( int x, int y, int w, int h )
    { p.eraseRect( x, y, w, h ); }

    void setWindow( int x, int y, int w, int h )
    { p.setWindow( x, y, w, h ); }

    void setViewport( int x, int y, int w, int h )
    { p.setWindow( x, y, w, h ); }

    void resize( int w, int h )
    {
        p.end();

        QPixmap tmppm(w, h);
        tmppm.fill(Qt::black);
        QPainter pa(&tmppm);
        pa.drawPixmap(0, 0, pix);
        pa.end();
        pix = tmppm;

        p.begin( &pix );
        p.setRenderHint(QPainter::Antialiasing);
    }

private:
    QPoint current_point;
    QPixmap pix;
    QPainter p;
    QPen pen;
    QColor color;
};



class CanvasInterface : public QObject
{
    Q_OBJECT

public:
    CanvasInterface( Canvas *mainCanvas, QObject *parent = 0, const char *name = 0 )
	: QObject(parent)
    {
        setObjectName(QLatin1String(name));
	    kanwaz = mainCanvas;
    }

public slots:
    PixmapInterface* pixmap() const
    {
	return new PixmapInterface( kanwaz->pixmap() );
    }

    void setPixmap( PixmapInterface *Pixmap )
    {
	    kanwaz->setPixmap( Pixmap->buffer() );
	    kanwaz->repaint();
    }

    int width()
    {
	return kanwaz->pixmap().width();
    }

    int height()
    {
	return kanwaz->pixmap().height();
    }

    int visibleWidth()
    {
	return kanwaz->width();
    }

    int visibleHeight()
    {
	return kanwaz->height();
    }

private:
    Canvas *kanwaz;
};

#endif
