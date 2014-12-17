#include "dialogclasschoose.h"
#include "ui_dialogclasschoose.h"
#include "dialogcreateclass.h"

DialogClassChoose::DialogClassChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClassChoose)
{
    ui->setupUi(this);

    connect(this, &DialogClassChoose::classCreated,
            this, &DialogClassChoose::addClassItem);
}

DialogClassChoose::~DialogClassChoose()
{
    delete ui;
}

void DialogClassChoose::on_tbCreateClass_clicked()
{
    DialogCreateClass dcc(this, this);
    dcc.exec();
}

void DialogClassChoose::addClassItem(QString classname) {
    // ui->listWidget->addItem(classname);
}

void DialogClassChoose::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(wParam);
    Q_UNUSED(lParam);
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;

    switch (head->type) {
    case CREATECLASS:
        {
            DOWN_CREATECLASS* down = (DOWN_CREATECLASS*) &msg;
            if (down->failcode == Success) {
                emit classCreated(QString::fromLocal8Bit((char*) down->info.className));
            } // TODO else
        }
        break;
    }
}

void DialogClassChoose::on_listWidget_doubleClicked(const QModelIndex &index)
{

}
