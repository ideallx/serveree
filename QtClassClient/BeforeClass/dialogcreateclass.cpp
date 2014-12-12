#include "dialogcreateclass.h"
#include "ui_dialogcreateclass.h"

DialogCreateClass::DialogCreateClass(QWidget *parent, CMsgObject* msgParent)
    : QDialog(parent)
    , CMsgObject(msgParent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ds = DataSingleton::getInstance();
}

DialogCreateClass::~DialogCreateClass()
{
    delete ui;
}

void DialogCreateClass::on_buttonBox_accepted()
{
    ts_msg msg;
    UP_CREATECLASS* up = (UP_CREATECLASS*) &msg;
	memcpy(up->className, ui->leClassName->text().toLocal8Bit().data(), 40);
	memset(up->nickname, 0, 20);

    up->uid = ds->getUID();
    up->head.size = sizeof(UP_CREATECLASS);
    up->head.type = CREATECLASS;

    sendToDown(msg, 0, 0, false);
}
