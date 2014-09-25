#include "myview.h"

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    lastTwoFingerPos = QPointF(-1, -1);
}

bool MyView::viewportEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::TouchBegin:
        lastTwoFingerPos = QPointF(-1, -1);
    case QEvent::TouchEnd:
    case QEvent::TouchUpdate:
    {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        if (touchEvent) {
            if (2 == touchEvent->touchPoints().size()) {        // change canvas postiont by 2 fingers
                QPointF curTwoFingerPos = QPointF(touchEvent->touchPoints()[0].pos() + touchEvent->touchPoints()[1].pos()) / 2;
                if (lastTwoFingerPos != QPointF(-1, -1)) {
                    int x = lastTwoFingerPos.x() - curTwoFingerPos.x();
                    int y = lastTwoFingerPos.y() - curTwoFingerPos.y();
                    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + x);
                    verticalScrollBar()->setValue(verticalScrollBar()->value() + y);
                }
                lastTwoFingerPos = curTwoFingerPos;
                return true;
            }
        }
        break;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

