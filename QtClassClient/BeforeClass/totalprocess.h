#ifndef TOTALPROCESS_H
#define TOTALPROCESS_H

#include <QObject>

#include "logindialog.h"
#include "dialogclasschoose.h"

#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"
#include "../BizLogic/CBusinessLogic.h"
#include "../Message/CMsgObject.h"
#include "../Reliable/Server/CWSServer.h"


class TotalProcess : public QObject
{
    Q_OBJECT
public:
    explicit TotalProcess(int argc, char* argv[]);
    virtual ~TotalProcess();

    void buildBoard(int role);
    void buildNetwork();

    void buildOldStyle();

signals:
    void endLoginDialog();

public slots:
    void setUnPw(QString username, QString password);
    void buildUI();
    void reviewClass(QString className);

private:
    void parseParam(int argc, char* argv[]);

private:
    MainWindow *ui;
    LoginDialog *ld;
    CClientNet* cn;
    CBusinessLogic* bl;
    DialogClassChoose* dcc;

private:
    QString serverIp;
    QString username;
    QString password;
};

#endif // TOTALPROCESS_H
