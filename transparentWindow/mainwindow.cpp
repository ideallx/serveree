#include <QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
//    p.save();
//    QBrush brush(Qt::transparent);
//    p.setBrush(brush);
//    p.drawRoundedRect(rect(),20,20);
//    p.restore();
    p.fillRect(this->rect(), QColor(0, 0, 255, 20));
}
