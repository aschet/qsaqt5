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

#include <QtCore/QVariant>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

struct qt_meta_stringdata_QSMetaObject_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSMetaObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSMetaObject_t qt_meta_stringdata_QSMetaObject = {
    {
QT_MOC_LITERAL(0, 0, 12) // "QSMetaObject"

    },
    "QSMetaObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSMetaObject[] = {

    // content:
          8,       // revision
          0,       // classname
          0,    0, // classinfo
          0,    0, // methods
          0,    0, // properties
          0,    0, // enums/sets
          0,    0, // constructors
          0,       // flags
          0,       // signalCount

          0        // eod
};

QT_INIT_METAOBJECT const QMetaObject QSMetaObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QSMetaObject.data,
    qt_meta_data_QSMetaObject,
    nullptr,
    nullptr,
    nullptr
} };

#else

namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSQSMetaObjectENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSQSMetaObjectENDCLASS = QtMocHelpers::stringData(
    "QSMetaObject"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQSMetaObjectENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQSMetaObjectENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQSMetaObjectENDCLASS_t qt_meta_stringdata_CLASSQSMetaObjectENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12)   // "QSMetaObject"
    },
    "QSMetaObject"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQSMetaObjectENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QSMetaObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSQSMetaObjectENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQSMetaObjectENDCLASS,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQSMetaObjectENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QSMetaObject, std::true_type>
    >,
    nullptr
} };

#endif

QSMetaObject::QSMetaObject(QObject *parent) : QObject(parent)
{ }

QSMetaObject::~QSMetaObject()
{ }

const QMetaObject *QSMetaObject::metaObject()
{ return &staticMetaObject; }

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
    *types += QMetaType::Type(QMetaType::type(retType.constData()));
    *typeNames += retType;

    begin = ++pos;
    Q_ASSERT(begin>0);

    // Parse argument types
    while (pos < buf.size() && buf[pos]) {
        if ((buf[pos] == ',' || buf[pos] == ')') && pos-begin>0) {
            QByteArray param = QByteArray(buf.constData() + begin, pos-begin);
            QMetaType::Type t = (QMetaType::Type) QMetaType::type(param.constData());
            if (t == 0) {
                QMetaType::Type vt = static_cast<QMetaType::Type>(QVariant::nameToType(param.constData()));
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
    QByteArray buf = staticMetaObject.normalizedSignature(signature);

    QVector<QMetaType::Type> types;
    QVector<QByteArray> typeNames;
    parseQtSignature(buf, &types, &typeNames);

    m_slots += QSSlot(types, typeNames, newId, callback, obj);
    m_slotnames[buf] = newId + staticMetaObject.methodOffset();

    return newId;
}

int QSMetaObject::qt_metacall(QMetaObject::Call c, int id, void **arguments)
{
    if (c != QMetaObject::InvokeMetaMethod)
        QObject::qt_metacall(c, id, arguments);

    id -= staticMetaObject.methodOffset();
    Q_ASSERT(id >= 0 && id < m_slots.size());

    m_slots.at(id).call(arguments);

    return 0;
}

void *QSMetaObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (!strcmp(_clname, qt_meta_stringdata_QSMetaObject.stringdata0))
#else
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQSMetaObjectENDCLASS.stringdata0))
#endif
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

bool QSMetaObject::dynamicConnect(const QObject *sender, const char *signal, const char *method)
{
    QByteArray buf = staticMetaObject.normalizedSignature(method);

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

    QMetaObject::connect(sender, signal_index, this, slot_id + staticMetaObject.methodOffset(),
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

    QMetaObject::disconnect(sender, signal_index, this, slot_id + staticMetaObject.methodOffset());

    return true;
}

