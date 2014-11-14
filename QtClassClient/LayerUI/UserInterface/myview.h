#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QEvent>
#include <QTimer>
#include <QGroupBox>
#include <QToolButton>
#include <QPaintEvent>
#include <QHBoxLayout>
#include "../../Reliable/DataUnit/CMessage.h"
#include "../MsgGenerator/cplayergenerator.h"

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);

    ~MyView();

    bool viewportEvent(QEvent *event);

    void moveScreen(QPoint p);

    void buildPlayer();     // build media player button

    QTimer panTimer;        // gesture -> move
    bool isLeftClicked;

    void setPaintMode(enum PaintMode in);

signals:
    void screenMoved(QPoint p);


private:
    void hideButtons(bool hide = true);

private:
    enum PaintMode pm;

    QList<QToolButton*> ctrllist;

    bool        isWareStarted;
};

#endif // MYVIEW_H
