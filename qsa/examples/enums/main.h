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
#ifndef MAIN_H
#define MAIN_H

#include <qsinterpreter.h>

/* Provide an object that will represent the static part of the Direction class,
 * allowing scripters to write contructs like:
 *
 * var x = Direction.LeftToRight;
 *
 * The key is the Q_ENUMS() declaration which exports the enum Mode via through
 * moc, which makes it available to QSA.
 */
class DirectionStatic : public QObject
{
    Q_OBJECT
    Q_OVERRIDE(QString objectName SCRIPTABLE false)
    Q_ENUMS(Mode)
public:
    enum Mode { Undefined, LeftToRight, RightToLeft };
};

/* Proved the class that will represent the instances in the script. Notice
 * that this class redeclares the enum mode so that it will be possible
 * to write constructions like:
 *
 * var x = dir.LeftToRight;
 *
 * where 'x' is an instance of the direction class.
 */
class Direction : public QObject
{
    Q_OBJECT
    Q_OVERRIDE(QString objectName SCRIPTABLE false)
    Q_ENUMS(Mode)
public:
    enum Mode { Undefined, LeftToRight, RightToLeft };

    Direction(QSInterpreter *interp) : d(Undefined), ip(interp) { };

public slots:
    bool isLeftToRight() const { return d == LeftToRight; }
    bool isRightToLeft() const { return d == RightToLeft; }

    void setMode(int mode) {
        if (mode == LeftToRight || mode == RightToLeft)
            d = Mode(mode);
        else
            ip->throwError("mode must be Direction.LeftToRight or Direction.RightToLeft");
    }

private:
    Mode d;
    QSInterpreter *ip;
};

#endif