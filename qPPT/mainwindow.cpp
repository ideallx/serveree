#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    opened = NULL;
    ui->setupUi(this);
    ppt = ui->axWidget;

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    if (opened)
        opened->dynamicCall("Close()");
    ppt->dynamicCall("Quit()");
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
    if (!view) {
        qDebug() << "view error";
        return;
    }
    view->dynamicCall("Previous()");
    auto slide = view->querySubObject("Slide");
    if (NULL == slide) {
        return;
    }

    qDebug() << "slide index is" << slide->dynamicCall("SlideIndex").toInt();
}

int i = 1;
void MainWindow::on_pushButton_3_clicked()
{
    auto view = window->querySubObject("View");
    if (!view) {
        qDebug() << "view error";
        return;
    }
    view->dynamicCall("Next()");

    auto slide = view->querySubObject("Slide");
    if (NULL == slide) {
        return;
    }
    qDebug() << "slide index is" << slide->dynamicCall("SlideIndex").toInt();
}

#include <QFileDialog>
void MainWindow::on_pushButton_4_clicked()
{
    QString filename = "E:\\ff ff\\xxxx.ppt"; //= QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;
    if (!ppt->setControl("Powerpoint.Application")) {
        ui->txShow->append("power point controler set failed");
        return;
    }
    ui->txShow->append("application success");
    presentation = ppt->querySubObject("Presentations");

    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filename, 1, 1, 0);
    if (!opened) {
        ui->txShow->append("open error");
        return;
    }
    opened->setProperty("IsFullScreen", false);


    sss = opened->querySubObject("SlideShowSettings");
    if (!sss) {
        qDebug() << "SlideShowSettings error";
        return;
    }
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


    auto slides = window->querySubObject("Presentation");
    slides = slides->querySubObject("Slides");
    if (!slides) {
        ui->txShow->append("slides failed");
        return;
    }
    int slideNum = slides->dynamicCall("Count").toInt();
    qDebug() << "slideNum:" << slideNum;


//    QString fp = QDir::currentPath() + "/aaa.jpg";
//    qDebug() << fp;
//    slides->querySubObject("Export(QString, QString, int, int)", fp, "jpg", 1920, 1080);
//    if (!slides) {
//        qDebug() << "fuck";
//        return;
//    }

//    QWidget* w = QWidget::find((WId) handle);
//    if (handle.isNull()) {
//        qDebug() << "sfadsf";
//    }
}

#include <QDesktopServices>
void MainWindow::on_label_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}
