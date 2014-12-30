#include "myview.h"
#include <QGestureEvent>
#include <QScrollBar>
#include <QDebug>
#include <QAction>
#include <QDesktopWidget>
#include <QDir>
#include <QApplication>
#include "../../player/playerfactory.h"


MyView::MyView(QWidget *parent)
	: QGraphicsView(parent)
	, pm(PaintNormal)
    , isLeftClicked(false) {
    //setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    panTimer.setSingleShot(true);
    zoomTimer.setSingleShot(true);
    setAttribute(Qt::WA_AcceptTouchEvents);
    setMouseTracking(true);

    setStyleSheet("background-color: rgb(255, 254, 240)");

//    grabGesture(Qt::PinchGesture);
//    ungrabGesture(Qt::PanGesture);
}

MyView::~MyView() {
}

bool MyView::viewportEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::Gesture:
    {
        QGestureEvent* ge = static_cast<QGestureEvent*> (event);
        if (QGesture *pan = ge->gesture(Qt::PanGesture)) {
            QPoint dest;
            QPanGesture *pg = static_cast<QPanGesture*> (pan);
            dest.setX(horizontalScrollBar()->value() - pg->delta().toPoint().x());
            dest.setY(verticalScrollBar()->value() - pg->delta().toPoint().y());
            panTimer.start(100);
            qDebug() << "dest is" << dest;
            emit screenMoved(dest);
        } else if (QGesture *pan = ge->gesture(Qt::PinchGesture)) {
            qDebug() << "pinch";
        }
        return true;
    }
    case QEvent::Leave:
        isLeftClicked = false;
        break;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
        return true;
    case QEvent::MouseButtonRelease:
        isLeftClicked = false;
        break;
    case QEvent::MouseButtonPress:
        isLeftClicked = true;
        break;
    case QEvent::MouseMove:
        if (!isLeftClicked)
            return true;
        isLeftClicked = true;
        break;
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::Wheel:
        return true;
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void MyView::moveScreen(QPoint p) {
    // verticalScrollBar()->setValue(p.y());
    horizontalScrollBar()->setValue(p.x());
}

void MyView::setPaintMode(int in) {
    switch (in) {
    case PaintPPT:
        setStyleSheet("background: transparent");
        break;
    default:
        setStyleSheet("background-color: rgb(255, 254, 240)");
        break;
    }
    qDebug() << this->backgroundBrush().color();
}
