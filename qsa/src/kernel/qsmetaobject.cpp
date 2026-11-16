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
#include "qsmetaobject.h"

#include "qsaqtcompat.h"

#include <QtCore/QVariant>

QSMetaObject::QSMetaObject(QObject *parent) : QSMetaObjectBase(parent)
{ }

QSMetaObject::~QSMetaObject()
{ }

int QSMetaObject::slotOffset()
{ return QSMetaObjectBase::staticMetaObject.methodCount(); }

static void parseQtSignature(const QByteArray &buf, QVector<QMetaType::Type> *types, QVector<QByteArray> *typeNames)
{
    int pos = 0, begin = 0;

    // Find the position in the signature of the slot name
    int namePos = 0;
    while (buf[pos] && buf[pos] != '(') {
        if (buf[pos++] == ' ')
            namePos = pos;
    }

    // Retrieve the return type (default void)
    QByteArray retType("void");
    if (namePos > 0)
        retType = QByteArray(buf.constData(), namePos - 1);
    *types += QMetaType::Type(QSAQtCompat::typeIdForName(retType.constData()));
    *typeNames += retType;

    begin = ++pos;
    Q_ASSERT(begin>0);

    // Parse argument types
    while (pos < buf.size() && buf[pos]) {
        if ((buf[pos] == ',' || buf[pos] == ')') && pos-begin>0) {
            QByteArray param = QByteArray(buf.constData() + begin, pos-begin);
            QMetaType::Type t = (QMetaType::Type) QSAQtCompat::typeIdForName(param.constData());
            if (t == QMetaType::UnknownType) {
                QMetaType::Type vt = static_cast<QMetaType::Type>(QSAQtCompat::variantTypeForName(param.constData()));
                if (vt != QMetaType::UnknownType)
                    t = vt;
            }
            *types += t;
            *typeNames += param;

            begin = pos+1;
        }
        ++pos;
    }
}

int QSMetaObject::registerSlot(QObject *obj, const char *signature, PtrCallbackForSlot callback)
{
    int newId = m_slots.size();
    QByteArray buf = QMetaObject::normalizedSignature(signature);

    QVector<QMetaType::Type> types;
    QVector<QByteArray> typeNames;
    parseQtSignature(buf, &types, &typeNames);

    m_slots += QSSlot(types, typeNames, newId, callback, obj);
    m_slotnames[buf] = newId;

    return newId;
}

int QSMetaObject::qt_metacall(QMetaObject::Call c, int id, void **arguments)
{
    id = QSMetaObjectBase::qt_metacall(c, id, arguments);
    if (id < 0)
        return id;

    if (c == QMetaObject::InvokeMetaMethod || c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (c == QMetaObject::InvokeMetaMethod && id < m_slots.size())
            m_slots.at(id).call(arguments);
        id -= m_slots.size();
    }

    return id;
}

void *QSMetaObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, "QSMetaObject"))
        return static_cast<void*>(this);
    return QSMetaObjectBase::qt_metacast(_clname);
}

bool QSMetaObject::dynamicConnect(const QObject *sender, const char *signal, const char *method)
{
    QByteArray buf = QMetaObject::normalizedSignature(method);

    if (!QMetaObject::checkConnectArgs(signal, method))
        return false;

    int method_index;
    if (m_slotnames.contains(buf))
        method_index = m_slotnames.value(buf);
    else
        return false;

    return dynamicConnect(sender, signal, method_index);
}

bool QSMetaObject::dynamicConnect(const QObject *sender, const char *signal, int slot_id)
{
// ### sanity check would be nice here...
//     if (!QMetaObject::checkConnectArgs(signal, method))
//         return false;

    const QMetaObject *smeta = sender->metaObject();
    ++signal; //skip code
    int signal_index = smeta->indexOfSignal(signal);

    QByteArray tmp_signal_name;
    if (signal_index < 0) {
        // check for normalized signatures
        tmp_signal_name = QMetaObject::normalizedSignature(signal).prepend(*(signal - 1));
        signal = tmp_signal_name.constData() + 1;
        signal_index = smeta->indexOfSignal(signal);
        if (signal_index < 0)
            return false;
    }

    QMetaObject::connect(sender, signal_index, this, slot_id + slotOffset(),
                         Qt::AutoConnection, 0);

    return true;
}



bool QSMetaObject::dynamicDisconnect(const QObject *sender, const char *signal, int slot_id)
{
// ### sanity check would be nice here...
//     if (!QMetaObject::checkConnectArgs(signal, method))
//         return false;

    const QMetaObject *smeta = sender->metaObject();
    ++signal; //skip code
    int signal_index = smeta->indexOfSignal(signal);

    QByteArray tmp_signal_name;
    if (signal_index < 0) {
        // check for normalized signatures
        tmp_signal_name = QMetaObject::normalizedSignature(signal).prepend(*(signal - 1));
        signal = tmp_signal_name.constData() + 1;
        signal_index = smeta->indexOfSignal(signal);
        if (signal_index < 0)
            return false;
    }

    QMetaObject::disconnect(sender, signal_index, this, slot_id + slotOffset());

    return true;
}

