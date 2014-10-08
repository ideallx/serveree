#ifndef QECLASS_H
#define QECLASS_H

#include <QDialog>
#include <QWidget>
#include <QMouseEvent>

#define PADDING 2
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP };

namespace Ui {
class QEClass;
}


class QEClass : public QDialog
{
    Q_OBJECT

public:

    explicit QEClass(QWidget *parent = 0);
    void setBackgroundImage(QPixmap&pixmap);
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void region(const QPoint &cursorGlobalPoint);

    ~QEClass();

private:
    Ui::QEClass *ui;
    QPixmap m_bkgPixmap;  // 背景图
    bool isLeftPressDown; // 判断左键是否按下
    QPoint dragPosition;  // 窗口移动拖动时需要记住的点
    Direction dir;        // 窗口大小改变时，记录改变方向


//public slots:

signals:
    void loginClicked();
};

#endif // QECLASS_H
