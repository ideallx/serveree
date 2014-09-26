#ifndef CSHAPE_H_
#define CSHAPE_H_

#include <QGraphicsItem>
#include "../Reliable/DataUnit/CMessage.h"


class CShape {
public:
    CShape(QGraphicsItem* item);
    virtual ~CShape();

protected:
    QPointF beginPos;
    QGraphicsItem* item;

public:
    virtual void setBeginPos(QPointF pos);
    virtual void setCurPos(QPointF pos) = 0;
    virtual void setPen(const QPen& pen) {Q_UNUSED(pen); }
    virtual void setBrush(const QBrush& brush) {Q_UNUSED(brush);}

    inline QGraphicsItem* getGraphicsItem() { return item; }
};

class CShapeLine : public CShape {
public:
    CShapeLine(QGraphicsItem* item = NULL);

    void setCurPos(QPointF pos);
    void setPen(const QPen &pen);
    void setBrush(const QBrush& brush);
};

class CShapeEllipse : public CShape {
public:
    CShapeEllipse(QGraphicsItem* item = NULL);
    void setCurPos(QPointF pos);
    void setPen(const QPen &pen);
    void setBrush(const QBrush& brush);
};

class CShapeRectangle : public CShape {
public:
    CShapeRectangle(QGraphicsItem* item = NULL);
    void setCurPos(QPointF pos);
    void setPen(const QPen &pen);
    void setBrush(const QBrush& brush);
};


class CShapeScripts : public CShape{
public:
    CShapeScripts(QGraphicsItem* item = NULL);
    void setBeginPos(QPointF pos);
    void setCurPos(QPointF pos);
    void setPen(const QPen &pen);
    void setBrush(const QBrush& brush);
};

class CShapeFactory
{
public:
    explicit CShapeFactory() {}

    static CShape* createShape(int shapeType, QGraphicsItem *parent = 0);

signals:

public slots:

};


#endif // CLINE_H
