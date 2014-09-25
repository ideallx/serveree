#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtWidgets>

class MyScene : public QGraphicsScene
{
    Q_OBJECT

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
