#include "myview.h"

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent),
    isDeprecated(false) {
    setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qApp->setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
    lastTwoFingerPos = QPointF(-1, -1);
}

bool MyView::viewportEvent(QEvent *event) {
    qDebug() << event->type();
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchEnd:
        lastTwoFingerPos = QPointF(-1, -1);
    case QEvent::TouchUpdate:
    case QEvent::TouchCancel:
    case QEvent::Gesture:
    {
        QTouchEvent* touchEvent = dynamic_cast<QTouchEvent*> (event);
        if (touchEvent) {
            if (touchEvent->touchPoints().size() > 1) {        // change canvas postiont by 2 fingers
                isDeprecated = true;
                QPointF curTwoFingerPos = QPointF(touchEvent->touchPoints()[0].pos() + touchEvent->touchPoints()[1].pos()) / 2;
                if (lastTwoFingerPos != QPointF(-1, -1)) {
                    int x = lastTwoFingerPos.x() - curTwoFingerPos.x();
                    int y = lastTwoFingerPos.y() - curTwoFingerPos.y();
                    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + x);
                    verticalScrollBar()->setValue(verticalScrollBar()->value() + y);
                }
                lastTwoFingerPos = curTwoFingerPos;
            } else {
                isDeprecated = false;
            }
        }
        return true;
    }
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        if (isDeprecated) {
            qDebug() << "depracted";
            return true;
        } else {
            qDebug() << "mouse";
        }
        break;
    default:
        qDebug() << event->type();
        break;
    }
    return QGraphicsView::viewportEvent(event);

}
