#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new QAxObject;
    if (!controller->setControl("Word.Application"))
        qDebug() << "fuck";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbrun_clicked()
{
    docu = controller->querySubObject("Documents");
    QAxObject* open = docu->querySubObject("Open(QString)", QString("D:/abc.doc"));

}
