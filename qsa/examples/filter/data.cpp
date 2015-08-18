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
#include "data.h"

Data::Data( int w, int h ) :
    wid( w ),
    hei( h )
{
    buffer = new DataBuffer( w*h );
    for ( int i=0; i<w*h; i++ )
	buffer->data[i] = 0;
}

Data::~Data()
{
    buffer->deref();
    if( buffer->data==0 )
	delete buffer;
}


int Data::value( int x, int y ) const
{
    if ( x>=0 && x<wid && y>=0 && y<hei )
	return buffer->data[ y*wid + x ];
    qWarning( "Data::value(), Accessing out of bounds" );
    return 0;
}

void Data::setValue( int x, int y, int val )
{
    if ( x>=0 && x<wid && y>=0 && y<hei )
	buffer->data[ y*wid + x ] = val;
    else
	qWarning( "Data::value(), Accessing out of bounds" );
}


Data::Data( const Data &d )
    : wid( d.wid ), hei( d.hei ), buffer( d.buffer )
{
    buffer->ref();
}


Data& Data::operator=( const Data &d )
{
    wid = d.wid;
    hei = d.hei;
    buffer->deref();
    buffer = d.buffer;
    buffer->ref();
    return *this;
}

DataBuffer::DataBuffer( int size )
    : data( new int[size] ), count( 1 )
{
}


void DataBuffer::ref()
{
    Q_ASSERT( data );
    Q_ASSERT( count>0 );
    count++;
}

void DataBuffer::deref()
{
    Q_ASSERT( data );
    Q_ASSERT( count>0 );

    if( --count == 0 ) {
	delete [] data;
	data = 0;
    }
}
