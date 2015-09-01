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

#include "scribblescripter.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QColorDialog>
#include <QtGui/QCursor>
#include <QtWidgets/QDockWidget>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>
#include <QtGui/QImage>
#include <QtCore/QList>
#include <QtWidgets/QTreeWidget>
#include <QtGui/QPainter>
#include <QtCore/QPoint>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtCore/QRect>
#include <QtWidgets/QSpinBox>
#include <QtCore/QString>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>
#include <QtCore/QVariant>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPixmap>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>

#include <qsproject.h>
#include <qsinputdialogfactory.h>

const bool no_writing = false;

Canvas::Canvas( QWidget *parent, const char *name )
    : QWidget(parent), pen(Qt::red, 3), polyline(3),
      mousePressed(false), buffer(width(), height())
{
    setObjectName(QLatin1String(name));
    setAttribute(Qt::WA_StaticContents, true);

    setMinimumSize(QSize(256, 256));

	// TODO: QSAQt5 check if correctly ported
	QStringList arguments = qApp->arguments();
	if ((arguments.size() > 1) && !buffer.load(arguments[1]))
	    buffer.fill(palette().base().color());
#ifndef QT_NO_CURSOR
    setCursor( Qt::CrossCursor );
#endif
}

void Canvas::save( const QString &filename, const QString &format )
{
    if ( !no_writing )
	    buffer.save(filename, qPrintable(format.toUpper()));
}

void Canvas::clearScreen()
{
    buffer.fill(palette().base().color());
    repaint();
}

void Canvas::mousePressEvent( QMouseEvent *e )
{
    mousePressed = true;
    polyline[2] = polyline[1] = polyline[0] = e->pos();
}

void Canvas::mouseReleaseEvent( QMouseEvent * )
{
    mousePressed = false;
}

void Canvas::mouseMoveEvent( QMouseEvent *e )
{
    if ( mousePressed ) {
	QPainter painter;
	painter.begin( &buffer );
        painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen( pen );
	polyline[2] = polyline[1];
	polyline[1] = polyline[0];
	polyline[0] = e->pos();
	painter.drawPolyline( polyline );
	painter.end();

	QRect r = polyline.boundingRect();
	r = r.normalized();
	r.setLeft( r.left() - penWidth() );
	r.setTop( r.top() - penWidth() );
	r.setRight( r.right() + penWidth() );
	r.setBottom( r.bottom() + penWidth() );

	update();
    }
}

void Canvas::resizeEvent( QResizeEvent *e )
{
    QWidget::resizeEvent( e );

    int w = width();
    int h = height();

    QPixmap tmp(w, h);
    {
        QPainter p(&tmp);
        p.fillRect(0, 0, w, h, Qt::white);
        if (!buffer.isNull())
            p.drawPixmap(0, 0, buffer);
    }
    buffer = tmp;

    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, buffer);
}

//------------------------------------------------------

void ScriptView::updateScripts()
{
    if (view) {
	QTreeWidgetItem *tmp = 0, *func;
    while (globals->childCount() > 0)
        globals->takeChild(0);
    while (classes->childCount() > 0)
        classes->takeChild(0);

#ifndef QSA_NO_EDITOR
	interpreter->project()->commitEditorContents();
#endif

	QStringList flist = interpreter->functions();
	for (QStringList::iterator x = flist.begin();
	     x != flist.end(); x++) {
	    func = new QTreeWidgetItem(globals);
        func->setText(0, *x);
	    func->setIcon(0, QIcon(*funcPixmap));
	}

	QStringList clist = interpreter->classes( QSInterpreter::GlobalClasses );
	for (QStringList::iterator y = clist.begin();
	     y != clist.end(); y++) {
	    tmp = new QTreeWidgetItem(classes);
        tmp->setText(0, *y);
        tmp->setFlags(Qt::ItemIsEnabled);
	    tmp->setIcon(0, QIcon(*varPixmap));
	    QStringList flist = interpreter->functions( *y );
	    for (QStringList::iterator i = flist.begin();
		 i != flist.end(); i++) {
		func = new QTreeWidgetItem(tmp);
        func->setText(0, *i);
		func->setIcon(0, QIcon(*funcPixmap));
	    }
	}

    view->setItemExpanded(globals, true);
    view->setItemExpanded(classes, true);
    }
}

void ScriptView::runScript( QTreeWidgetItem *item )
{
    if ( item->parent() == globals ) {
	    QString funcName  = item->text(0);
#ifndef QSA_NO_EDITOR
	    interpreter->project()->commitEditorContents();
#endif
	    interpreter->call(funcName);
    }
}

void ScriptView::openIDE()
{
#ifndef QSA_NO_IDE
    ide->open();
#else
    QMessageBox::information( this, "Disabled feature",
			      "QSA Workbench, the QSA graphical scripting environment,\n"
			      "has been disabled. Reconfigure to enable",
			      QMessageBox::Ok );
#endif
}

//------------------------------------------------------

Scribble::Scribble( QWidget *parent, const char *name )
    : QMainWindow(parent)
{
    setObjectName(QLatin1String(name));

    canvas = new Canvas( this );
    setCentralWidget( canvas );

    tools = new QToolBar;
    addToolBar(tools);

    bSave = tools->addAction("Save As...", this, SLOT(slotSave()));
    bSave->setToolTip("Save as PNG image");
    bSave->setIconText("Save");

    tools->addSeparator();

    bPColor = tools->addAction("Choose Pen Color...", this, SLOT(slotColor()));
    bPColor->setToolTip("Choose Pen Color");
    bPColor->setIconText("Choose Pen Color");

    tools->addSeparator();

    bPWidth = new QSpinBox;
    bPWidth->setMinimum(1);
    bPWidth->setMaximum(20);
    bPWidth->setSingleStep(1);
    tools->addWidget(bPWidth);
    bPWidth->setToolTip("Choose Pen Width");
    connect( bPWidth, SIGNAL( valueChanged( int ) ), this, SLOT( slotWidth( int ) ) );
    bPWidth->setValue( 3 );

    tools->addSeparator();

    bClear = tools->addAction("Clear screen", this, SLOT(slotClear()));
    bClear->setToolTip("Clear Screen");
    bClear->setIconText("Clear Screen");

    project = new QSProject( this, "scribblescript_project" );
    interpreter = project->interpreter();
#ifndef QSA_NO_GUI
	QSInputDialogFactory *factory = new QSInputDialogFactory();
    interpreter->addObjectFactory( factory );
#endif

    project->addObject( new CanvasInterface( canvas, this, "Canvas" ) );
    project->load( "scribblescript.qsa" );
    connect( project, SIGNAL( projectEvaluated() ), project, SLOT( save() ) );

    selector = new ScriptView( interpreter, false, this );
    selector->setWindowTitle("ScribbleScripts");
    addDockWidget(Qt::LeftDockWidgetArea, selector);
    selector->show();
}

void Scribble::slotSave()
{
    QMenu *menu = new QMenu( 0 );
    QMap<QAction *, QString *> formats;

    formats[menu->addAction(QLatin1String("jpg"))] = new QString( "jpg" );
    formats[menu->addAction(QLatin1String("png"))] = new QString( "png" );

    QAction *act = menu->exec(tools->mapToGlobal(QPoint(0, tools->height() + 1)));
    if (act != 0) {
	    QString format = *formats[act];

	    QString filename = QFileDialog::getSaveFileName(this, QString(), QString(), QString( "*.%1" ).arg( format.toLower() ));
	    if (!filename.isEmpty())
	        canvas->save(filename, format);
    }

    QMap<QAction *, QString *>::iterator it;
    for (it = formats.begin(); it != formats.end(); ++it)
        delete *it;

    delete menu;
}

void Scribble::slotColor()
{
    QColor c = QColorDialog::getColor( canvas->penColor(), this );
    if ( c.isValid() )
	canvas->setPenColor( c );
}

void Scribble::slotWidth( int w )
{
    canvas->setPenWidth( w );
}

void Scribble::slotClear()
{
    canvas->clearScreen();
}
