#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QtWidgets>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);

    bool viewportEvent(QEvent *event);

signals:

public slots:

private:
    QPointF lastTwoFingerPos;
    bool isDeprecated;
};

#endif // MYVIEW_H
