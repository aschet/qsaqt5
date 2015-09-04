/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3Support module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Q3URL_H
#define Q3URL_H

#include <QtCore/QString>







#ifndef QT_NO_URL

class Q3UrlPrivate;

class QSA_EXPORT Q3Url
{
public:
    Q3Url();
    Q3Url( const QString& url );
    Q3Url( const Q3Url& url );
    Q3Url( const Q3Url& url, const QString& relUrl, bool checkSlash = false );
    virtual ~Q3Url();

    QString protocol() const;
    virtual void setProtocol( const QString& protocol );

    QString user() const;
    virtual void setUser( const QString& user );
    bool hasUser() const;

    QString password() const;
    virtual void setPassword( const QString& pass );
    bool hasPassword() const;

    QString host() const;
    virtual void setHost( const QString& user );
    bool hasHost() const;

    int port() const;
    virtual void setPort( int port );
    bool hasPort() const;

    QString path( bool correct = true ) const;
    virtual void setPath( const QString& path );
    bool hasPath() const;

    virtual void setEncodedPathAndQuery( const QString& enc );
    QString encodedPathAndQuery();

    virtual void setQuery( const QString& txt );
    QString query() const;

    QString ref() const;
    virtual void setRef( const QString& txt );
    bool hasRef() const;

    bool isValid() const;
    bool isLocalFile() const;

    virtual void addPath( const QString& path );
    virtual void setFileName( const QString& txt );

    QString fileName() const;
    QString dirPath() const;

    Q3Url& operator=( const Q3Url& url );
    Q3Url& operator=( const QString& url );

    bool operator==( const Q3Url& url ) const;
    bool operator==( const QString& url ) const;

    static void decode( QString& url );
    static void encode( QString& url );

    operator QString() const;
    virtual QString toString( bool encodedPath = false, bool forcePrependProtocol = true ) const;

    virtual bool cdUp();

    static bool isRelativeUrl( const QString &url );

protected:
    virtual void reset();
    virtual bool parse( const QString& url );

private:
    Q3UrlPrivate *d;

};

#endif // QT_NO_URL





#endif // Q3URL_H
