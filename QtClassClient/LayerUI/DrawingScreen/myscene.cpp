#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMessageBox>
#include <QTouchEvent>
#include <QDesktopWidget>
#include <QApplication>

#include "../../player/absplayer.h"
#include "../../BizLogic/datasingleton.h"
#include "cshape.h"
#include "myscene.h"
#include "myview.h"

enum GRAPHICITEM_KEY_t {
    GraphicUID,
    GraphicShapeID
};

const int percentage = 60000;
static const QPointF PointNull = QPointF(-1, -1);
static QRect staticSZ = QRect(0, 0, 0, 0);

QRect screenSize() {
    if (staticSZ.width() == 0) {
        QDesktopWidget *dwsktopwidget = QApplication::desktop();
        staticSZ = dwsktopwidget->screenGeometry();
    }
    return staticSZ;
}

QRect widgetAvaiableSize() {
    QRect result = screenSize();
    result.setHeight(result.height() - 80);
    result.setWidth(result.width() - 300);
    return result;
}

QPointF screenToViewPercent(QPointF p, QGraphicsView* view) {
    if (NULL == view)
        return QPointF();
    QRect sz = screenSize();
    QPointF p2 = view->mapFromScene(p);
    QPointF result = QPointF(p2.x() * percentage / view->width(),
                             p2.y() * percentage / view->height());

    if (result.x() < 0) {
        result.setX(0);
    } else if (result.x() > percentage) {
        result.setX(percentage);
    }

    if (result.y() < 0) {
        result.setY(0);
    } else if (result.y() > percentage) {
        result.setY(percentage);
    }

    return result;
}

QPointF rawScreenToViewPercent(QPointF p, QGraphicsView* view) {
    if (NULL == view)
        return QPointF();
    QRect sz = screenSize();
    QPointF p2 = view->mapFromScene(p);
    QPointF result = QPointF(p2.x() * percentage / view->width(),
                             p2.y() * percentage / view->height());

    return result;
}

// TODO may be < 0 error
QPointF viewToScreenPercent(QPointF p, QGraphicsView *view) {
    if (NULL == view)
        return QPointF();
    QPointF p2 = QPointF(p.x() * view->width()  / percentage,
                         p.y() * view->height() / percentage);
    QPointF result = view->mapToScene(p2.toPoint());
    return result;
}

MyScene::MyScene(DWORD sceneID, QGraphicsView* view, QObject *parent, CMsgObject *msgParent)
    : QGraphicsScene(parent)
    , sceneID(sceneID)
    , gmc(new CGraphicMsgCreator(sceneID))
    , msgParent(msgParent)
    , toolChanged(true)
    , isEraser(false)
    , mt(MoveDraw)
    , isWriteable(false)
    , media(NULL)
    , m_view(view)
    , lastPos(PointNull)
    , cachedPos(PointNull) {
    ds = DataSingleton::getInstance();

    panFixer.setSingleShot(true);
    QRect scr = screenSize();
    if (sceneID == CoursewareUID) {
        setSceneRect(0, 0, scr.width() * 200 + 200, scr.height() + 10);
    } else {
        setSceneRect(0, 0, scr.width() * 20 + 200, scr.height() + 10);
    }
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
    lastPos = screenToViewPercent(event->scenePos(), m_view);

    TS_GRAPHIC_PACKET gmsg;
    MyView* mv = static_cast<MyView*> (m_view);
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

    cachedPos = screenToViewPercent(event->scenePos(), m_view);
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
    if (cachedPos == PointNull)
        return;
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
    QPointF tranferredP = screenToViewPercent(event->scenePos(), m_view);

    TS_GRAPHIC_PACKET gmsg;
    gmc->generateGraphicsData(gmsg, tranferredP, false);
    actMove(gmsg);
    msgParent->ProcessMessage(*(ts_msg*) &gmsg, 0, 0, false);

    // prevent long line
    cachedPos = PointNull;
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

    return item;
}

static int updateCounter = 0;
void MyScene::actMove(TS_GRAPHIC_PACKET &graphicMsg) {
    QPointF scenePos = QPointF(graphicMsg.data.PointX, graphicMsg.data.PointY);
    QPointF p2 = viewToScreenPercent(scenePos, m_view);
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
    QPointF p2 = viewToScreenPercent(scenePos, m_view);
    TS_UINT64 uid = graphicMsg.head.UID;
    if (!lastItems.contains(uid)) {
        lastItems.insert(uid, NULL);
    }

    lastItems[uid] = createNewItem(uid, graphicMsg.data.ShapeType, p2);
    if (NULL == lastItems[uid])
        return;

    if (SelfUID == graphicMsg.head.UID)
        graphicMsg.head.UID = ds->getUID();

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
    QPointF p2 = viewToScreenPercent(scenePos, m_view);
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

// negative number!!!
// in normal screen: move screen means the canvas was moved
// in courseware screen: move screen means change a specific canvas
void MyScene::actMoveScreen(TS_GRAPHIC_PACKET& graphicMsg) {
    QPointF scenePos = QPointF(static_cast<int> (graphicMsg.data.PointX),
                               static_cast<int> (graphicMsg.data.PointY));
    QPointF p2 = viewToScreenPercent(scenePos, m_view);

    // calc the total offset in ten moves
    const int TimeN = 30;
    static int times = 0;  // 
    static bool isCoursewareSlide = true;
    static QPointF total = QPointF(0, 0);

    if (sceneID == CoursewareUID) {
        if (times <= TimeN) {
            total += scenePos;
            times++;
        } else {
            times = 0;
            total = scenePos;
        }
        if (total.x() > 0 && total.x() > (percentage / 8)) {
            times = 0;
            total = QPointF(0, 0);
            emit changeSide(false);
        } else if (total.x() < 0 && total.x() < (-percentage / 8)) {
            times = 0;
            total = QPointF(0, 0);
            emit changeSide(true);
        }
    } else {
        MyView* mv = static_cast<MyView*> (m_view);
        mv->moveScreen(p2.toPoint());
    }
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

// contains two types of move such as Draw and Move Screen
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
    } else {
        if (ds->getSelfRole() == RoleStudent)   // student is now not allowed to move the screen
            return;

        QPointF p2 = rawScreenToViewPercent(p, m_view);
        TS_GRAPHIC_PACKET gmsg;
        gmc->generateScreenMove(gmsg, p2.toPoint());
        actMoveScreen(gmsg);
        msgParent->ProcessMessage(*(ts_msg*)&gmsg, 0, 0, false);
    }
}

void MyScene::setBackground(QPixmap pix) {
    if (pix.isNull())
        return;

    if (items().contains(m_backpixmap))
        removeItem(m_backpixmap);

    QRect size = widgetAvaiableSize();
    QPointF sceneBeginPoint;

    if (size.height() > pix.height())
        sceneBeginPoint.setY((size.width() - pix.width()) / 2);

    if (size.width() > pix.width())
        sceneBeginPoint.setX((size.height() - pix.height()) / 2);

    const QPointF p = sceneBeginPoint;
    qDebug() << "scene position" << m_view->mapFromScene(p);

    m_backpixmap = addPixmap(pix);
    m_backpixmap->setPos(m_view->mapToScene(p.x(), p.y()));
    m_backpixmap->setVisible(true);
    m_backpixmap->setZValue(-100);
}

void MyScene::playMedia(QMediaPlayer *player) {
    // TODO new new!! maybe deleted somewhere else.
    media = new QGraphicsVideoItem;
    media->setVisible(false);

    player->setVideoOutput(media);
    media->setPos(m_view->mapToScene(0, 0));
    QRect r = widgetAvaiableSize();
    media->setSize(QSize(r.width(), r.height()));
    media->setZValue(-100);
    media->setVisible(true);
    addItem(media);

    player->play();
    qDebug() << "media play" << player->isVideoAvailable();
}

void MyScene::cleanFirstPage() {
    auto needToDelete = items(widgetAvaiableSize());
    foreach(auto item, needToDelete) {
        // if (item->zValue() < 0)
            removeItem(item);
    }
}