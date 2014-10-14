#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->groupBox_2->setHidden(true);

    ui->listWidget->addItem("Li Xiang\nshlxzj@gmail.com");
    ui->listWidget->addItem("ideallx\nshlxzj@gmail.com");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tbMyClass_clicked()
{
    ui->groupBox_2->setHidden(!ui->groupBox_2->isHidden());
}

void MainWindow::on_btClassInfo_clicked()
{
    ui->groupBox_2->setHidden(true);
}
