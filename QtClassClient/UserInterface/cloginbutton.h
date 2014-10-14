#ifndef CLOGINBUTTON_H
#define CLOGINBUTTON_H

#include <QToolButton>
#include "ui_loginwidget.h"

class CLoginButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CLoginButton(QWidget *parent = 0);

    bool eventFilter(QObject *o, QEvent *e);

    void setLoggedIn(bool isLoggedIn);

private:
    void menuCreate();

    Ui::loginWidget *ui;

    void login();

private:
    bool isLoggedIn;

signals:
    void loginClicked(QString username, QString password);
    void logoutClicked();

public slots:
    void usernameCheck(QString text);
};

#endif // CLOGINWIDGET_H
