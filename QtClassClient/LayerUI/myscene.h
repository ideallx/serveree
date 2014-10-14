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

signals:
    void sceneMoved();

private:
    void cachePressEvent(QGraphicsSceneMouseEvent *event);

    TS_GRAPHIC_PACKET gmsgCache;
    bool hasNewMove;
    QPointF lastBeginPos;

    CMsgObject* msgParent;
    CGraphicMsgCreator* gmc;
    QMap<TS_UINT64, CShape*> lastItems;
    QMap<TS_UINT64, QPair<QPen, QBrush> > toolsMap;
    QMutex mutex;
    QTimer panFixer;    // delete the useless pangesture track
    QTimer panFixer2;

    DWORD sceneID;
    bool toolChanged;   // is pen or brush changed

    QPen pen;
    QBrush brush;

    int drawingType;

    QPointF beginPoint;
};

#endif // MYSCENE_H
