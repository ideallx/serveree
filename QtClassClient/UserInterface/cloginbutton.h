#ifndef CLOGINBUTTON_H
#define CLOGINBUTTON_H

#include <QToolButton>
#include <QTimer>
#include "ui_loginwidget.h"

class CLoginButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CLoginButton(QWidget *parent = 0);

    bool eventFilter(QObject *o, QEvent *e);

    void setLoggedIn(bool isLoggedIn);

    void setAccount(QString username, QString password);

private:
    void menuCreate();
    void sendNoResponse();
    Ui::loginWidget *ui;

private:
    bool isLoggedIn;
    QTimer serverNoResponse;

signals:
    void loginClicked(QByteArray username, QByteArray password);
    void logoutClicked();
    void sendResultPrompt(int);

public slots:
    void usernameCheck(QString text);
    void stopTimer();

private slots:
    void login();
};

#endif // CLOGINWIDGET_H
