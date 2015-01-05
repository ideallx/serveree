#include <QDebug>
#include "cgraphicmsgcreator.h"

CGraphicMsgCreator::CGraphicMsgCreator(DWORD sceneID) :
    curShapeID(0),
    curShapeType(NONE),
    curPenBrushid(0),
    sceneID(sceneID) {
}

void CGraphicMsgCreator::create(DWORD type, QPointF p) {
    begin = p;
    curShapeType = type;
}

void CGraphicMsgCreator::buildCommonInfo(TS_GRAPHIC_PACKET& msg) {
    msg.SceneID = sceneID;
    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
}

void CGraphicMsgCreator::generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isBegin) {
    if (isBegin) {
        curShapeID++;
        msg.graphicsType = GraphicPacketBeginMove;
    } else {
        msg.graphicsType = GraphicPacketNormal;
    }
    buildCommonInfo(msg);

    msg.data.Alpha = 1;
    msg.data.BeginFlag = isBegin;
    msg.data.PageID = 0;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
    msg.data.ShapeID = curShapeID;
    msg.data.ShapeType = curShapeType;
    msg.data.BeginPx = begin.x();
    msg.data.BeginPy = begin.y();
}

void CGraphicMsgCreator::generateEraserData(TS_GRAPHIC_PACKET& msg, QPointF p,
                                            TS_UINT64 uid,
                                            DWORD shapeID) {
    msg.graphicsType = GraphicPacketEraser;
    buildCommonInfo(msg);

    msg.eraser.targetUID = uid;
    msg.eraser.shapeID = shapeID;
    msg.eraser.PointX = p.x();
    msg.eraser.PointY = p.y();
    qDebug() << "eraser: " << uid << shapeID;
}

void CGraphicMsgCreator::generateScreenMove(TS_GRAPHIC_PACKET& msg, QPoint p) {
    msg.graphicsType = GraphicPacketMoveScreen;
    buildCommonInfo(msg);

    msg.data.BeginFlag = true;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
}

void CGraphicMsgCreator::generatePenBrushData(TS_GRAPHIC_PACKET& msg, QPen& p, QBrush& b) {
    msg.graphicsType = GraphicPacketPenBrush;
    buildCommonInfo(msg);

    curPenBrushid++;
    msg.tool.brushB = b.color().blue();
    msg.tool.brushG = b.color().green();
    msg.tool.brushR = b.color().red();
    msg.tool.brushid = curPenBrushid;

    msg.tool.penR = p.color().red();
    msg.tool.penG = p.color().green();
    msg.tool.penB = p.color().blue();
    msg.tool.penWidth = p.width();
    msg.tool.penid = curPenBrushid;
}

void CGraphicMsgCreator::generateClearScreen(TS_GRAPHIC_PACKET& msg) {
    msg.graphicsType = GraphicPacketCls;
    buildCommonInfo(msg);
}
