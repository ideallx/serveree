#include <QAction>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel model(4, 1);
    ui->listView->setModel(&model);

    for (int i = 0; i < 4; i++) {
        QModelIndex index = model.index(i, 1, QModelIndex());
        model.setData(index, QVariant(i));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
