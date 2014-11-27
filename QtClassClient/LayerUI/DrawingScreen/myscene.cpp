#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>
#include <QTouchEvent>

#include "../../player/absplayer.h"
#include "cshape.h"
#include "myscene.h"
#include "myview.h"

enum GRAPHICITEM_KEY_t {
    GraphicUID,
    GraphicShapeID
};

const int percentage = 1920;
QPointF screenToViewPercent(QPointF p, QGraphicsView* view) {
//    QPointF p2 = view->mapFromScene(p);
//    QPointF result = QPointF(p2.x() * percentage / view->width(),
//                             p2.y() * percentage / view->height());
//    return result;
    return p;
}


// TODO may be < 0 error
QPointF viewToScreenPercent(QPointF p, QGraphicsView *view) {
//    QPointF p2 = QPointF(p.x() * view->width() / percentage,
//                             p.y() * view->height() / percentage);
//    QPointF result = view->mapToScene(p2.toPoint());
//    return result;
    return p;
}

MyScene::MyScene(DWORD sceneID, QObject *parent, CMsgObject *msgParent)
    : QGraphicsScene(parent)
    , sceneID(sceneID)
    , gmc(new CGraphicMsgCreator(sceneID))
    , msgParent(msgParent)
    , toolChanged(true)
    , isEraser(false)
    , mt(MoveDraw)
    , isWriteable(false)
    , media(NULL) {
    panFixer.setSingleShot(true);
    setSceneRect(0, 0, 5000, 5000);
    connect(&panFixer, &QTimer::timeout,
            this, &MyScene::sendMoveBegin);

    setErase.pen = QPen(QColor(255, 254, 240), 50);
    setErase.drawingType = SCRIPTS;

    setDraw.pen = QPen(Qt::black, 1);
    setDraw.drawingType = SCRIPTS;

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

//    qDebug() << event->screenPos() << event->scenePos();
//    QPointF ff = screenToViewPercent(event->scenePos().toPoint(), views()[0]);
//    viewToScreenPercent(ff, views()[0]);
//    qDebug();

    //lastPos = event->scenePos();
    lastPos = screenToViewPercent(event->scenePos(), views()[0]);
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
    if (mt != MoveDraw)
        return;
    gmc->generateGraphicsData(gmsg, lastPos, false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isWriteable)
        return;

    mt = MovePending;
    panFixer.start(40);
    cachedPos = screenToViewPercent(event->scenePos(), views()[0]);
}

void MyScene::sendMoveBegin() {
    if (!isWriteable)
        return;

    TS_GRAPHIC_PACKET gmsg;
    mt = MoveDraw;

    DrawingSettingData *s = isEraser ? &setErase : &setDraw;

    if (toolChanged) {
        gmc->generatePenBrushData(gmsg, s->pen, s->brush);
        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        toolChanged = false;
    }
    gmc->create(s->drawingType, cachedPos);
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
    gmc->generateGraphicsData(gmsg, screenToViewPercent(event->scenePos(), views()[0]), false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
}

void MyScene::revocation() {
    isEraser = !isEraser;
    toolChanged = true;
}


CShape *MyScene::createNewItem(TS_UINT64 uid, int shapeType, QPointF curPoint) {
    CShape* item = CShapeFactory::createShape(shapeType);
    if (NULL == item)
        return NULL;
    item->setBeginPos(curPoint);
    item->getGraphicsItem()->acceptTouchEvents();

    QPen p;
    QBrush b(Qt::NoBrush);

    DrawingSettingData *s = isEraser ? &setErase : &setDraw;

    if (uid == SelfUID) {
        p = s->pen;
        b = s->brush;
    } else if (toolsMap.contains(uid)) {
        p = toolsMap[uid].first;
        b = toolsMap[uid].second;
    }

    item->setPen(p);
    item->setBrush(b);

    if (!isEraser)
        item->getGraphicsItem()->setOpacity(0.9);
    return item;
}

static int updateCounter = 0;
void MyScene::actMove(TS_GRAPHIC_PACKET &graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    QPointF p2 = viewToScreenPercent(scenePos, views()[0]);
    CShape* lastItem = lastItems[graphicMsg.head.UID];
	if (NULL == lastItem)
		return;
    lastItem->setCurPos(p2);

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

void MyScene::actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.BeginPx, graphicMsg.data.BeginPy);
    QPointF p2 = viewToScreenPercent(scenePos, views()[0]);
    TS_UINT64 uid = graphicMsg.head.UID;
    if (!lastItems.contains(uid)) {
        lastItems.insert(uid, NULL);
    }

    lastItems[uid] = createNewItem(uid, graphicMsg.data.ShapeType, p2);
    if (NULL == lastItems[uid])
        return;

    if (SelfUID == graphicMsg.head.UID)
        graphicMsg.head.UID = globalUID;

    QGraphicsItem* item = lastItems[uid]->getGraphicsItem();
    item->setData(GraphicUID, graphicMsg.head.UID);
    item->setData(GraphicShapeID, static_cast<int> (graphicMsg.data.ShapeID));
    addItem(item);

    updateCounter++;
    if (updateCounter % 10)
        update();   // repaint
}

// deprecated
void MyScene::actErase(TS_GRAPHIC_PACKET& graphicMsg) {
    qDebug() << "erase" << graphicMsg.eraser.targetUID << graphicMsg.eraser.shapeID;
    QPointF scenePos = QPointF(graphicMsg.eraser.PointX, graphicMsg.eraser.PointY);
    QPointF p2 = viewToScreenPercent(scenePos, views()[0]);
    QGraphicsItem* chosenItem = itemAt(p2, QTransform());
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
    if (items().size() != 0) {
        clear();
//        TS_GRAPHIC_PACKET gmsg;
//        gmc->generateClearScreen(gmsg);
//        msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);
        update();
    }
    lastItems.clear();
}

void MyScene::changeShapeByUI(int shape) {
    setDraw.drawingType = shape;
    isEraser = false;
}

void MyScene::moveScreen(QPoint p) {
    if (!isWriteable)
        return;

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

    QRect size = AbsPlayer::screenSize();
    QPointF sceneBeginPoint;

    if (size.height() > pix.height())
        sceneBeginPoint.setY((size.width() - pix.width()) / 2);

    if (size.width() > pix.width())
        sceneBeginPoint.setX((size.height() - pix.height()) / 2);

    const QPointF p = sceneBeginPoint;

    m_backpixmap = addPixmap(pix);
	m_backpixmap->setPos(views()[0]->mapToScene(p.x(), p.y()));
    m_backpixmap->setVisible(true);
    m_backpixmap->setZValue(-100);
}

void MyScene::playMedia(QMediaPlayer *player) {
    // TODO new new!! maybe deleted somewhere else.
    media = new QGraphicsVideoItem;
    media->setVisible(false);

    player->setVideoOutput(media);
    media->setPos(views()[0]->mapToScene(0, 0));
    QRect r = AbsPlayer::screenSize();
    media->setSize(QSize(r.width(), r.height()));
    media->setZValue(-100);
    media->setVisible(true);
    addItem(media);

    qDebug() << player->position();
    player->play();
    qDebug() << "media play" << player->isVideoAvailable();
}
