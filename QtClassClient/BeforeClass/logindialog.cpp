#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include "logindialog.h"
#include "ui_logindialog.h"
#include "../LayerUI/UserInterface/prompt.h"
#include "dialogchoosereplay.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->pbDownload->setHidden(true);

    serverNoResponse.setSingleShot(true);
    connect(&serverNoResponse, &QTimer::timeout,
            this, &LoginDialog::sendNoResponse);
    connect(this, &LoginDialog::endTimer,
            &serverNoResponse, &QTimer::stop);
    connect(this, &LoginDialog::promptChanged,
            this, &LoginDialog::showPrompt);

    connect(this, &LoginDialog::progressChanged,
            this, &LoginDialog::setLoadProgress);

    //ui->tbReplay->setHidden(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_tbEnterClass_clicked()
{
    emit loginClass(ui->leUsername->text(), ui->lePassword->text());

    ts_msg msg;
    UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
    up->head.type = ENTERAGENT;
    up->head.size = sizeof(UP_AGENTSERVICE);
    up->head.sequence = 0;
    up->head.subSeq = 0;
    up->classid = 10000;
    memcpy(up->username, ui->leUsername->text().toLocal8Bit().data(), 20);
    memcpy(up->password, ui->lePassword->text().toLocal8Bit().data(), 20);

    // make sure the login msg sent and recved
    for (int i = 0; i < 3; i++) {
        sendToDown(*(ts_msg*) &msg, 0, 0, false);
    }
    serverNoResponse.start(1000);
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
    ui->tbEnterClass->setEnabled(true);
}

void LoginDialog::sendNoResponse() {
    ui->lbPrompt->setText(Prompt::getPrompt(ErrorNoResponseFromServer));
}

void LoginDialog::ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(event);
    Q_UNUSED(lParam);
    Q_UNUSED(isRemote);
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    switch (head->type) {
    case ENTERCLASS:
    case LEAVECLASS:
    case ENTERAGENT:
        {
            emit endTimer();
            DOWN_AGENTSERVICE* down = reinterpret_cast<DOWN_AGENTSERVICE*> (&msg);
            qDebug() << "login result:" << down->result;
            ui->lbPrompt->setText(Prompt::getPrompt(down->result));
            if (down->result == SuccessEnterClass)
                emit loginSuccess();
//            sendResultPrompt(down->result);
//            recvClassInfo();
//            switch (down->result) {
//            case SuccessEnterClass:
//                enterClassResult(true);
//                setRole(down->role);
//                break;
//            case SuccessLeaveClass:
//                leaveClassResult(true);
//            }
        }
        break;
    }
}

void LoginDialog::setPrompt(int result) {
    emit promptChanged(result);
    qDebug() << "set prompt";
}

void LoginDialog::showPrompt(int result) {
    ui->lbPrompt->setText(Prompt::getPrompt(result));
    qDebug() << "show prompt";
}

void LoginDialog::setLoadProgress(int permillage) {
    ui->pbDownload->setHidden(false);
    ui->pbDownload->setValue(permillage / 10);
}

void LoginDialog::on_leUsername_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if (ui->leUsername->text().size() > 1 &&
            ui->lePassword->text().size() > 1) {
        ui->tbEnterClass->setEnabled(true);
    } else {
        ui->tbEnterClass->setEnabled(false);
    }
}

void LoginDialog::on_lePassword_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if (ui->leUsername->text().size() > 1 &&
            ui->lePassword->text().size() > 1) {
        ui->tbEnterClass->setEnabled(true);
    } else {
        ui->tbEnterClass->setEnabled(false);
    }
}

void LoginDialog::on_tbReplay_clicked()
{
    DialogChooseReplay dcr;
    hide();
    connect(&dcr, &DialogChooseReplay::classChosen,
            this, &LoginDialog::classReview);
    connect(&dcr, &DialogChooseReplay::goBack,
            this, &LoginDialog::show);
    dcr.exec();
}
