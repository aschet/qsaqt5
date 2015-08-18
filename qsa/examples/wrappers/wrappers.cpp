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
#include <qsinterpreter.h>
#include <qswrapperfactory.h>

#include <QtWidgets/QApplication>
#include <QtCore/QFile>

#include <QtWidgets/QListWidget>


/* Wrapper for QListWidget that gives access to the functions
 * palette() and setPalette();
 */
class ListViewWrapper : public QObject
{
    Q_OBJECT
public:
    ListViewWrapper(QListWidget *l) : listView(l) { }

public slots:
    QPalette palette() const { return listView->palette(); }
    void setPalette(const QPalette &palette) { listView->setPalette(palette); }

private:
    QListWidget *listView;
};


/* Wrapper for QListWidgetItem that gives access to the items text
 */
class ItemWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    ItemWrapper(QListWidgetItem *i) : item(i) { };

    QString text() const { return item->text(); }
    void setText(const QString &txt) { item->setText(txt); }
private:
    QListWidgetItem *item;
};


class Wrappers : public QSWrapperFactory
{
public:
    Wrappers()
    {
	// Tell the factory what which classes we provide wrappers for.
	registerWrapper("QListWidget");
	registerWrapper("QListWidgetItem");

}
    QObject *create(const QString &name, void *ptr)
    {
	if (name == "QListWidget")
	    return new ListViewWrapper((QListWidget *)ptr);
	else if (name == "QListWidgetItem")
	    return new ItemWrapper((QListWidgetItem *)ptr);
	return 0;
    }
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Get the script to load...
    QString fileName = "test.qs";
    if (argc > 1)
	fileName = argv[1];
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
	printf("Could not open file: %s, %s\n", qPrintable(fileName),
	       qPrintable(file.errorString()));
	return 1;
    }
    QString script(file.readAll());

    // Create my list view
    QListWidget *listView = new QListWidget(0);
    listView->setObjectName("listView");
//     listView->addColumn("1");
    listView->addItem("Red");
    listView->addItem("Blue");
    listView->addItem("Green");
    listView->addItem("Cyan");
    listView->addItem("Yellow");
    listView->addItem("Purple");
    listView->addItem("Orange");
    listView->addItem("Gray");

    // Create interpreter and add listview and factory to it. Order here is
    // important since adding a wrapper factory will reset the interpreter.
    QSInterpreter ip;
    ip.addWrapperFactory(new Wrappers());
    ip.addTransientObject(listView);

    ip.evaluate(script, 0, fileName);

    listView->show();

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    return app.exec();
}

#include "wrappers.moc"
