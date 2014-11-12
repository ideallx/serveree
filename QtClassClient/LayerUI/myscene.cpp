#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>
#include <QTouchEvent>

#include "../player/absplayer.h"
#include "cshape.h"
#include "myscene.h"
#include "myview.h"

enum GRAPHICITEM_KEY_t {
    GraphicUID,
    GraphicShapeID
};

MyScene::MyScene(DWORD sceneID, QObject *parent, CMsgObject *msgParent) :
    QGraphicsScene(parent),
    sceneID(sceneID),
    gmc(new CGraphicMsgCreator(sceneID)),
    drawingType(SCRIPTS),
    msgParent(msgParent),
    toolChanged(false),
    isEraser(false),
    mt(MoveDraw),
    isWriteable(false),
    m_backpixmap(NULL) {
    panFixer.setSingleShot(true);
    setSceneRect(0, 0, 5000, 50000);
    connect(&panFixer, &QTimer::timeout,
            this, &MyScene::sendMoveBegin);

    media = new QGraphicsVideoItem;
    media->setVisible(false);
    addItem(media);
    //generateTestShape();
}

void MyScene::generateTestShape() {
    for (int i = 0; i < 5000; i++) {
        QPainterPath path;
        for (int j = 0; j < 50; j++) {
            path.lineTo(rand() % 700, rand() % 300 + i*10);
        }
        QGraphicsItem *item = new QGraphicsPathItem(path);
        addItem(item);
    }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!isWriteable)
        return;

    lastPos = event->scenePos();
    TS_GRAPHIC_PACKET gmsg;
    MyView* mv = static_cast<MyView*> (this->views()[0]);
    if (mv->panTimer.isActive()) {
        panFixer.stop();
        mt = MoveScreen;
        return;
    }
    if (!mv->isLeftClicked)
        return;
    if (panFixer.isActive())
        return;
    if (isEraser || mt != MoveDraw)
        return;
    gmc->generateGraphicsData(gmsg, event->scenePos(), false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isWriteable)
        return;

    if (isEraser)
        return;

    mt = MovePending;
    panFixer.start(40);
    cachedPos = event->scenePos();
}

void MyScene::sendMoveBegin() {
    if (!isWriteable)
        return;

    TS_GRAPHIC_PACKET gmsg;
    mt = MoveDraw;
    if (toolChanged) {
        gmc->generatePenBrushData(gmsg, pen, brush);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        toolChanged = false;
    }
    gmc->create(drawingType, cachedPos);
    gmc->generateGraphicsData(gmsg, cachedPos, true);
    actMoveBegin(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (!isWriteable)
        return;

    if (panFixer.isActive() || mt != MoveDraw)
        return;
    TS_GRAPHIC_PACKET gmsg;
    if (isEraser) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item != NULL && item->zValue() >= 0) {       // dont remvoe the background
            gmc->generateEraserData(gmsg, event->scenePos(),
                                    item->data(GraphicUID).toULongLong(),
                                    item->data(GraphicShapeID).toInt());
            actErase(gmsg);
            msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        }
    } else {
        gmc->generateGraphicsData(gmsg, event->scenePos(), false);
        actMove(gmsg);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
    }
}

void MyScene::revocation() {
    isEraser = !isEraser;
}


CShape *MyScene::createNewItem(TS_UINT64 uid, int shapeType, QPointF curPoint) {
    CShape* item = CShapeFactory::createShape(shapeType);
    if (NULL == item)
        return NULL;
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
    QPointF scenePos = QPointF(graphicMsg.data.BeginPx, graphicMsg.data.BeginPy);
    TS_UINT64 uid = graphicMsg.head.UID;
    if (!lastItems.contains(uid)) {
        lastItems.insert(uid, NULL);
    }

    lastItems[uid] = createNewItem(uid, graphicMsg.data.ShapeType, scenePos);
    if (NULL == lastItems[uid])
        return;

    if (SelfUID == graphicMsg.head.UID)
        graphicMsg.head.UID = globalUID;
    auto itemPair = make_pair(graphicMsg.head.UID,
                              graphicMsg.data.ShapeID);
    // qDebug() << "recv" << graphicMsg.head.UID << graphicMsg.data.ShapeID;

    if (eraseList.count(itemPair)) {
        qDebug() << "find and remaining" << eraseList.size() << "remove" <<
                    graphicMsg.head.UID << graphicMsg.data.ShapeID;;
        eraseList.erase(itemPair);
        return;
    }


    QGraphicsItem* item = lastItems[uid]->getGraphicsItem();
    item->setData(GraphicUID, graphicMsg.head.UID);
    item->setData(GraphicShapeID, static_cast<int> (graphicMsg.data.ShapeID));
    addItem(item);

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

void MyScene::actErase(TS_GRAPHIC_PACKET& graphicMsg) {
    qDebug() << "erase" << graphicMsg.eraser.targetUID << graphicMsg.eraser.shapeID;
    QPointF scenePos = QPointF(graphicMsg.eraser.PointX, graphicMsg.eraser.PointY);
    QGraphicsItem* chosenItem = itemAt(scenePos, QTransform());
    // first find by position
    if ((chosenItem->data(GraphicUID).toLongLong() == graphicMsg.eraser.targetUID) &&
            (chosenItem->data(GraphicShapeID).toInt() == graphicMsg.eraser.shapeID)) {
        removeItem(chosenItem);
        return;
    }

    // if not found, find by uid and shapeid
    foreach (QGraphicsItem* i, items()) {
        if ((i->data(GraphicUID).toLongLong() == graphicMsg.eraser.targetUID) &&
            (i->data(GraphicShapeID).toInt() == graphicMsg.eraser.shapeID)) {
            removeItem(i);
            return;
        }
    };
    eraseList.insert(make_pair(graphicMsg.eraser.targetUID,
                               graphicMsg.eraser.shapeID));
}

void MyScene::changeType(ShapeType s) {
    drawingType = s;
}

void MyScene::setOthersPenBrush(TS_GRAPHIC_PACKET& graphicMsg) {
    TS_UINT64 uid = graphicMsg.head.UID;
    QPen p(QColor(graphicMsg.tool.penR,
                  graphicMsg.tool.penG,
                  graphicMsg.tool.penB),
           graphicMsg.tool.penWidth);

    QBrush b(QColor(graphicMsg.tool.brushR,
                    graphicMsg.tool.brushG,
                    graphicMsg.tool.brushB));
    if (graphicMsg.tool.brushR == 0 &&
            graphicMsg.tool.brushG == 0 &&
            graphicMsg.tool.brushB == 0)
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

void MyScene::moveScreen(QPoint p) {
    if (mt == MoveDraw) {
        TS_GRAPHIC_PACKET gmsg;
        gmc->generateGraphicsData(gmsg, lastPos, false);
        actMove(gmsg);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);

        mt = MoveScreen;
        return;
    }

    MyView* mv = static_cast<MyView*> (this->views()[0]);
    mv->moveScreen(p);
    TS_GRAPHIC_PACKET gmsg;
    gmc->generateScreenMove(gmsg, p);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::setBackground(QPixmap pix) {
    if (pix.isNull())
        return;

    if (items().contains(m_backpixmap))
        removeItem(m_backpixmap);


    m_backpixmap = addPixmap(pix);
    m_backpixmap->setPos(views()[0]->mapToScene(0, 0));
    m_backpixmap->setVisible(true);
    m_backpixmap->setZValue(-100);
}

void MyScene::playMedia(QMediaPlayer *player) {
    // TODO new new!!
    media = new QGraphicsVideoItem;
    player->setVideoOutput(media);
    media->setPos(views()[0]->mapToScene(0, 0));
    QRect r = AbsPlayer::screenSize();
    media->setSize(QSize(r.width(), r.height()));
    media->setZValue(-100);
    media->setVisible(true);
    addItem(media);

    player->play();
    qDebug() << "media play" << player->isVideoAvailable();
}
