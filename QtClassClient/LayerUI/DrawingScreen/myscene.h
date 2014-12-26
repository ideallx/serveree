#ifndef MYSCENE_H
#define MYSCENE_H

#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QMap>
#include <QMutex>
#include <QTimer>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>

#include "../../Reliable/DataUnit/CMessage.h"
#include "../MsgGenerator/cgraphicmsgcreator.h"
#include "../../Message/CMsgObject.h"

class CShape;
class DataSingleton;

enum MoveType {
    MovePending,
    MoveScreen,
    MoveDraw
};

class DrawingSettingData {
public:
    int     drawingType;    // the type of shape drawing by the client user
    QPen    pen;            // the pen/brush of this client user
    QBrush  brush;
};

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyScene(DWORD sceneID, QGraphicsView* view, QObject *parent = 0, CMsgObject* msgParent = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    CShape* createNewItem(TS_UINT64 uid, int shapeType, QPointF curPoint);

    void actMove(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveEnd(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveBegin(TS_GRAPHIC_PACKET& graphicMsg);

    void actErase(TS_GRAPHIC_PACKET& graphicMsg);

    void actMoveScreen(TS_GRAPHIC_PACKET& graphicMsg);

    void setBackground(QPixmap pix);

    inline void setWriteable(bool set) { isWriteable = set; }

    void playMedia(QMediaPlayer* player);

    inline void setView(QGraphicsView* view) { m_view = view; }

public slots:

    void changeShapeByUI(int shape);

    void setPenWidth(int width) { setDraw.pen.setWidth(width); toolChanged = true; isEraser = false;}

    void setPenColor(QColor c) { setDraw.pen.setColor(c); toolChanged = true ; isEraser = false; }

    void setBrushColor(QColor c) { setDraw.brush = QBrush(c); toolChanged = true; isEraser = false; }

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
    bool                                    isEraser;       // is in eraser mode

    QMap<TS_UINT64, CShape*>                lastItems;      // the recent shape each user was drawing
    QMap<TS_UINT64, QPair<QPen, QBrush> >   toolsMap;       // the pen and brush each user was using


    MoveType                                mt;             // use for multi-finger touch
    QPointF                                 cachedPos;      // begin point cache for multi-finger touch
    QTimer                                  panFixer;       // begin drawing when move type isnot move screen

    QPointF                                 lastPos;        // last move point used when move type changed to movemode
    bool                                    isWriteable;
    QGraphicsPixmapItem                     *m_backpixmap;
    QGraphicsVideoItem*                     media;

    DrawingSettingData                      setDraw;
    DrawingSettingData                      setErase;

    DataSingleton                           *ds;
    QGraphicsView*                          m_view;
};

#endif // MYSCENE_H
