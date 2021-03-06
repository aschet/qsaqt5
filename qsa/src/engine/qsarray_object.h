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

#ifndef QSARRAY_OBJECT_H
#define QSARRAY_OBJECT_H

#include "qsclass.h"

class QSArrayClass : public QSWritableClass {
public:
    QSArrayClass(QSClass *b);
    QString name() const { return QString::fromLatin1("Array"); }

    QString toString(const QSObject *) const;
    QSObject toPrimitive(const QSObject *obj, const QSClass *cl) const;
    QVariant toVariant(const QSObject *obj, QMetaType::Type) const;

    QSObject construct(const QSList &args) const;
    QSObject cast(const QSList &args) const;

    virtual void write(QSObject *objPtr, const QSMember &mem,
			const QSObject &val) const;

    static uint length(const QSObject *);
    static void setLength(QSObject *, uint l);

    static QString joinInternal(const QSObject &obj, const QString &sep);

    static QSObject concat(QSEnv *);
    static QSObject join(QSEnv *);
    static QSObject pop(QSEnv *);
    static QSObject push(QSEnv *);
    static QSObject reverse(QSEnv *);
    static QSObject shift(QSEnv *);
    static QSObject slice(QSEnv *);
    static QSObject sort(QSEnv *);
    static QSObject splice(QSEnv *);
    static QSObject unshift(QSEnv *);
};

#endif
