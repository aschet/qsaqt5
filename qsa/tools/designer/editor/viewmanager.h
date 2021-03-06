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

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QtWidgets/QWidget>
#include <QtCore/QList>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QResizeEvent>
#include <QtCore/QChildEvent>

class QChildEvent;
class MarkerWidget;
class QVBoxLayout;
class Q3TextParagraph;
class QLabel;
class QTimer;

class ViewManager : public QWidget
{
    Q_OBJECT
public:
    ViewManager(QWidget *parent, const char *name);

    void addView(QWidget *view);
    QWidget *currentView() const;
    void showMarkerWidget(bool);

    void setError(int line);
    void setStep(int line);
    void setStackFrame(int line);
    void clearStep();
    void clearStackFrame();
    void setBreakPoints(const QList<uint> &l);
    QList<uint> breakPoints() const;

    void emitMarkersChanged();
    MarkerWidget *marker_widget() const { return markerWidget; }

signals:
    void markersChanged();
    void expandFunction(Q3TextParagraph *p);
    void collapseFunction(Q3TextParagraph *p);
    void collapse(bool all /*else only functions*/);
    void expand(bool all /*else only functions*/);
    void editBreakPoints();
    void isBreakpointPossible(bool &possible, const QString &code, int line);

protected slots:
    void clearErrorMarker();
    void cursorPositionChanged(int row, int col);
    void showMessage(const QString &msg);
    void clearStatusBar();

protected:
    void childEvent(QChildEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    QWidget *curView;
    MarkerWidget *markerWidget;
    QVBoxLayout *layout;
    QLabel *posLabel;
    QString extraText;
    QTimer *messageTimer;

};

#endif
