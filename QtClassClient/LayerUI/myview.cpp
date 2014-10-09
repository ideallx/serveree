#include "myview.h"

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qApp->setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
    isDeprecated = false;
}

bool MyView::viewportEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::Gesture:
    {
        QGestureEvent* ge = static_cast<QGestureEvent*> (event);
        if (QGesture *pan = ge->gesture(Qt::PanGesture)) {
            QPanGesture *pg = static_cast<QPanGesture*> (pan);
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - pg->delta().x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - pg->delta().y());
            if (scene()->items().size() != 0 && isDeprecated) {     // delete recently added shape
                scene()->removeItem(scene()->items().first());      // the shape(track of swipe) is redundant
                isDeprecated = false;                               // still little problem
            }
        }
        return true;
    }
    case QEvent::MouseButtonPress:
        isDeprecated = true;
        break;
    case QEvent::MouseButtonRelease:
    case QEvent::TouchEnd:
        isDeprecated = false;
        break;
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);

}
