#include <QDebug>
#include "dialogpixmap.h"
#include "ui_dialogpixmap.h"

DialogPixmap::DialogPixmap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPixmap)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

DialogPixmap::~DialogPixmap()
{
    delete ui;
}

void DialogPixmap::on_toolButton_clicked()
{
    accept();
}
