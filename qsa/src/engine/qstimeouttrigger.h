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

#ifndef QSTIMEOUTTRIGGER_H
#define QSTIMEOUTTRIGGER_H

#include <QtCore/QObject>
#include <QtCore/QElapsedTimer>

class QSTimeoutTrigger : public QObject
{
    Q_OBJECT
public:
    QSTimeoutTrigger() : QObject() { }
    inline void start() { time.start(); lastTimeout = 0; }
    inline void fireTimeout()
    {
	if (time.elapsed()-lastTimeout >= ival) {
	    lastTimeout = time.elapsed();
	    emit timeout(lastTimeout);
	}
    }

    void setInterval(int i) { ival = i; }
    int interval() const { return ival; }

signals:
    void timeout(int runningTime);

private:
    QElapsedTimer time;
    int lastTimeout;
    int ival;
};

#endif // QSTIMEOUTTRIGGER_H
