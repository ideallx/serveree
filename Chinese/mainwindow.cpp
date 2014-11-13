#include <QDebug>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QByteArray AllPrompts[] = {
    "成功",
    "登录成功",
    "登出成功",
    "课件下载成功",

    "已经登录",

    "用户名错误",
    "密码错误",
    "未知错误",
    "播放失败",

    "暂不支持该格式的文件",
    "敬请期待",
    "服务器没有响应",
    "文件已存在"
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str;
    str = QString::fromLocal8Bit("第三方");
    qDebug() << str;

//    tr = QFileDialog::getOpenFileName();
    qDebug() << QString::fromLocal8Bit(AllPrompts[2]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
