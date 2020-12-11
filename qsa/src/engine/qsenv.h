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

#ifndef QSENV_H
#define QSENV_H

#include "qsobject.h"
#include "qsclasslist.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

class QSEngine;
class QSClass;
class QSObjectClass;
class QSUndefinedClass;
class QSNullClass;
class QSBooleanClass;
class QSNumberClass;
class QSStringClass;
class QSCharacterClass;
class QSFunctionClass;
class QSTypeClass;
class QSDateClass;
class QSMathClass;
class QSRegExpClass;
class QSArrayClass;
class QSErrorClass;
class QSArgumentsClass;
class QSDynamicClass;
class QSGlobalClass;
class QSFuncRefClass;
class QSDebugClass;
class QSSystemClass;

typedef QList<QSObject> ScopeChain;

class QSEnv {
public:
    enum ExecutionMode { Normal, Break, Continue, ReturnValue, Throw };
    QSEnv(QSEngine *e);
    ~QSEnv();
    void init();
    void clear();

    QSEngine* engine() const { return eng; }

    void pushScopeBlock();
    void pushScope(const QSObject &scope);
    void popScope();
    void popScopeBlock();
    ScopeChain scope() const;
    QSObject currentScope() const;
    void clearScopeChain();
    void printScopeChain() const;
    QSObject thisValue() const;
    void setThisValue(const QSObject &t);
    const QSClass* thisClass() const { return thisValue().objectType(); }
    QSObject globalObject() const;
    QSObject getValueDirect(int index, int level);
    void setValueDirect(int index, int level, const QSObject &value);
    QSObject scopeObjectAt(int level) const;

    QSClass* classByName(const QString &n);
    QSClass* classByIdentifier(const QString &n);

    void pushLabel(const QString &l);
    void popLabel();
    bool containsLabel(const QString &l) const;
    QString currentLabel() const { return label; }
    void setCurrentLabel(const QString &l) { label = l; }
    bool isCurrentLabelValid() const;

    QSObjectClass *objectClass() const { return objClass; }
    QSNullClass *nullClass() const { return nilClass; }
    QSUndefinedClass *undefinedClass() const { return undefClass; }
    QSNumberClass *numberClass() const { return numClass; }
    QSBooleanClass *booleanClass() const { return boolClass; }
    QSStringClass *stringClass() const { return strClass; }
    QSTypeClass *typeClass() const { return typClass; }
    QSErrorClass *errorClass() const { return errClass; }
    QSArrayClass *arrayClass() const { return arrClass; }
    QSDateClass *dateClass() const { return datClass; }
    QSRegExpClass *regexpClass() const { return regClass; }
    QSMathClass *mathClass() const { return matClass; }
    QSFuncRefClass *funcRefClass() const { return refClass; }
    QSDebugClass *debugClass() const { return dbgClass; }
    QSSystemClass *systemClass() const { return sysClass; }

    // internal
    QSGlobalClass *globalClass() const { return globClass; }
    QSArgumentsClass *argumentsClass() const { return argsClass; }
    QSDynamicClass *dynamicClass() const { return dynClass; }

    void registerClass(QSClass *cl);
    void unregisterClass(QSClass *cl);

    QSObject resolveValue(const QString &n) const;

    const QList<QSClass *> &classes() const { return classList; }

    QSObject throwError(ErrorType e, const QString &m = QString(),
			 int l = -1);
    QSObject throwError(const QString &msg);

    void setException(const QSObject &e);
    void setException(const QString &msg);
    QSObject exception();
    void clearException();

    void setExecutionMode(ExecutionMode mode);
    ExecutionMode executionMode() const { return execMode; }
    bool isNormalMode() const { return execMode==Normal; }
    bool isExceptionMode() const { return execMode==Throw; }
    bool isBreakMode() const { return execMode==Break; }
    bool isContinueMode() const { return execMode==Continue; }
    bool isReturnValueMode() const { return execMode==ReturnValue; }

    void setArguments(const QSList *lst) { args = lst; }
    const QSList* arguments() const { return args; }
    QSObject arg(int index) const { return index>=args->size() || index<0 ?
						    createUndefined() : args->at(index); }
    int numArgs() const { return args->size(); }

    QSObject createNumber(double n) const;
    QSObject createBoolean(bool b) const;
    QSObject createString(const QString &s) const;
    QSObject createUndefined() const;
    QSObject createNull() const;

    QSObject createShared(const QSClass *cl, QSShared *sh) const;
    void registerShared(QSShared *sh) const;
    void removeShared(QSShared *sh) const;
    bool isShuttingDown() const { return shutDown; }

    int stackDepth() const { return stackDep; }
    void incrStackDepth() { ++stackDep; }
    void decrStackDepth() { --stackDep; }

private:
    QSEngine *eng;

    QSObjectClass *objClass;
    QSUndefinedClass *undefClass;
    QSNullClass *nilClass;
    QSBooleanClass *boolClass;
    QSNumberClass *numClass;
    QSStringClass *strClass;
    QSCharacterClass *charClass;
    QSTypeClass *typClass;
    QSDateClass *datClass;
    QSMathClass *matClass;
    QSRegExpClass *regClass;
    QSArrayClass *arrClass;
    QSErrorClass *errClass;
    QSGlobalClass *globClass;
    QSArgumentsClass *argsClass;
    QSDynamicClass *dynClass;
    QSFuncRefClass * refClass;
    QSDebugClass *dbgClass;
    QSSystemClass *sysClass;

    ScopeChain * scopeChain;
    QSObject thVal;
    QSClassList classList;
    QStringList labels;
    QString label;
    const QSList *args;
    QSShared *sharedList;

    // exception
    QString exMsg;
    QSObject exVal;
    QSObject retVal;

    ExecutionMode execMode;

    int stackDep;

    uint shutDown : 1;
};


inline QSObject QSEnv::createNumber(double value) const
{
    return QSNumber(this, value);
}


inline QSObject QSEnv::createBoolean(bool b) const
{
    return QSBoolean(this, b);
}

inline QSObject QSEnv::createUndefined() const
{
    return QSUndefined(this);
}

inline QSObject QSEnv::createString(const QString &s) const
{
    return QSString(this, s);
}

inline QSObject QSEnv::createNull() const
{
    return QSNull(this);
}


#endif
