#include <QDebug>
#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->pbDownload->setHidden(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_tbEnterClass_clicked()
{
    emit loginClass(ui->leUsername->text(), ui->lePassword->text());
}

void LoginDialog::on_tbExit_clicked()
{
    done(1);
}

void LoginDialog::setUsernamePassword(QString username, QString password) {
    if (username.isNull() || password.isNull())
        return;

    ui->leUsername->setText(username);
    ui->lePassword->setText(password);
}
