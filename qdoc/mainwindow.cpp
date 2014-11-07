#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QAxObject* controller = new QAxObject;
    controller->setControl("Word.Application");

    QAxObject* docu = controller->querySubObject("Documents");
    QAxObject* open = docu->querySubObject("D:/abc.doc");
}
