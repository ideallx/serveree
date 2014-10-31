#include <QDebug>
#include "mytransview.h"

MyTransView::MyTransView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MyTransView::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.fillRect(80, 80, 80, 80, QColor(255, 0, 0));
}
