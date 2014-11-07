#include <QMenu>
#include <QVBoxLayout>
#include <QDebug>
#include <QBitmap>
#include <QTimer>

#include "../Reliable/DataUnit/CMessage.h"
#include "cloginbutton.h"

CLoginButton::CLoginButton(QWidget *parent) :
    QToolButton(parent),
    isLoggedIn(false)
{
    setPopupMode(QToolButton::InstantPopup);
    menuCreate();
    serverNoResponse.setSingleShot(true);

    connect(&serverNoResponse, &QTimer::timeout,
            this, &CLoginButton::sendNoResponse);
}

void CLoginButton::menuCreate() {
    QMenu* menu = new QMenu(this);

    QWidget *w = new QWidget(this);
    ui = new Ui::loginWidget;
    ui->setupUi(w);

    ui->toolButton->setEnabled(false);
    connect(ui->lineEdit, &QLineEdit::textChanged,
            this, &CLoginButton::usernameCheck);
    connect(ui->toolButton, &QToolButton::clicked,
            this, &CLoginButton::login);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(w);
    menu->setLayout(vlayout);

    QPixmap pixmap(":/back/ui/back/combox.png");
    menu->setMask(pixmap.mask());
    menu->setStyleSheet("color:white; background-color: rgb(85, 92, 120);");

    setMenu(menu);
    menu->installEventFilter(this);
}

bool CLoginButton::eventFilter(QObject *o, QEvent *e) {
    if(e->type() == QEvent::Show) {
        QMenu *event_menu = static_cast<QMenu *>(o);
        if(event_menu == NULL)
            return false;
        const QPoint point = parentWidget()->mapToGlobal((geometry().bottomRight() + geometry().bottomLeft()) / 2);
        event_menu->move(point.x() - event_menu->width() / 2, point.y() + 2);
    }
    return QToolButton::eventFilter(o, e);
}

void CLoginButton::setLoggedIn(bool isLoggedInSuccess) {
    isLoggedIn = isLoggedInSuccess;
    if (isLoggedIn) {
        ui->toolButton->setIcon(QIcon(":/word/ui/word/leaveclass.png"));
    } else {
        ui->toolButton->setIcon(QIcon(":/word/ui/word/enterclass.png"));
    }
}

void CLoginButton::usernameCheck(QString text) {
    if (text.size() > 1) {
        ui->toolButton->setEnabled(true);
    } else {
        ui->toolButton->setEnabled(false);
    }
}

void CLoginButton::setAccount(QString username, QString password) {
    ui->lineEdit->setText(username);
    ui->lineEdit_2->setText(password);
}

void CLoginButton::login()
{
    if (isLoggedIn) {
        emit logoutClicked();
    } else {
        emit loginClicked(ui->lineEdit->text(), ui->lineEdit_2->text());
    }

    serverNoResponse.start(2000);
}

void CLoginButton::sendNoResponse() {
    emit sendResultPrompt(ErrorNoResponseFromServer);
    menu()->setHidden(true);
}

void CLoginButton::stopTimer() {
    serverNoResponse.stop();
}
