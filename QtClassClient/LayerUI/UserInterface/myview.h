#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QEvent>
#include <QTimer>
#include <QGroupBox>
#include <QToolButton>
#include <QPaintEvent>
#include <QHBoxLayout>
#include "../../Reliable/DataUnit/CMessage.h"
#include "../MsgGenerator/cplayergenerator.h"


class CourseSceneInfo {
public:
    int                 backgroundMode;
    int                 newSlideNo;        // for 1 to N
    QMap<QString, int>  allSlides;
    bool                isCoursewareSide;
};


class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);

    ~MyView();

    bool viewportEvent(QEvent *event);

    void moveScreen(QPoint p);

    // if courseware scene: use csi.backgroundMode
    // else normalMode;
    void initViewBySceneID(TS_UINT64 sceneid);

    QTimer panTimer;        // gesture -> move
    QTimer zoomTimer;
    bool isLeftClicked;

    // set slide name means you have a new slide, but you dont really summon a new board so 
    // when you really summon a board, i'll create or use a former one by setSlide
    void setNewSlideName(QString slideInfo);

    void moveToSlide(bool isLeftSlide);

public slots:
    // set the lastPaintMode addtional to rawSetPaintMode
    void setPaintMode(int in);

signals:
    void screenMoved(QPoint p);


private:
    void hideButtons(bool hide = true);

    // only set the paint mode
    void rawSetPaintMode(int mode);

private:
    QString newSlideName;
    enum PaintMode pm;
    CourseSceneInfo csi;
};

#endif // MYVIEW_H
