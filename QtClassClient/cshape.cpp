#include <QPainter>
#include "cshape.h"
#include <QDebug>

CShape* CShapeFactory::createShape(int shapeType, QGraphicsItem *parent) {
    switch (shapeType) {
    case LINE:
        return new CShapeLine(new QGraphicsLineItem(parent));
    case ELLIPSE:
        return new CShapeEllipse(new QGraphicsEllipseItem(parent));
    case RECTANGLE:
        return new CShapeRectangle(new QGraphicsRectItem(parent));
    case SCRIPTS:
        return new CShapeScripts(new QGraphicsPathItem(parent));
    default:
        return NULL;
    }
    return NULL;
}

CShape::~CShape() {
    delete item;
}

CShape::CShape(QGraphicsItem* item) :
    item(item) {

}

void CShape::setBeginPos(QPointF pos) {
    beginPos = pos;
}




CShapeLine::CShapeLine(QGraphicsItem *item) :
    CShape(item) {

}

void CShapeLine::setCurPos(QPointF pos) {
    static_cast<QGraphicsLineItem*> (item)->setLine(
                beginPos.x(), beginPos.y(),
                pos.x(), pos.y());
}

void CShapeLine::setPen(const QPen &pen) {
    static_cast<QGraphicsLineItem*> (item)->setPen(pen);
}

void CShapeLine::setBrush(const QBrush &brush) {
    Q_UNUSED(brush);
}




CShapeEllipse::CShapeEllipse(QGraphicsItem *item) :
    CShape(item) {
}

void CShapeEllipse::setCurPos(QPointF pos) {
    static_cast<QGraphicsEllipseItem*> (item)->setRect(
                beginPos.x(), beginPos.y(),
                pos.x() - beginPos.x(),
                pos.y() - beginPos.y());
}


void CShapeEllipse::setPen(const QPen &pen) {
    static_cast<QGraphicsEllipseItem*> (item)->setPen(pen);
}

void CShapeEllipse::setBrush(const QBrush &brush) {
    static_cast<QGraphicsEllipseItem*> (item)->setBrush(brush);
}




CShapeRectangle::CShapeRectangle(QGraphicsItem *item) :
    CShape(item) {
}


void CShapeRectangle::setCurPos(QPointF pos) {
    qreal x = qMin(beginPos.x(), pos.x());
    qreal y = qMin(beginPos.y(), pos.y());
    qreal w = abs(beginPos.x() - pos.x());
    qreal h = abs(beginPos.y() - pos.y());
    static_cast<QGraphicsRectItem*> (item)->setRect(x, y, w, h);
}

void CShapeRectangle::setPen(const QPen &pen) {
    static_cast<QGraphicsRectItem*> (item)->setPen(pen);
}

void CShapeRectangle::setBrush(const QBrush &brush) {
    static_cast<QGraphicsRectItem*> (item)->setBrush(brush);
}



CShapeScripts::CShapeScripts(QGraphicsItem *item) :
    CShape(item) {
}

void CShapeScripts::setBeginPos(QPointF pos) {
    CShape::setBeginPos(pos);
    QPainterPath p(pos);
    static_cast<QGraphicsPathItem*> (item)->setPath(p);
}

void CShapeScripts::setCurPos(QPointF pos) {
    QPainterPath p = static_cast<QGraphicsPathItem*> (item)->path();
    p.lineTo(pos);
    static_cast<QGraphicsPathItem*> (item)->setPath(p);
}

void CShapeScripts::setPen(const QPen &pen) {
    static_cast<QGraphicsPathItem*> (item)->setPen(pen);
}

void CShapeScripts::setBrush(const QBrush &brush) {
    Q_UNUSED(brush);
}
