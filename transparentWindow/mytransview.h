#ifndef MYTRANSVIEW_H
#define MYTRANSVIEW_H

#include <QGraphicsView>
#include <QPaintEvent>

class MyTransView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyTransView(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // MYTRANSVIEW_H
