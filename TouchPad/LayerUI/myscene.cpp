#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>

#include "myscene.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    number = 0;
    lastItem = NULL;

    setSceneRect(0, 0, 5000, 5000);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (NULL != lastItem && (number % 4 != 3)) {
        removeItem(lastItem);
        delete lastItem;
    }
    lastItem = createNewItem(event->scenePos());
    lastItem->acceptTouchEvents();
    addItem(lastItem);
    if (number % 4 == 3) {
        beginPoint = event->scenePos();
    }
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    beginPoint = event->scenePos();
    lastItem = NULL;
    number++;
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    removeItem(lastItem);
    lastItem = createNewItem(event->scenePos());
    lastItem->acceptTouchEvents();
    addItem(lastItem);
}

QGraphicsItem* MyScene::createNewItem(QPointF curPoint) {
    switch (number % 4) {
    case 0:
        return new QGraphicsLineItem(beginPoint.x(), beginPoint.y(),
                                     curPoint.x(), curPoint.y());
    case 1:
        return new QGraphicsEllipseItem(beginPoint.x(), beginPoint.y(),
                                        curPoint.x() - beginPoint.x(),
                                        curPoint.y() - beginPoint.y());
    case 2:
    {
        qreal x = qMin(beginPoint.x(), curPoint.x());
        qreal y = qMin(beginPoint.y(), curPoint.y());
        qreal w = abs(beginPoint.x() - curPoint.x());
        qreal h = abs(beginPoint.y() - curPoint.y());
        return new QGraphicsRectItem(x, y, w, h);
    }
    case 3:
        return new QGraphicsLineItem(beginPoint.x(), beginPoint.y(),
                                     curPoint.x(), curPoint.y());
    default:
        return NULL;
    }
}
