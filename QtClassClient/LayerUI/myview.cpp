#include "myview.h"
#include <QGestureEvent>
#include <QScrollBar>
#include <QDebug>
#include <QAction>
#include <QDesktopWidget>
#include <QDir>
#include <QApplication>
#include "../player/playerfactory.h"


MyView::MyView(QWidget *parent) :
    QGraphicsView(parent),
    pm(PaintPPT),
    isLeftClicked(false),
    player(NULL),
    msg(NULL),
    isWareStarted(false) {
    //setRenderHint(QPainter::Antialiasing);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    panTimer.setSingleShot(true);
    setAttribute(Qt::WA_AcceptTouchEvents);
    setMouseTracking(true);

    prev = new QToolButton(this);
    stop = new QToolButton(this);
    next = new QToolButton(this);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screen = desktopWidget->screenGeometry();

    const int width = 81;
    const int height = 65;
    prev->setGeometry(0, screen.height() - height - 75, width, height);
    stop->setGeometry(width + 5, screen.height() - height - 75, width, height);
    next->setGeometry(width*2 + 10, screen.height() - height - 75, width, height);

    prev->setIcon(QIcon(":/icon/ui/icon/prev.png"));
    prev->setIconSize(QSize(width, height));
    stop->setIcon(QIcon(":/icon/ui/icon/stop.png"));
    stop->setIconSize(QSize(width, height));
    next->setIcon(QIcon(":/icon/ui/icon/next.png"));
    next->setIconSize(QSize(width, height));

    connect(prev, &QToolButton::clicked,
            this, &MyView::pprev);
    connect(stop, &QToolButton::clicked,
            this, &MyView::pstop);
    connect(next, &QToolButton::clicked,
            this, &MyView::pnext);

    ctrllist.append(prev);
    ctrllist.append(stop);
    ctrllist.append(next);

    hideButtons();
}

void MyView::pstop() {
//    if (isWareStarted) {
        player->close();
        delete player;
        player = 0;
        setPaintMode(PaintNormal);
        isWareStarted = false;
        scene()->clear();
//    } else {
//        if (player) {
//            player->start();
//            scene()->clear();
//            stop->setIcon(QIcon(":/icon/ui/icon/stop.png"));
//            isWareStarted = true;
//        }
//    }
}

void MyView::pprev() {
    if (player)
        player->prev();
    scene()->clear();
}

void MyView::pnext() {
    if (player)
        player->next();
    scene()->clear();
}

MyView::~MyView() {
    if (player) {
        player->close();
        delete player;
        player = 0;
    }
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
        }
        return true;
    }

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
    verticalScrollBar()->setValue(p.y());
    horizontalScrollBar()->setValue(p.x());
}

void MyView::buildPlayer() {

}

void MyView::setPaintMode(PaintMode in) {
    switch (in) {
    case PaintPPT:
        hideButtons(false);
        setStyleSheet("background: transparent");
        break;
    default:
        hideButtons(true);
        setStyleSheet("background-color: rgb(255, 254, 240)");
        break;
    }
}

void MyView::playCourseware(QString filepath) {
    setPaintMode(PaintPPT);
    if (player) {
        player->close();
        delete player;
    }
    QString path = QDir::currentPath();
    QString file = path + "/" + filepath;
    qDebug() << file;
    player = PlayerFactory::createPlayer(file, msg);
    player->run();
}

void MyView::hideButtons(bool hide) {
    foreach (QToolButton* tb, ctrllist) {
        tb->setHidden(hide);
    }
}
