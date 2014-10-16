#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QTimer>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);

    bool viewportEvent(QEvent *event);

    void moveScreen(QPoint p);

    QTimer panTimer;        // gesture -> move

signals:
    void screenMoved(QPoint p);
};

#endif // MYVIEW_H
