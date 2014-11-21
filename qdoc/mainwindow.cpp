#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new QAxObject;
    ui->axWidget->setControl("Word.Application");
    controller = ui->axWidget->querySubObject("Documents");
    if (!controller)
        qDebug() << "fff";
    auto open = controller->querySubObject("Open(QString)", QString("D:/abc.doc"));
    if (!open)
        qDebug() << "ddd";
}

MainWindow::~MainWindow()
{
    delete ui;
}
