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

signals:

public slots:

private:
    bool isDeprecated;
    QTimer panTimer;        // gesture -> move
};

#endif // MYVIEW_H
