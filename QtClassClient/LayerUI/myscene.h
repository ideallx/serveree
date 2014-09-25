#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtWidgets>
//#include "../Message/CMsgObject.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT
    //CMsgObject* msgParent;

public:
    explicit MyScene(QObject *parent = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QGraphicsItem* createNewItem(QPointF curPoint);

private:
    QGraphicsItem* lastItem;


    int number;

    QPointF beginPoint;

};

#endif // MYSCENE_H
