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
#ifndef WIDGETWRAPPER_H
#define WIDGETWRAPPER_H

#include <qswrapperfactory.h>
#include <qsobjectfactory.h>

#include <QtWidgets/QWidget>

class WidgetWrapper : public QObject
{
    Q_OBJECT

public:
    WidgetWrapper( QWidget *w );

public slots:
    void sendMousePressEvent( const QPoint &pos, int button, int state );
    void sendMouseReleaseEvent( const QPoint &pos, int button, int state );

private:
    QWidget *widget;
};


class WidgetWrapperFactory : public QSWrapperFactory
{
public:
    WidgetWrapperFactory();
    QObject *create( const QString &className, void *ptr );
};

class QtNamespace : public QObject
{
public:
    int noButton() const { return Qt::NoButton; }
    int leftButton() const { return Qt::LeftButton; }
    int rightButton() const { return Qt::RightButton; }
    int midButton() const { return Qt::MidButton; }
    int shiftButton() const { return Qt::ShiftModifier; }
    int controlButton() const { return Qt::ControlModifier; }
    int altButton() const { return Qt::AltModifier; }
    int metaButton() const { return Qt::MetaModifier; }
    const QMetaObject *metaObject() const { return &QObject::staticQtMetaObject; }
};

class QtNamespaceProvider : public QSObjectFactory
{

public:
    QtNamespaceProvider();    
};

#endif
