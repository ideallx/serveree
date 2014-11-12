#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->axWidget->dynamicCall("LoadMovie(long, QString)", 0, "C:/eclass/1.swf");

}

MainWindow::~MainWindow()
{
    delete ui;
}
