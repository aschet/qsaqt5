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
#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) 
: QMainWindow(parent)
{
    setupUi(this);
    init();
}

static QString loadFile(const QString &name)
{
    QFile file(name);
    if (!file.open(QFile::ReadOnly)) {
        qDebug("Can't open file %s", qPrintable(name));
        return QString();
    }
    QTextStream str(&file);
    return str.readAll();
}

void GameWindow::init()
{
    connect(startButton, SIGNAL(clicked()), this, SLOT(startTimer()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopTimer()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(playField, SIGNAL(gameCompleted()), this, SLOT(stopTimer()));
    connect(&qsa, SIGNAL(error(const QString &, const QString &, int)),
        this, SLOT(stopTimer()));
    ok = true;
}

void GameWindow::timeout()
{
    qsa.call("next", QVariantList(), playField);
    playField->update();
}

void GameWindow::startTimer()
{
    ok = true;
    QString code = loadFile(combo->currentText());
    if(code.isNull()) {
        QMessageBox::warning(this, "Failed to load file",
            "The file containing the script code could not be loaded");
        return;
    }
    playField->clear();
    playField->setFocus();
    qsa.clear();
    qsa.evaluate(code, playField);
    if (!ok)
        return;
    qsa.call("init", QVariantList(), playField);
    startButton->setEnabled(false);
    stopButton->setEnabled(true);
    timer.start(25);
}

void GameWindow::stopTimer()
{
    ok = false;
    timer.stop();
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
}
