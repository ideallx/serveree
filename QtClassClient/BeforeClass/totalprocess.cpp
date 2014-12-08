#include <iostream>
#include "totalprocess.h"

using namespace std;

TotalProcess::TotalProcess(int argc, char* argv[]) {
    parseParam(argc, argv);

    // buildOldStyle();
    buildNetwork();

    if (ld->exec() != 0) {
        exit(0);        // TODO how to do it better?
        return;
    }
}

TotalProcess::~TotalProcess() {
    delete ui;
    // delete ld;
    delete bl;
    delete cn;
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

            QFile f("aa.txt");
            f.open(QIODevice::Append);
            f.write(username);
            f.write("\r\n");
            f.write(password);
            f.write("\r\n");
            f.write(serverip);
            f.write("\r\n");
            f.close();
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
    ld->setUsernamePassword(username, password);
}

void TotalProcess::buildBoard(int role) {
    qDebug() << "build board";
    ld->showPrompt(NormalCourseLoading);
    bl->removeUpReceiver(ld);
    iop_usleep(200);
    int process = 0;
    while (process < 980) {
        ld->setLoadProgress(process);
        process = cn->loadProgress();
        qDebug() << process;
        iop_usleep(100);
    }
    delete ld;


    CModuleAgent *ma = CModuleAgent::getUniqueAgent();
    ui = new MainWindow;
    ui->setRole(static_cast<RoleOfClass> (role));
    ma->registerModule("UI", ui);
    ui->addDownReceiver(bl);
    bl->addUpReceiver(ui);

    // ui->enterClass(username, password);
    ui->show();
}
