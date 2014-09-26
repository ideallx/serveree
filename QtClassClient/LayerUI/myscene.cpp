#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>

#include "cshape.h"
#include "myscene.h"

MyScene::MyScene(QObject *parent, CMsgObject *msgParent) :
    QGraphicsScene(parent),
    pointCounter(0),
    msgParent(msgParent)
{
    drawingType = SCRIPTS;
    gmc = new CGraphicMsgCreator();

    setSceneRect(0, 0, 5000, 5000);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
    actMove(gmsg);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    pointCounter = 0;
    gmc->create(drawingType, event->scenePos());

    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), true);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
    actMoveBegin(gmsg);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
    actMove(gmsg);
}

CShape *MyScene::createNewItem(QPointF curPoint) {
    CShape* item = CShapeFactory::createShape(drawingType);
    item->setBeginPos(curPoint);
    item->getGraphicsItem()->acceptTouchEvents();
    item->setPen(pen);
    item->setBrush(brush);
    return item;
}

void MyScene::actMove(TS_GRAPHIC_PACKET &graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    CShape* lastItem = lastItems[graphicMsg.head.UID];
	if (NULL == lastItem)
		return;
    lastItem->setCurPos(scenePos);
    lastItems.insert(graphicMsg.head.UID, lastItem);
    update();   // repaint
}

void MyScene::actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    TS_UINT64 uid = graphicMsg.head.UID;
    if (!lastItems.contains(uid)) {
        lastItems.insert(uid, NULL);
    }
    drawingType = graphicMsg.data.ShapeType;
    beginPoint = scenePos;
    lastItems[uid] = createNewItem(scenePos);
    addItem(lastItems[uid]->getGraphicsItem());
    update();   // repaint
}

void MyScene::changeType(ShapeType s) {
    drawingType = s;
}
