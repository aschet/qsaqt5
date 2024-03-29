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

#include "linenumberwidget.h"
#include "qsaeditor.h"
#include <QtWidgets/QScrollBar>
#include <QtGui/QPainter>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QTextBlock>

LineNumberWidget::LineNumberWidget(QSAEditor *_editor, QWidget *parent)
    : QWidget(parent), editor(_editor)
{
    setFixedWidth(fontMetrics().horizontalAdvance(QLatin1String("0000")) + 20);
    connect(editor->document()->documentLayout(), SIGNAL(update(const QRectF &)),
            this, SLOT(update()));
    connect(editor->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(update()));
}

void LineNumberWidget::paintEvent(QPaintEvent *)
{
    int contentsY = editor->verticalScrollBar()->value();
    qreal pageBottom = contentsY + editor->viewport()->height();
    int lineNumber = 1;
    const QFontMetrics fm = fontMetrics();
    const int ascent = fontMetrics().ascent() + 1; // height = ascent + descent + 1

    QPainter p(this);

    for (QTextBlock block = editor->document()->begin();
         block.isValid(); block = block.next(), ++lineNumber) {
        QTextLayout *layout = block.layout();

        const QRectF boundingRect = layout->boundingRect();
        QPointF position = layout->position();
        if (position.y() + boundingRect.height() < contentsY)
            continue;
        if (position.y() > pageBottom)
            break;

        const QString txt = QString::number(lineNumber);
        p.drawText(width() - fm.horizontalAdvance(txt), qRound(position.y()) - contentsY + ascent, txt);
    }
}

