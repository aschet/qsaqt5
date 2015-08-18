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
#include "modules.h"

#include <QtGui/QPainter>
#include <QtCore/QFile>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>
#include <math.h>

#include <qsinterpreter.h>


Renderer::Renderer( QSInterpreter *interp ) :
    QObject(0), ip( interp )
{
    setObjectName("Renderer");
    widget = new QLabel(0);
}


Renderer::~Renderer()
{
    delete widget;
}

void Renderer::input( Data *data )
{
    im = QImage(data->width(), data->height(), QImage::Format_Indexed8);
    if(im.isNull()) {
	    ip->throwError( "Failed to create image" );
	    return;
    }
	// TODO: QSAQt5 - check if correct replacement was used
	im.setColorCount(256);

    for( int i=0; i<256; i++ )
	im.setColor( i, qRgb( i, i, i ) );

    int w = data->width();
    int h = data->height();
    uchar *bits = im.bits();
    int oset = 0;

    for( int y = 0; y<h; y++ ) {
	for( int x = 0; x<w; x++ ) {
	    bits[oset++] = (uchar) ( data->value( x, y ) & 0xff );
	}
    }

    widget->setFixedSize( im.width(), im.height() );
    QPixmap pm( QSize( im.width(), im.height() ) );
    QPainter p( &pm );
    p.drawImage( 0, 0, im );
    p.end();
    widget->setPixmap( pm );

    if( !widget->isVisible() )
	widget->show();
}


ImgSource::ImgSource( QSInterpreter *interp )
    : ip( interp )
{
}

void ImgSource::setFile( const QString &name )
{
    if( !QFile::exists( name ) ) {
	ip->throwError( "File does not exists '" + name + "'" );
    }
    fileName = name;
}


void ImgSource::load()
{
    if( fileName.isNull() ) {
	ip->throwError( "Could not load image: No filename specified" );
	return;
    }

    if( !QFile::exists( fileName ) ) {
	ip->throwError( "Unable to load file '" + fileName + "', file does not exist" );
	return;
    }

    if( !lastName.isNull() && fileName==lastName ) {
	emit output(&last);
	return;
    }

    QImage im( fileName );
    int w = im.width(), h = im.height();
    Data d( im.width(), im.height() );

    for( int y=0; y<h; y++ ) {
	for( int x=0; x<w; x++ ) {
	    QRgb rgb = im.pixel( x, y );
	    d.setValue( x, y, int( ( qRed(rgb) + qGreen(rgb) + qBlue(rgb) ) / 3.0 ) );
	}
    }

    last = d;
    lastName = fileName;

    emit output( &d );
}


void Threshold::input( Data *d )
{
    int w = d->width(), h = d->height();
    int fac = 256 / step;
    Data th( w, h );
    for( int y=0; y<h; y++ ) {
	for( int x=0; x<w; x++ ) {
	    th.setValue( x, y, ( d->value( x, y ) / fac ) * fac );
	}
    }
    qApp->processEvents();
    emit output( &th );
}


#define veclen(x,y,z) sqrt( x*x + y*y + z*z )

BumpMapper::BumpMapper()
    : lp( QPoint(100,100) ), smooth( 8 ), rad( 150 )
{

}

void BumpMapper::input( Data *d )
{
    int w = d->width(), h = d->height();
    int lz = 260;
    int a, b;
    double nx, ny, nz, nl;
    double dx, dy, dz, dl, dot;
    Data out( w, h );

    if( smooth == 0 )
	smooth = 1;

    for( int y=1; y<h-1; y++ ) {
	for( int x=1; x<w-1; x++ ) {
	    // Calculate the the normal vector..
	    a = d->value( x, y+1 ) - d->value( x, y-1 );
	    b = d->value( x+1, y ) - d->value( x-1, y );
	    nx = -2*b;
	    ny = -2*a;
	    nz = smooth;
	    nl = veclen( nx, ny, nz );
	    nx /= nl;
	    ny /= nl;
	    nz /= nl;

	    dx = lp.x()-x;
	    dy = lp.y()-y;
	    dz = lz-d->value( x, y );
	    dl = veclen( dx, dy, dz );
	    if( dl>rad ) {
		out.setValue( x, y, 0 );
		continue;
	    }

	    dx /= dl;
	    dy /= dl;
	    dz /= dl;

	    dot = dx*nx + dy*ny + dz*nz;
	    dl = (rad-dl)/(float)rad;
	    if( dot<0 || dl<0 ) {
		out.setValue( x, y, 0 );
		continue;
	    }

	    out.setValue( x, y, (int)(dl*dot*255) );
	}
    }

    qApp->processEvents();

    emit output( &out );
}
Smudger::Smudger() : iter( 1 )
{
}

void Smudger::input( Data *d )
{
    int w = d->width(), h = d->height();
    Data out( w, h );
    const Data *use = d;
    int val;
    for( int step=0; step<iter; ++step ) {
	for( int y=1; y<h-1; ++y ) {
	    for( int x=1; x<w-1; ++x ) {
		val = use->value( x, y )
		    + use->value( x+1, y ) + use->value( x-1, y )
		    + use->value( x, y+1 ) + use->value( x, y-1 );
		out.setValue( x, y, val / 5 );
	    }
  	}
	use = &out;
    }
    emit output(&out);
}

