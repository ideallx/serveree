#ifndef CGRAPHICMSGCREATOR_H
#define CGRAPHICMSGCREATOR_H

#include <QPointF>
#include <QPen>
#include <QBrush>
#include "../../Reliable/DataUnit/CMessage.h"

// used only for client user yourself

class CGraphicMsgCreator
{
public:
    CGraphicMsgCreator(DWORD sceneID);
    ~CGraphicMsgCreator();

    DWORD       curShapeID;         // added by self when begin drawing
    DWORD       curShapeType;
    QPointF     begin;              // begin point of current shape
    DWORD       sceneID;
    DWORD       curPenBrushid;

    void create(DWORD type, QPointF in);

    void generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isBegin);

    void generatePenBrushData(TS_GRAPHIC_PACKET& msg, QPen& p, QBrush& b);

    void generateClearScreen(TS_GRAPHIC_PACKET& msg);

    void generateEraserData(TS_GRAPHIC_PACKET& msg, QPointF p, TS_UINT64 uid, DWORD shapeID);

    void generateScreenMove(TS_GRAPHIC_PACKET& msg, QPoint p);

    void buildCommonInfo(TS_GRAPHIC_PACKET& msg);
};

#endif // CGRAPHICMSGCREATOR_H
