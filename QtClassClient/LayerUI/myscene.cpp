#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>
#include <QTouchEvent>

#include "cshape.h"
#include "myscene.h"

MyScene::MyScene(DWORD sceneID, QObject *parent, CMsgObject *msgParent) :
    QGraphicsScene(parent),
    sceneID(sceneID),
    gmc(new CGraphicMsgCreator(sceneID)),
    drawingType(SCRIPTS),
    msgParent(msgParent),
    toolChanged(false),
    isEraser(false) {
    panFixer.setSingleShot(true);
    panFixer2.setSingleShot(true);
    setSceneRect(0, 0, 5000, 5000);
    connect(&panFixer, &QTimer::timeout,
            this, &MyScene::sendMoveBegin);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    if (panFixer2.isActive()) {
//        hasNewMove = false;
//        return;
//    } else if (panFixer.isActive()) {
//        hasNewMove = true;
//        return;
//    }

    if (isEraser)
        return;
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    panFixer.start(100);
//    panFixer2.start(50);
    if (isEraser)
        return;
    cachePressEvent(event);
    sendMoveBegin();
}

void MyScene::cachePressEvent(QGraphicsSceneMouseEvent *event) {
    if (toolChanged) {
        qDebug() << "changed";
        gmc->generatePenBrushData(gmsgCache, pen, brush);
        msgParent->ProcessMessage(*(ts_msg*) &gmsgCache, 0, 0, false);
        toolChanged = false;
    }
    lastBeginPos = event->scenePos();
}

void MyScene::sendMoveBegin() {
//    if (!hasNewMove)
//        return;
    gmc->create(drawingType, lastBeginPos);
    gmc->generateGraphicsData(gmsgCache, lastBeginPos, false);
    actMoveBegin(gmsgCache);
    msgParent->ProcessMessage(*(ts_msg*) &gmsgCache, 0, 0, false);
}

void MyScene::revocation() {
    isEraser = !isEraser;
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    TS_GRAPHIC_PACKET gmsg;
    if (isEraser) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item != NULL) {
            gmc->generateEraserData(gmsg, event->scenePos());
            actErase(gmsg);
            msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        }
    } else {
        gmc->generateGraphicsData(gmsg, event->scenePos(), true);
        actMove(gmsg);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
    }
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
    item->getGraphicsItem()->setOpacity(0.9);
    return item;
}

static int updateCounter = 0;
void MyScene::actMove(TS_GRAPHIC_PACKET &graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    CShape* lastItem = lastItems[graphicMsg.head.UID];
	if (NULL == lastItem)
		return;
    lastItem->setCurPos(scenePos);

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

    lastItems[uid] = createNewItem(uid, graphicMsg.data.ShapeType, scenePos);
    addItem(lastItems[uid]->getGraphicsItem());

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

void MyScene::actErase(TS_GRAPHIC_PACKET& graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    removeItem(itemAt(scenePos, QTransform()));
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
}

void MyScene::cls() {
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateClearScreen(gmsg);
    if (items().size() != 0) {
        clear();
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        update();
    }
}

void MyScene::changeShapeByUI(int shape) {
    drawingType = shape;
}
