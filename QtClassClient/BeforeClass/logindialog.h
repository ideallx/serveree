#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTimer>
#include "../Message/CMsgObject.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog, public CMsgObject
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void setUsernamePassword(QString username, QString password);

    void ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote);

    void setPrompt(int result);
    void showPrompt(int result);

    void setLoadProgress(int permillage);


private slots:
    void on_tbEnterClass_clicked();
    void on_tbExit_clicked();

    void sendNoResponse();

    void on_leUsername_textChanged(const QString &arg1);

    void on_lePassword_textChanged(const QString &arg1);

    void on_tbReplay_clicked();

signals:
    void loginClass(QString username, QString password);
    void loginSuccess();
    void endTimer();
    void promptChanged(int result);
    void classReview(QString className);
    void progressChanged(int value);

private:
private:
    Ui::LoginDialog *ui;
    QTimer serverNoResponse;
};

#endif // LOGINDIALOG_H
