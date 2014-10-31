#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->axWidget->setControl("D:/xxxx.ppt");
    ppt = ui->axWidget;

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    ppt->deleteLater();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto view = window->querySubObject("View");
    if (!view) {
        qDebug() << "view error";
        return;
    }
    view->querySubObject("First()");
}

void MainWindow::on_pushButton_2_clicked()
{
    auto view = window->querySubObject("View");
    view->querySubObject("GotoSlide(int)", 3);
}

int i = 1;
void MainWindow::on_pushButton_3_clicked()
{
    auto view = window->querySubObject("View");
    view->querySubObject("GotoClick(int)", i);
    i++;

//    view->querySubObject("Next()");
//    qDebug() << view->querySubObject("GetClick");
}

void MainWindow::on_pushButton_4_clicked()
{
    ppt->setControl("Powerpoint.Application");
    ppt->setProperty("Visible", false);


    presentation = ppt->querySubObject("Presentations");
    QString filename("D:/xxxx.ppt");
    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filename, 1, 0, 0);
    if (!opened) {
        qDebug() << "open error";
        return;
    }
    opened->setProperty("IsFullScreen", false);
    opened->setProperty("ShowType", "ppShowTypeWindow");


    sss = opened->querySubObject("SlideShowSettings");
    if (!sss) {
        qDebug() << "SlideShowSettings error";
        return;
    }
    sss->setProperty("ShowType", 1);
    sss->querySubObject("Run()");

    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        qDebug() << "SlideShowSWindow error";
        return;
    }
    window->setProperty("Top", 100);
    window->setProperty("Left", 100);
    window->setProperty("Width", 400);
    window->setProperty("Height", 400);

//    QWidget* w = QWidget::find((WId) handle);
//    if (handle.isNull()) {
//        qDebug() << "sfadsf";
//    }
}
