#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->axWidget->setControl("bb.xlsx");
//    ui->axWidget->setControl("Powerpoint.Application");
//    presentation = ui->axWidget->querySubObject("Presentations");
//    QString filename("D:/xxxx.ppt");
//    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filename, 1, 0, 0);
//    if (!opened) {
//        qDebug() << "open error";
//        return;
//    }

//    sss = opened->querySubObject("SlideShowSettings");
//    if (!sss) {
//        qDebug() << "SlideShowSettings error";
//        return;
//    }
//    sss->setProperty("RangeType", 1);
//    sss->setProperty("SlideShowName", "Quick Show");
//    sss->querySubObject("Run");
}

MainWindow::~MainWindow()
{
    ui->axWidget->setControl("");
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        qDebug() << "SlideShowSWindow error";
        return;
    }

    auto view = window->querySubObject("View");
    if (!view) {
        qDebug() << "view error";
        return;
    }
}
