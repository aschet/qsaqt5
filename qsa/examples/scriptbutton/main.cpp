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
#include "scriptbutton.h"

#include <qsinterpreter.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMessageBox>
#include "widgetwrapper.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
#ifndef QSA_NO_EDITOR
    QWidget widget;
    QSProject project;
    QVBoxLayout *vboxLayout = new QVBoxLayout(&widget);

    // some help text
    QLabel *help = new QLabel("Right-click on any of the buttons to edit "
                              "its properties.");
    vboxLayout->addWidget(help);

    QWidget *hboxWidget = new QWidget;
    QHBoxLayout *hboxLayout = new QHBoxLayout(hboxWidget);
    vboxLayout->addWidget(hboxWidget);

    // create two sample widgets
    QGroupBox *lcdGroup = new QGroupBox( "lcd");
    hboxLayout->addWidget(lcdGroup);

    QVBoxLayout *lcdgroupLayout = new QVBoxLayout(lcdGroup);
    QLCDNumber *lcd = new QLCDNumber;
    lcd->setObjectName("lcd");
    lcdgroupLayout->addWidget(lcd);
    project.addObject(lcd);
    lcdgroupLayout->addWidget(new QLabel("Properties: <ul><li>value</li>"
                                         "<li>setHexMode()</li><li>...</li></ul>"));

    QGroupBox *editGroup = new QGroupBox( "edit");
    hboxLayout->addWidget(editGroup);

    QVBoxLayout *editgroupLayout = new QVBoxLayout(editGroup);
    QLineEdit *edit = new QLineEdit;
    edit->setObjectName("edit");
    edit->setText( "text" );
    editgroupLayout->addWidget(edit);
    project.addObject(edit);
    editgroupLayout->addWidget(new QLabel("Properties: <ul><li>text</li><li>maxLength</li>"
                                          "<li>clear()</li><li>...</li></ul>"));

    QWidget *buttonWidget = new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonWidget);
    hboxLayout->addWidget(buttonWidget);

    // add script buttons
    ScriptButton *button1 = new ScriptButton(&project, "Increase Counter", 0, "button1");
    buttonLayout->addWidget(button1);
    button1->setScriptCode( "Application.lcd.value++;" );

    ScriptButton *button2 = new ScriptButton(&project, "Reset Counter", 0, "button2");
    buttonLayout->addWidget(button2);
    button2->setScriptCode( "Application.lcd.value = 0;" );

    ScriptButton *button3 = new ScriptButton(&project, "Convert to uppercase", 0, "button3");
    buttonLayout->addWidget(button3);
    button3->setScriptCode( "Application.edit.text = Application.edit.text.upper();" );

    QPushButton *button4 = new QPushButton("&Quit");
    button4->setObjectName("button4");
    buttonLayout->addStretch(-1);
    buttonLayout->addWidget(button4);
    QObject::connect(button4, SIGNAL(clicked()), &app, SLOT(quit()));

    // teach interpreter about widgets
    project.interpreter()->addWrapperFactory( new WidgetWrapperFactory() );
    project.interpreter()->addObjectFactory( new QtNamespaceProvider() );

    widget.show();
#else
    QMessageBox::information( 0, "Disabled feature",
			      "QSA Editor has been disabled. Reconfigure to enable",
			      QMessageBox::Ok );
#endif

    return app.exec();
}
