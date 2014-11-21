#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
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

private slots:
    void on_tbEnterClass_clicked();
    void on_tbExit_clicked();

signals:
    void loginClass(QString username, QString password);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
