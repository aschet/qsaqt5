/****************************************************************************
**
** Copyright (C) 1992-$THISYEAR$ Trolltech AS. All rights reserved.
**
** This file is part of the $MODULE$ of the Qt Toolkit.
**
** $LICENSE$
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef ARGHINTWIDGET_H
#define ARGHINTWIDGET_H

#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QMap>

class QLabel;
class ArrowButton;

class ArgHintWidget : public QFrame
{
    Q_OBJECT

public:
    ArgHintWidget(QWidget *parent, const char*name);

    void setFunctionText(int func, const QString &text);
    void setNumFunctions(int num);

public slots:
    void relayout();
    void gotoPrev();
    void gotoNext();

private:
    void updateState();

private:
    int curFunc;
    int numFuncs;
    QMap<int, QString> funcs;
    QLabel *funcLabel;
    ArrowButton *prev, *next;

};

class ArrowButton : public QPushButton
{
	Q_OBJECT

public:
	enum Dir { Left, Right };

	ArrowButton(QWidget *parent, const char *name, Dir d);
	void drawButton(QPainter *p);

private:
	QPixmap pix, pix_disabled;

};

#endif
