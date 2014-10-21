#ifndef MYSCENE_H
#define MYSCENE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QMap>
#include <QMutex>
#include <QTimer>
#include "cgraphicmsgcreator.h"

#include "../Message/CMsgObject.h"

class CShape;

enum MoveType {
    MovePending,
    MoveScreen,
    MoveDraw
};

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MyScene(DWORD sceneID, QObject *parent = 0, CMsgObject* msgParent = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    CShape* createNewItem(TS_UINT64 uid, int shapeType, QPointF curPoint);

    void actMove(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveEnd(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg);

    void actErase(TS_GRAPHIC_PACKET& graphicMsg);

    void changeType(enum ShapeType s);

public slots:

    void changeShapeByUI(int shape);

    void setPenWidth(int width) { pen.setWidth(width); toolChanged = true; }

    void setPenColor(QColor c) { pen.setColor(c); toolChanged = true; }

    void setBrushColor(QColor c) { brush = QBrush(c); toolChanged = true; }

    void setOthersPenBrush(TS_GRAPHIC_PACKET& graphicMsg);

    void cls();

    void sendMoveBegin();

    void revocation();

    void setEraser(bool set) { isEraser = set; }

    void moveScreen(QPoint p);

private:
    void cachePressEvent(QGraphicsSceneMouseEvent *event);

    void generateTestShape();

    set<pair<TS_UINT64, DWORD> > eraseList;

    CMsgObject* msgParent;
    CGraphicMsgCreator* gmc;
    QMap<TS_UINT64, CShape*> lastItems;
    QMap<TS_UINT64, QPair<QPen, QBrush> > toolsMap;
    QPointF cachedPos;

    QTimer panFixer;    // begin drawing when move type isnot move screen

    DWORD sceneID;
    bool toolChanged;   // is pen or brush changed

    QPen pen;
    QBrush brush;

    int drawingType;

    bool isEraser;

    MoveType mt;
    QPointF lastPos;
};

#endif // MYSCENE_H
