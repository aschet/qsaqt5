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
#ifndef MODULES_H
#define MODULES_H

#include <QtCore/QEvent>
#include <QtGui/QImage>
#include <QtWidgets/QLabel>

#include "data.h"

class QSInterpreter;
class QLabel;

class Renderer : public QObject
{
    Q_OBJECT
    Q_OVERRIDE( QString objectName SCRIPTABLE false )
public:
    Renderer( QSInterpreter *interp );
    ~Renderer();
public slots:
    void input( Data *data );
private:
    QImage im;
    QSInterpreter *ip;
    QLabel *widget;
};

class ImgSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString file READ file WRITE setFile )
    Q_OVERRIDE( QString name SCRIPTABLE false )
public:
    ImgSource( QSInterpreter *interp );
    void setFile( const QString &name );
    QString file() const { return fileName; }
public slots:
    void load();
signals:
    void output( Data *d );
private:
    QString fileName;
    Data last;
    QString lastName;
    QSInterpreter *ip;
};

class Threshold : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int steps READ steps WRITE setSteps )
    Q_OVERRIDE( QString objectName SCRIPTABLE false )
public:
    Threshold() : step( 1 ) { }
    int steps() const { return step; }
    void setSteps( int s ) { if( s>0 ) step = s; }
public slots:
    void input( Data *d );
signals:
    void output( Data *d );
private:
    int step;
};

class BumpMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QPoint light READ light WRITE setLight )
    Q_PROPERTY( int smoothness READ smoothness WRITE setSmoothness )
    Q_PROPERTY( int radius READ radius WRITE setRadius )
    Q_OVERRIDE( QString objectName SCRIPTABLE false )
public:
    BumpMapper();
    QPoint light() const { return lp; }
    int smoothness() const { return smooth; }
    int radius() const { return rad; }
    void setLight( const QPoint &p ) { lp = p; }
    void setSmoothness( int smo ) { smooth = smo; }
    void setRadius( int ra ) { rad = ra; }
public slots:
    void input( Data *d );
signals:
    void output( Data *d );
private:
    QPoint lp;
    int smooth;
    int rad;
};

class Smudger : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int iterations READ iterations WRITE setIterations )
    Q_OVERRIDE( QString objectName SCRIPTABLE false )
public:
    Smudger();
    int iterations() const { return iter; }
    void setIterations( int it ) { iter = it; }
public slots:
    void input( Data *d );
signals:
    void output( Data *d );
private:
    int iter;
};

#endif


