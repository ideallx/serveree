#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

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
    if (!ppt->setControl("Powerpoint.Application")) {
        ui->txShow->append("power point controler set failed");
        return;
    }
    ppt->setProperty("Visible", false);
    ui->txShow->append("application success");
    presentation = ppt->querySubObject("Presentations");
    QString filename("D:/xxxx.ppt");

    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filename, 1, 0, 0);
    if (!opened) {
        ui->txShow->append("open error");
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


    auto slides = window->querySubObject("Presentation");
    slides = slides->querySubObject("Slides(int)", 1);
    if (!slides) {
        qDebug() << "fuck";
        return;
    }
    QString fp = QDir::currentPath() + "/aaa.jpg";
    qDebug() << fp;
    slides->querySubObject("Export(QString, QString, int, int)", fp, "jpg", 1920, 1080);
    if (!slides) {
        qDebug() << "fuck";
        return;
    }

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
