#include <QMenu>
#include <QVBoxLayout>
#include <QDebug>
#include <QBitmap>
#include "cloginbutton.h"

CLoginButton::CLoginButton(QWidget *parent) :
    QToolButton(parent),
    isLoggedIn(false)
{
    setPopupMode(QToolButton::InstantPopup);
    menuCreate();
}

void CLoginButton::menuCreate() {
    QMenu* menu = new QMenu(this);

    QWidget *w = new QWidget(this);
    ui = new Ui::loginWidget;
    ui->setupUi(w);

    ui->toolButton->setEnabled(false);
    connect(ui->toolButton, &QToolButton::clicked,
            this, &CLoginButton::login);
    connect(ui->lineEdit, &QLineEdit::textChanged,
            this, &CLoginButton::usernameCheck);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(w);
    menu->setLayout(vlayout);

    QPixmap pixmap(":/back/ui/back/combox.png");
    menu->setMask(pixmap.mask());
    menu->setStyleSheet("background-color: rgb(85, 92, 120);");

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

void CLoginButton::login() {
    if (isLoggedIn) {
        emit logoutClicked();
    } else {
        emit loginClicked(ui->lineEdit->text(), ui->lineEdit_2->text());
    }
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
    if (text.size() > 6) {
        ui->toolButton->setEnabled(true);
    } else {
        ui->toolButton->setEnabled(false);
    }
}
