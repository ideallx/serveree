#include <iostream>
#include "totalprocess.h"

using namespace std;

static bool isProgramRunning;

TotalProcess::TotalProcess(int argc, char* argv[])
    : ui(NULL)
    , ld(NULL)
    , cn(NULL)
    , bl(NULL)
    , dcc(NULL) {
    isProgramRunning = true;
    parseParam(argc, argv);

    // buildOldStyle();
    buildNetwork();

    int answer = ld->exec();
	if (answer != 0) {
		exit(0);
	}
    qDebug() << "ld terminated";
    // exit(0);        // TODO how to do it better?

    return;
}

TotalProcess::~TotalProcess() {
    isProgramRunning = false;
    iop_usleep(100);
    DESTROY(ui);
    DESTROY(bl);
    DESTROY(cn);

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
            fclose(fp);
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
    connect(ld, &LoginDialog::classReview,
            this, &TotalProcess::replayClass);

    ld->setUsernamePassword(username, password);
}

void loadCourse(LoginDialog* ld, CClientNet* cn) {
    int progress = 0;
    while (progress < 980 && isProgramRunning) {
        qDebug() << "progress is " << progress;
        emit ld->progressChanged(progress);
        // ld->setLoadProgress(progress);
        progress = cn->loadProgress();
        iop_usleep(100);
    }
    qDebug() << "load class complete";
}

void TotalProcess::buildBoard() {
    qDebug() << "build board";
    ld->showPrompt(NormalCourseLoading);
    bl->removeUpReceiver(ld);

    connect(&threadLoad, SIGNAL(finished()),
            this, SLOT(buildUI()));
    threadLoad.setFuture(QtConcurrent::run(loadCourse, ld, cn));
}

void TotalProcess::buildUI() {
    qDebug() << "build";
    ui = new MainWindow;
    ui->addDownReceiver(bl);
    bl->addUpReceiver(ui);
    // ui->setRole(static_cast<RoleOfClass> (role));
    ui->loadComplete();
    ld->hide();
    ui->show();
}

void msgThread(CClientNet* cn, QString classname, MainWindow* ui) {
    if (cn->replayInit(classname) != Success)
        return;                 // TODO error checking
    int sleepTime;
    bool result = true;
    iop_usleep(1000);           // wait 1 second to start
    while (isProgramRunning && result) {
        result = cn->replays(sleepTime);
        iop_usleep(sleepTime);
        //iop_usleep(5);
    }
    if (!result) {              // if the replay is ended normally
        ui->sendPrompt(QString::fromLocal8Bit("Â¼Ïñ²¥·ÅÍê±Ï"));
    }
    qDebug() << "replays end";
}

void TotalProcess::replayClass(QString className) {
	ld->done(0);

    bl->removeUpReceiver(ld);

    ui = new MainWindow;
	ui->loadComplete();

    bl->addUpReceiver(ui);
	bl->setReviewMode();
    ui->addDownReceiver(bl);

    ui->setRole(RoleReplay);
    ui->show();

    // iop_thread_create(&pthread_input, MsgInProc, (void *) this, 0);
    threadRev = QtConcurrent::run(msgThread, cn, className, ui);
	iop_usleep(100);
}
