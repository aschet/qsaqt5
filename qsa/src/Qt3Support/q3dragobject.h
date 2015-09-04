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

#ifndef Q3DRAGOBJECT_H
#define Q3DRAGOBJECT_H

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtCore/QMimeData>
#include <QtGui/QImage>
#include <QtCore/QList>







class QWidget;
class Q3TextDragPrivate;
class Q3DragObjectPrivate;
class Q3StoredDragPrivate;
class Q3ImageDragPrivate;
class Q3ImageDrag;
class Q3TextDrag;
class Q3StrList;
class QImage;
class QPixmap;

class QSA_EXPORT Q3DragObject : public QMimeData {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Q3DragObject)
public:
    Q3DragObject(QWidget * dragSource = 0, const char *name = 0);
    virtual ~Q3DragObject();

    bool drag();
    bool dragMove();
    void dragCopy();
    void dragLink();

    virtual void setPixmap(QPixmap);
    virtual void setPixmap(QPixmap, const QPoint& hotspot);
    QPixmap pixmap() const;
    QPoint pixmapHotSpot() const;

    QWidget * source();
    static QWidget * target();

    enum DragMode { DragDefault, DragCopy, DragMove, DragLink, DragCopyOrMove };

protected:
    Q3DragObject(Q3DragObjectPrivate &, QWidget *dragSource = 0);
    virtual bool drag(DragMode);

private:
    friend class QDragMime;
    Q_DISABLE_COPY(Q3DragObject)
};

class QSA_EXPORT Q3StoredDrag: public Q3DragObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Q3StoredDrag)
public:
    Q3StoredDrag(const char *mimeType, QWidget *dragSource = 0, const char *name = 0);
    ~Q3StoredDrag();

    virtual void setEncodedData(const QByteArray &);

    const char * format(int i) const;
    virtual QByteArray encodedData(const char*) const;

protected:
    Q3StoredDrag(Q3StoredDragPrivate &, const char *mimeType, QWidget *dragSource = 0);

private:
    Q_DISABLE_COPY(Q3StoredDrag)
};

class QSA_EXPORT Q3TextDrag: public Q3DragObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Q3TextDrag)
public:
    Q3TextDrag(const QString &, QWidget *dragSource = 0, const char *name = 0);
    Q3TextDrag(QWidget * dragSource = 0, const char * name = 0);
    ~Q3TextDrag();

    virtual void setText(const QString &);
    virtual void setSubtype(const QString &);

    const char * format(int i) const;
    virtual QByteArray encodedData(const char*) const;

    static bool canDecode(const QMimeData* e);
    static bool decode(const QMimeData* e, QString& s);
    static bool decode(const QMimeData* e, QString& s, QString& subtype);

protected:
    Q3TextDrag(Q3TextDragPrivate &, QWidget * dragSource = 0);

private:
    Q_DISABLE_COPY(Q3TextDrag)
};

class QSA_EXPORT Q3ImageDrag: public Q3DragObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Q3ImageDrag)
public:
    Q3ImageDrag(QImage image, QWidget * dragSource = 0, const char * name = 0);
    Q3ImageDrag(QWidget * dragSource = 0, const char * name = 0);
    ~Q3ImageDrag();

    virtual void setImage(QImage image);

    const char * format(int i) const;
    virtual QByteArray encodedData(const char*) const;

    static bool canDecode(const QMimeData* e);
    static bool decode(const QMimeData* e, QImage& i);
    static bool decode(const QMimeData* e, QPixmap& i);

protected:
    Q3ImageDrag(Q3ImageDragPrivate &, QWidget * dragSource = 0);

private:
    Q_DISABLE_COPY(Q3ImageDrag)
};


class QSA_EXPORT Q3UriDrag: public Q3StoredDrag {
    Q_OBJECT

public:
    Q3UriDrag(const Q3StrList &uris, QWidget * dragSource = 0, const char * name = 0);
    Q3UriDrag(QWidget * dragSource = 0, const char * name = 0);
    ~Q3UriDrag();

    void setFileNames(const QStringList & fnames);
    inline void setFileNames(const QString & fname) { setFileNames(QStringList(fname)); }
    void setFilenames(const QStringList & fnames) { setFileNames(fnames); }
    inline void setFilenames(const QString & fname) { setFileNames(QStringList(fname)); }
    void setUnicodeUris(const QStringList & uuris);
    virtual void setUris(const QList<QByteArray> &uris);

    static QString uriToLocalFile(const char*);
    static QByteArray localFileToUri(const QString&);
    static QString uriToUnicodeUri(const char*);
    static QByteArray unicodeUriToUri(const QString&);
    static bool canDecode(const QMimeData* e);
    static bool decode(const QMimeData* e, Q3StrList& i);
    static bool decodeToUnicodeUris(const QMimeData* e, QStringList& i);
    static bool decodeLocalFiles(const QMimeData* e, QStringList& i);

private:
    Q_DISABLE_COPY(Q3UriDrag)
};

class QSA_EXPORT Q3ColorDrag : public Q3StoredDrag
{
    Q_OBJECT
    QColor color;

public:
    Q3ColorDrag(const QColor &col, QWidget *dragsource = 0, const char *name = 0);
    Q3ColorDrag(QWidget * dragSource = 0, const char * name = 0);
    void setColor(const QColor &col);

    static bool canDecode(QMimeData *);
    static bool decode(QMimeData *, QColor &col);

private:
    Q_DISABLE_COPY(Q3ColorDrag)
};





#endif // Q3DRAGOBJECT_H
