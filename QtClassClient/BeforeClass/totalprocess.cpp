#include <iostream>
#include "totalprocess.h"

using namespace std;

TotalProcess::TotalProcess(int argc, char* argv[]) {
    parseParam(argc, argv);

    ld = new LoginDialog;

    connect(ld, &LoginDialog::loginClass,
            this, &TotalProcess::setUnPw);
    ld->setUsernamePassword(username, password);
    if (ld->exec() != 0) {
        exit(0);        // TODO how to do it better?
        return;
    }
    buildBoard();
}

TotalProcess::~TotalProcess() {
    delete ld;
    delete ui;
    delete cn;
    delete bl;
}

void TotalProcess::setUnPw(QString username, QString password) {
    this->username = username;
    this->password = password;
    ld->done(0);
}

void TotalProcess::parseParam(int argc, char* argv[]) {
    if (argc == 2) {        // argv[1] should be :    //192.168.1.123/teacher1/11
        QString para(argv[1]);
        auto list = para.split('/');
        int size = list.size();
        if (size < 3)
            return;

        serverIp = list[size - 3];
        username = list[size - 2];
        password = list[size - 1];
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

void TotalProcess::buildBoard() {
    ui = new MainWindow;
    bl = new CBusinessLogic;
    cn = new CClientNet;

    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("UI", ui);
    ma->registerModule("BIZ", bl);
    ma->registerModule("NET", cn);

    ui->addDownReceiver(bl);
    bl->addDownReceiver(cn);

    cn->addUpReceiver(bl); 
    bl->addUpReceiver(ui);

    cn->SetServerAddr(0, serverIp.toLatin1().data(), 2222);
    ui->enterClass(username, password);
    ui->show();
}
