#include "myview.h"

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    isDeprecated = false;
    panTimer.setSingleShot(true);
    viewport()->setBaseSize(QSize(5000, 5000));
    setAttribute(Qt::WA_AcceptTouchEvents);
}

bool MyView::viewportEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::Gesture:
    {
//        QGestureEvent* ge = static_cast<QGestureEvent*> (event);
//        if (QGesture *pan = ge->gesture(Qt::PanGesture)) {
//            QPanGesture *pg = static_cast<QPanGesture*> (pan);
//            viewport()->move(pg->delta().toPoint() + viewport()->pos());
//            panTimer.start(100);
//        }
        return true;
    }
//    case QEvent::MouseButtonPress:
//    case QEvent::TouchBegin:
//    case QEvent::MouseMove:
//    case QEvent::TouchUpdate:
//    case QEvent::MouseButtonRelease:
//    case QEvent::TouchEnd:
//        if (panTimer.isActive())
//            return true;
    case QEvent::Wheel:
        return true;
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);

}
