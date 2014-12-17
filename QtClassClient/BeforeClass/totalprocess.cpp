#include <iostream>
#include <QtConcurrent>
#include "totalprocess.h"

using namespace std;

TotalProcess::TotalProcess(int argc, char* argv[]) {
    parseParam(argc, argv);

    // buildOldStyle();
    buildNetwork();

    ld->exec();
    qDebug() << "ld terminated";
    //exit(0);        // TODO how to do it better?
    return;
}

TotalProcess::~TotalProcess() {
    delete ui;
    delete bl;
    delete cn;

    // delete ld;
    // delete dcc;
}

void TotalProcess::setUnPw(QString username, QString password) {
    this->username = username;
    this->password = password;
}

void TotalProcess::parseParam(int argc, char* argv[]) {
    if (argc == 2) {        // argv[1] should be :    //192.168.1.123/teacher1/11
        QString para = QString::fromLocal8Bit(argv[1]);
        auto list = para.split('/');
        int size = list.size();
        if (size < 3)
            return;

        serverIp = list[size - 3];
        username = list[size - 2];
        password = list[size - 1];

        if ('%' == username[0])
            username = QUrl::fromPercentEncoding(username.toLatin1().data());
    } else {
        FILE* fp = freopen("config.txt", "r", stdin);
        char username[30];
        char password[30];
        char serverip[30];

        if (fp != NULL) {
            cin >> serverip >> username >> password;
            this->serverIp = serverip;
            this->username = username;
            this->password = password;
            fclose(stdin);
        }
    }

    if (serverIp.isNull())
        serverIp = "192.168.1.123";
}

void TotalProcess::buildOldStyle() {
    bl = new CBusinessLogic;
    cn = new CClientNet;
    ui = new MainWindow;

    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("BIZ", bl);
    ma->registerModule("NET", cn);
    ma->registerModule("UI", ui);

    ui->addDownReceiver(bl);
    bl->addDownReceiver(cn);

    cn->addUpReceiver(bl);
    bl->addUpReceiver(ui);

    cn->SetServerAddr(0, serverIp.toLatin1().data(), 2222);
    ui->enterClass(username, password);

    ui->show();
}

void TotalProcess::buildNetwork() {
    bl = new CBusinessLogic;
    cn = new CClientNet;
    ld = new LoginDialog;

    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("BIZ", bl);
    ma->registerModule("NET", cn);
    ma->registerModule("UILOG", ld);

    ld->addDownReceiver(bl);
    bl->addDownReceiver(cn);

    cn->addUpReceiver(bl);
    bl->addUpReceiver(ld);

    cn->SetServerAddr(0, serverIp.toLatin1().data(), 2222);

    // struct sockaddr_in result;
    // cn->scanServer(result);

    connect(ld, &LoginDialog::loginClass,
            this, &TotalProcess::setUnPw);
    connect(ld, &LoginDialog::loginSuccess,
            this, &TotalProcess::buildBoard);
    connect(this, &TotalProcess::endLoginDialog,
            ld, &LoginDialog::accept);
    ld->setUsernamePassword(username, password);
}

void TotalProcess::buildBoard(int role) {
    qDebug() << "build board";
    ld->showPrompt(NormalCourseLoading);
    bl->removeUpReceiver(ld);

    int progress = 0;
    while (progress < 995) {
        qDebug() << progress;
        ld->setLoadProgress(progress);
        progress = cn->loadProgress();
        iop_usleep(100);
    }
    qDebug() << "load class complete";
    ld->hide();

    ui = new MainWindow;
    ui->addDownReceiver(bl);
    bl->addUpReceiver(ui);
    ui->setRole(static_cast<RoleOfClass> (role));
    ui->show();
    ui->loadComplete();

    // emit endLoginDialog();

//    ui = new MainWindow;
//    ui->addDownReceiver(bl);
//    bl->addUpReceiver(ui);
//    ui->setRole(static_cast<RoleOfClass> (role));
//    ui->show();

//	ui->loadComplete();

//    CModuleAgent *ma = CModuleAgent::getUniqueAgent();
//    ui = new MainWindow;
//    ui->setRole(static_cast<RoleOfClass> (role));
//    ma->registerModule("UI", ui);
//    ui->addDownReceiver(bl);
//    bl->addUpReceiver(ui);

//    // ui->enterClass(username, password);
//    ui->show();
}

void TotalProcess::buildUI() {
    qDebug() << "build";
    ld->hide();
    ui = new MainWindow;
    ui->addDownReceiver(bl);
    bl->addUpReceiver(ui);
    // ui->setRole(static_cast<RoleOfClass> (role));
    ui->show();
    ui->loadComplete();
}
