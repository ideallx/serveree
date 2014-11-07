#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Form f;
    ui->listWidget->setItemWidget(ui->listWidget->item(1), &f);
}

MainWindow::~MainWindow()
{
    delete ui;
}
