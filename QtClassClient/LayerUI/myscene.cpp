#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>

#include "cshape.h"
#include "myscene.h"

MyScene::MyScene(QObject *parent, CMsgObject *msgParent) :
    QGraphicsScene(parent),
    gmc(new CGraphicMsgCreator),
    drawingType(SCRIPTS),
    msgParent(msgParent),
    toolChanged(false) {

    setSceneRect(0, 0, 5000, 5000);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "move";
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "press";
    TS_GRAPHIC_PACKET gmsg;

    if (toolChanged) {
        qDebug() << "changed";
        gmc->generatePenBrushData(gmsg, pen, brush);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        toolChanged = false;
    }

    gmc->create(drawingType, event->scenePos());
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    actMoveBegin(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "release";
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), true);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

CShape *MyScene::createNewItem(TS_UINT64 uid, int shapeType, QPointF curPoint) {
    CShape* item = CShapeFactory::createShape(shapeType);
    item->setBeginPos(curPoint);
    item->getGraphicsItem()->acceptTouchEvents();

    QPen p;
    QBrush b(Qt::NoBrush);
    if (uid == SelfUID) {
        p = pen;
        b = brush;
    } else if (toolsMap.contains(uid)) {
        p = toolsMap[uid].first;
        b = toolsMap[uid].second;
    }

    item->setPen(p);
    item->setBrush(b);
    item->getGraphicsItem()->setOpacity(0.6);
    return item;
}

static int updateCounter = 0;
void MyScene::actMove(TS_GRAPHIC_PACKET &graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    CShape* lastItem = lastItems[graphicMsg.head.UID];
	if (NULL == lastItem)
		return;
    lastItem->setCurPos(scenePos);
    lastItems.insert(graphicMsg.head.UID, lastItem);

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

void MyScene::actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    TS_UINT64 uid = graphicMsg.head.UID;
    if (!lastItems.contains(uid)) {
        lastItems.insert(uid, NULL);
    }

    beginPoint = scenePos;
    lastItems[uid] = createNewItem(uid, graphicMsg.data.ShapeType, scenePos);
    addItem(lastItems[uid]->getGraphicsItem());

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

void MyScene::changeType(ShapeType s) {
    drawingType = s;
}

void MyScene::setOthersPenBrush(TS_GRAPHIC_PACKET& graphicMsg) {
    TS_UINT64 uid = graphicMsg.head.UID;
    QPen p(QColor(graphicMsg.penbrush.penR,
                  graphicMsg.penbrush.penG,
                  graphicMsg.penbrush.penB),
           graphicMsg.penbrush.penWidth);

    QBrush b(QColor(graphicMsg.penbrush.brushR,
                    graphicMsg.penbrush.brushG,
                    graphicMsg.penbrush.brushB));
    if (graphicMsg.penbrush.brushR == 0 &&
            graphicMsg.penbrush.brushG == 0 &&
            graphicMsg.penbrush.brushB == 0)
        b = Qt::NoBrush;
    toolsMap.insert(uid, QPair<QPen, QBrush> (p, b));
    qDebug() << "set pen and brush";
}

void MyScene::cls() {
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateClearScreen(gmsg);
    if (items().size() != 0) {
        clear();
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        update();
        qDebug() << "clear";
    }
}

void MyScene::changeShapeByUI(int shape) {
    switch (shape) {
    case 0:
        drawingType = SCRIPTS;
        break;
    case 1:
        drawingType = LINE;
        break;
    case 2:
        drawingType = RECTANGLE;
        break;
    case 3:
        drawingType = ELLIPSE;
        break;
    default:
        break;
    }
}
