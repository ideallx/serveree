#include <QtWidgets>
#include "qeclass.h"
#include "ui_qeclass.h"
#include "QDebug"
#include <QRect>
#include "IpAddressWidget.h"

QEClass::QEClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QEClass)
{

    ui->setupUi(this);

    isLeftPressDown = false;
    this->dir = NONE;
    this->setFixedWidth(325);
    this->setFixedHeight(513);

    //this->ui->HLAYOUT->setGeometry(QRect(2,367,320,50));
    this->ui->EDT_USERNAME->setGeometry(2,214,320,60);
    this->ui->EDT_USERNAME->setToolTip(tr("USER"));
    this->ui->EDT_USERNAME->setToolTipDuration(2);

    this->ui->EDT_PASSWORD->setGeometry(2,291,320,60);
    this->ui->BTN_LOGIN->setGeometry(2,444,320,60);
    ui->BTN_LOGIN->setStyleSheet("background-color: rgb(249, 103, 30);");

    //this->setMinimumHeight(100);
    //this->setMinimumWidth(150);
    //设置可随框大小变化拉伸的背景图案方案一
    //只指定QDialog有背景，而不是所有
    //setStyleSheet("QDialog{border-image:url(C://Qt//Qt5.3.2//Tools//QtCreator//bin//test//QClass//res//login.png)}");

    m_bkgPixmap.load("C://Qt//Qt5.3.2//Tools//QtCreator//bin//test//QClass//res//login_background.png");

    this->setMouseTracking(true);// 追踪鼠标
}

//设置可随框大小变化拉伸的背景图案方案二
void QEClass::setBackgroundImage(QPixmap&pixmap)
{
    //判断图片是否为空
    if(pixmap.isNull()){
        qDebug() << tr("illege arguments") <<endl;
        return;
    }
    //设置窗口的背景
    QPalette    palette = this->palette();
    palette.setBrush(this->backgroundRole(),
                     QBrush(pixmap.scaled(this->size(),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation)));
    this->setPalette(palette);
}

void QEClass::resizeEvent(QResizeEvent *)
{
     setBackgroundImage(m_bkgPixmap);
}

QEClass::~QEClass()
{
    delete ui;
}

void QEClass::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
        //if(dir == NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void QEClass::mousePressEvent(QMouseEvent *event)
{
    //处理拖动逻辑
    switch(event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if(dir != NONE) {//还没使用Region函数
            this->mouseGrabber();//返回获取到焦点的widget。可返回值未被用到
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();//????
        }
        break;
//    case Qt::RightButton:
//        this->close();
//        break;
    default:
        QDialog::mousePressEvent(event);
    }

}

void QEClass::mouseMoveEvent(QMouseEvent *event)
{
    //处理拉伸缩放逻辑
    QPoint gloPoint = event->globalPos();//光标当前点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {//未被按下时
        this->region(gloPoint);//此处被调用
    } else {

        if(dir != NONE) {
            QRect rMove(tl, rb);//窗口的当前位置信息

            switch(dir) {
            case LEFT:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    QDialog::mouseMoveEvent(event);
}


void QEClass::region(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}
