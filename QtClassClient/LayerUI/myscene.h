#ifndef MYSCENE_H
#define MYSCENE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QMap>
#include "cgraphicmsgcreator.h"

#include "../Message/CMsgObject.h"

class CShape;

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MyScene(QObject *parent = 0, CMsgObject* msgParent = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    CShape* createNewItem(QPointF curPoint);

    void actMove(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveEnd(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg);

    void changeType(enum ShapeType s);

    void setPenWidth(int width) { pen.setWidth(width); }

    void setPenColor(QString color) { pen.setColor(QColor(color)); }

    void setBrushColor(QString color) { brush = QBrush(QColor(color)); }

private:
    CMsgObject* msgParent;
    CGraphicMsgCreator* gmc;
    QMap<TS_UINT64, CShape*> lastItems;

    QPen pen;
    QBrush brush;

    int pointCounter;
    int drawingType;

    QPointF beginPoint;

};

#endif // MYSCENE_H
