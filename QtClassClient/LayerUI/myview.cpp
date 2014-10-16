#include "myview.h"

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent) {
    //setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    panTimer.setSingleShot(true);
    setAttribute(Qt::WA_AcceptTouchEvents);
}

bool MyView::viewportEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::Gesture:
    {
        QGestureEvent* ge = static_cast<QGestureEvent*> (event);
        if (QGesture *pan = ge->gesture(Qt::PanGesture)) {
            QPoint delta;
            QPanGesture *pg = static_cast<QPanGesture*> (pan);
            delta = pg->delta().toPoint();
            panTimer.start(100);
            emit screenMoved(delta);
        }
        return true;
    }
    case QEvent::MouseButtonPress:
    case QEvent::TouchBegin:
    case QEvent::MouseMove:
    case QEvent::TouchUpdate:
    case QEvent::MouseButtonRelease:
    case QEvent::TouchEnd:
        break;
    case QEvent::Wheel:
        return true;
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void MyView::moveScreen(QPoint p) {
    verticalScrollBar()->setValue(verticalScrollBar()->value() - p.y());
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - p.x());
}
