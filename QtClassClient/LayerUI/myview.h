#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QEvent>
#include <QTimer>
#include <QGroupBox>
#include <QToolButton>
#include <QPaintEvent>
#include <QHBoxLayout>
#include "../Reliable/DataUnit/CMessage.h"
#include "../player/absplayer.h"
#include "../Message/CMsgObject.h"

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

    inline void setMsgObject(CMsgObject* in) { msg = in; }

    void playCourseware(QString filepath);

signals:
    void screenMoved(QPoint p);

public slots:
    void pstop();
    void pprev();
    void pnext();

private:
    enum PaintMode pm;
    AbsPlayer*   player;

    QToolButton *prev;
    QToolButton *next;
    QToolButton *stop;

    CMsgObject* msg;
};

#endif // MYVIEW_H
