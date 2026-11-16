#ifndef QSAQTCOMPAT_H
#define QSAQTCOMPAT_H

#include <QtCore/QByteArray>
#include <QtCore/QMetaProperty>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>

// Helpers that hide the differences between the meta type APIs of Qt 5 and Qt 6.
// All type ids are plain ints holding QMetaType::Type values; 0 is QMetaType::UnknownType.
namespace QSAQtCompat {

// Type id of a variant. Qt 5 maps all custom types to QVariant::UserType, Qt 6 reports the real id.
inline int variantType(const QVariant &v)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return int(v.type());
#else
    return v.typeId();
#endif
}

// Type id registered for a type name, UnknownType if the name is not registered.
inline int typeIdForName(const char *name)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return QMetaType::type(name);
#else
    return QMetaType::fromName(name).id();
#endif
}

// Same as typeIdForName() but results are comparable with variantType().
inline int variantTypeForName(const char *name)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return int(QVariant::nameToType(name));
#else
    return QMetaType::fromName(name).id();
#endif
}

// Default constructed variant holding a value of the given type.
inline QVariant defaultVariant(int type)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return QVariant(QVariant::Type(type));
#else
    return QVariant(QMetaType(type));
#endif
}

// Variant of the given type holding a copy of the value pointed to by data.
inline QVariant variantFromData(int type, const void *data)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return QVariant(type, data);
#else
    return QVariant(QMetaType(type), data);
#endif
}

// Type id used to convert script values for a property. Enums and flags are
// reported with their own type (Qt 6) or as a user type (Qt 5), scripts only
// deal with int for them.
inline int propertyType(const QMetaProperty &property)
{
    if (property.isEnumType())
        return int(QMetaType::Int);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return int(property.type());
#else
    return property.typeId();
#endif
}

}

#endif // QSAQTCOMPAT_H
