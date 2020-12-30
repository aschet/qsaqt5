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

#include "qsengine.h"
#include "qsobject.h"
#include "qsenv.h"
#include "qsoperations.h"
#include "qsinternal.h"
#include "qslexer.h"
#include "qsnodes.h"
#include "qsclass.h"
#include "qscheck.h"
#include "qsnumeric.h"

#include "qsobject_object.h"
#include "qsfuncref.h"
#include "qsarray_object.h"
#include "qsbool_object.h"
#include "qsnumber_object.h"
#include "qsmath_object.h"
#include "qsdate_object.h"
#include "qsregexp_object.h"
#include "qserror_object.h"

#include <QtCore/QMutex>
#include <QtCore/QRegularExpression>

#include <stdio.h>
#include <string.h>

extern int qsyyparse();

using namespace QS;

static void postfixAdd( const QSClass *cl, QSCheckData *data )
{
    if( cl->enclosingClass() )
	postfixAdd( cl->enclosingClass(), data );
    // ### We should be doing correct enterXXX, but since we are not doing
    // any validation of the code, only add it for lookup by the eval
    // it should not make a difference.
    data->enterClass( (QSClass*) cl );
}

extern QMutex *qsa_lexer_mutex();

// eval()
static QSObject qsEval( QSEnv *env )
{
    QSObject x = env->arg( 0 );
    if ( !x.isString() ) {
	return x;
    } else {
	QSEngineImp *eimp = env->engine()->imp();
	QString s = x.toString();
	QSNode *progNode = 0;
	{ // begin mutext locker
            QMutexLocker locker(qsa_lexer_mutex());
            QSLexer::lexer()->setCode( s,
#ifdef QSDEBUGGER
                                       eimp->sourceId()
#else
                                       0
#endif
                                       );
            int yp = qsyyparse();
            progNode = QSProgramNode::last();
            if ( yp || QSLexer::lexer()->lexerState() == QSLexer::Bad ) {
                if (!progNode && progNode->deref())
                    delete progNode;
                return env->throwError( SyntaxError );
            }
	} // end mutext locker

	QSCheckData data( env );
	QSObject scopeTop = env->currentScope();
	postfixAdd( scopeTop.objectType(), &data );
	QSEvalScopeClass *cl = new QSEvalScopeClass( env->objectClass() );
	data.enterEval( cl );

	progNode->check( &data );
	if ( data.hasError() ) {
	    if (!progNode->deref())
		delete progNode;
	    return env->throwError( EvalError,
				    data.errorMessages().first(),
				    data.errorLines().first() );
	}

        QSList empty;
	env->pushScope( cl->construct( empty ) );
	// ### delete tmp scope class

	QSObject res = ((QSProgramNode*)progNode)->execute( env );

	if (!progNode->deref())
	    delete progNode;

	env->popScope();

	if ( env->isReturnValueMode() )
	  return res;
	else if ( env->isNormalMode() ) {
	    if ( res.isValid() )
		return res;
	    else
		return env->createUndefined();
	} else
	    return res;
    }
}


static QRegularExpression qs_regexp_for_radix(int radix)
{
    if (radix <= 10) {
        return QRegularExpression(QString(QString::fromLatin1("\\w*(-?[0-%1]+)")).arg(radix-1));
    } else if (radix == 16) {
        return QRegularExpression(QString(QString::fromLatin1("\\w*(-?[0-9a-fA-Fx]+)")));
    } else {
        return QRegularExpression(QString(QString::fromLatin1("\\w*(-?[0-9a-%1A-%2]+)")).arg('a'+(radix-9)).arg('A'+(radix-9)));
    }
}

// parseInt()
static QSObject qsParseInt( QSEnv *env )
{
    if( env->numArgs() < 1 )
	return QSObject();
    QString str = env->arg( 0 ).toString();
    int radix;
    if (env->numArgs()==1) {
	if (str.startsWith(QString::fromLatin1("0x")))
	    radix = 16;
	else if (str.startsWith(QString::fromLatin1("0")))
	    radix = 8;
	else
	    radix = 10;
    } else {
	radix = env->arg( 1 ).toInt32();
	if (radix < 2 || radix > 36 )
	    return env->createNumber(NaN);
    }

    QRegularExpression re = qs_regexp_for_radix(radix);
    Q_ASSERT(re.isValid());
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
        str = match.captured(1);
        bool ok = false;
        int val = str.toInt(&ok, radix);
        if (ok)
            return env->createNumber(val);
    }

    return env->createNumber(NaN);
}

// parseFloat()
static QSObject qsParseFloat( QSEnv *env )
{
    QRegularExpression re(QString::fromLatin1("[+-]?(\\d*)(\\.(\\d*))?([Ee]([+-]?\\d+))?"));
    Q_ASSERT(re.isValid());
    QString str = env->arg( 0 ).toString().trimmed();
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
        str = match.captured(0);
        bool ok = false;
        double value = str.toDouble(&ok);
        if (ok)
            return env->createNumber(value);
    }
    return env->createNumber(NaN);
}

// isNaN()
static QSObject qsIsNaN( QSEnv * env )
{
    return env->createBoolean( qsaIsNan( env->arg( 0 ).toNumber() ) );
}

// isFinite()
static QSObject qsIsFinite( QSEnv *env )
{
    double n = env->arg( 0 ).toNumber();
    return env->createBoolean( !qsaIsNan( n ) && !qsaIsInf( n ) );
}

// escape()
static QSObject qsEscape( QSEnv *env )
{
    const char non_escape[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789@*_+-./";
    QString r = QString::fromLatin1(""), str = env->arg( 0 ).toString();
    const QChar *c = str.unicode();
    for ( int k = 0; k < str.length(); k++, c++ ) {
	int u = c->unicode();
	if ( u > 255 ) {
	    char tmp[7];
	    sprintf(tmp, "%%u%04X", u);
	    r += QString::fromLatin1(tmp);
	} else if (strchr(non_escape, (char)u)) {
	    r += *c;
	} else {
	    char tmp[4];
	    sprintf(tmp, "%%%02X", u);
	    r += QString::fromLatin1(tmp);
	}
    }
    return env->createString( r );
}

// unescape()
static QSObject qsUnescape( QSEnv *env )
{
    QString s, str = env->arg( 0 ).toString();
    int k = 0, len = str.length();
    while ( k < len ) {
	const QChar *c = str.unicode() + k;
	QChar u;
	if ( *c == QChar('%') && k <= len - 6 && *(c+1) == QChar('u') ) {
	    u = QSLexer::convertUnicode( (c+2)->unicode(), (c+3)->unicode(),
					 (c+4)->unicode(), (c+5)->unicode() );
	    c = &u;
	    k += 5;
	} else if ( *c == QChar('%') && k <= len - 3 ) {
	    u = QChar( QSLexer::convertHex( (c+1)->unicode(),
					    (c+2)->unicode() ) );
	    c = &u;
	    k += 2;
	}
	k++;
	s += QString(c, 1);
    }
    return env->createString( s );
}

QSGlobalClass::QSGlobalClass( QSClass *b )
  : QSWritableClass( b )
{
    // ### DontEnum
    addMember( QString::fromLatin1("eval"), QSMember( &qsEval ) );
    addMember( QString::fromLatin1("parseInt"), QSMember( &qsParseInt ) );
    addMember( QString::fromLatin1("parseFloat"), QSMember( &qsParseFloat ) );
    addMember( QString::fromLatin1("isNaN"), QSMember( &qsIsNaN ) );
    addMember( QString::fromLatin1("isFinite"), QSMember( &qsIsFinite ) );
    addMember( QString::fromLatin1("escape"), QSMember( &qsEscape ) );
    addMember( QString::fromLatin1("unescape"), QSMember( &qsUnescape ) );

    addStaticVariableMember( QString::fromLatin1("NaN"), createNumber(NaN), AttributePublic );
    addStaticVariableMember( QString::fromLatin1("Infinity"), createNumber(Inf), AttributePublic );
    addStaticVariableMember( QString::fromLatin1("undefined"), createUndefined(), AttributePublic );
}

Global::Global( QSEngine *e )
    : eng( e )
{
}

void Global::init()
{
    QSEnv *e = eng->rep->env();
    clss = e->globalClass();
    QSInstanceData *data = new QSInstanceData( clss->numVariables(),
					       e->createUndefined() );
    e->registerShared( data );
    setVal( data );

    eng->registerType( e->objectClass() );
    eng->registerType( e->funcRefClass() );
    eng->registerType( e->arrayClass() );
    eng->registerType( e->stringClass() );
    eng->registerType( e->booleanClass() );
    eng->registerType( e->numberClass() );
    eng->registerType( e->dateClass() );
    eng->registerType( e->regexpClass() );
    eng->registerType( e->typeClass() );
    eng->registerType( e->errorClass() );
    eng->registerType( e->debugClass() );
    eng->registerType( e->systemClass() );

    // other properties
    eng->registerType( e->mathClass() );

    e->pushScope( * this );
}

void Global::clear()
{
}
