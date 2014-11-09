#ifndef MYSCENE_H
#define MYSCENE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QMap>
#include <QMutex>
#include <QTimer>

#include "../Reliable/DataUnit/CMessage.h"
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

    void setBackground(QPixmap pix);

    inline void setWriteable(bool set) { isWriteable = set; }

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

    DWORD                                   sceneID;        // scene id of this scene
    CMsgObject*                             msgParent;      // mainwindow
    CGraphicMsgCreator*                     gmc;            // graphic msg generator

    set<pair<TS_UINT64, DWORD> >            eraseList;      // for recv eraser earlier than the shape
    bool                                    toolChanged;    // is pen or brush changed
    int                                     drawingType;    // the type of shape drawing by the client user
    bool                                    isEraser;       // is in eraser mode

    QMap<TS_UINT64, CShape*>                lastItems;      // the recent shape each user was drawing
    QMap<TS_UINT64, QPair<QPen, QBrush> >   toolsMap;       // the pen and brush each user was using
    QPen                                    pen;            // the pen/brush of this client user
    QBrush                                  brush;

    MoveType                                mt;             // use for multi-finger touch
    QPointF                                 cachedPos;      // begin point cache for multi-finger touch
    QTimer                                  panFixer;       // begin drawing when move type isnot move screen

    QPointF                                 lastPos;        // last move point used when move type changed to movemode
    bool                                    isWriteable;
    QGraphicsPixmapItem                     *m_backpixmap;
};

#endif // MYSCENE_H
