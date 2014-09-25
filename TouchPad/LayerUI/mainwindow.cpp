#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new MyScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
