#include "myview.h"
#include <QGestureEvent>
#include <QScrollBar>
#include <QDebug>
#include <QAction>
#include <QDesktopWidget>
#include <QDir>
#include <QApplication>
#include "../../player/playerfactory.h"
#include "../DrawingScreen/myscene.h"       // for screen size function

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
    csi.backgroundMode = PaintNormal;
    csi.allSlides.insert("null", 0);
    csi.newSlideNo = 1;
    csi.isCoursewareSide = true;
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

void MyView::initViewBySceneID(TS_UINT64 sceneid) {
    if (sceneid == CoursewareUID) {
        setPaintMode(csi.backgroundMode);
    } else {
        setPaintMode(PaintNormal);
    }
}

void MyView::setPaintMode(int in) {
    csi.backgroundMode = in;
    // qDebug() << "set paint mode" << in;
    rawSetPaintMode(in);
}

void MyView::rawSetPaintMode(int in) {
    switch (in) {
    case PaintPPT:
        setStyleSheet("background: transparent");
        //qDebug() << "background transparent";
        break;
    default:
        setStyleSheet("background-color: rgb(255, 254, 240)");
        //qDebug() << "background rgb(255, 254, 240)";
        break;
    }

}

QPoint indexToPoint(int index) {
    QRect sz = screenSize();
    // qDebug() << "index to point the index is:" << index;
    return QPoint(index * sz.width(), 0);
}

void MyView::moveToSlide(bool isCoursewareSlide) {
    if (csi.isCoursewareSide == isCoursewareSlide)
        return;

    csi.isCoursewareSide = isCoursewareSlide;

    if (isCoursewareSlide) {
        rawSetPaintMode(csi.backgroundMode);
        moveScreen(indexToPoint(0));     // index 0 is null slide for normal screen
    } else {                             // move to left, show the couseslide
        rawSetPaintMode(PaintNormal);

        if (csi.allSlides.contains(newSlideName)) {
            moveScreen(indexToPoint(csi.allSlides[newSlideName]));
        } else {
            csi.allSlides.insert(newSlideName, csi.newSlideNo);
            moveScreen(indexToPoint(csi.newSlideNo));
            ++csi.newSlideNo;
            if (csi.newSlideNo > 200)   // TODO now the scene width of couseware is 200 * sz.width
                return;                 // TODO error 
        }
    }

    return;
}

void MyView::setNewSlideName(QString slideInfo) { 
    newSlideName = slideInfo; 
    moveScreen(indexToPoint(0));        // move the postion to 0, 0 make the pic show correctly
    // qDebug() << "myview" << newSlideName;
}
