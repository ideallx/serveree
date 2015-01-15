#include "dialogchooseshape.h"
#include "ui_dialogchooseshape.h"

DialogChooseShape::DialogChooseShape(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseShape)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

DialogChooseShape::~DialogChooseShape()
{
    delete ui;
}
