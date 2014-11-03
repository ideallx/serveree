#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "cpromptframe.h"

#include "../LayerUI/cpromptframe.h"


thread_ret_type thread_func_call UIMsgProc(LPVOID lpParam) {
    iop_thread_detach_self();
    MainWindow* m = (MainWindow*) lpParam;
    if (NULL == m) {
        iop_thread_exit(0);
        return 0;
    }
    m->msgProc();
    iop_thread_exit(0);
    return 0;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_userRole(RoleStudent),
    ui(new Ui::MainWindow),
    isRunning(false) {
    ui->setupUi(this);

    scene = new MyScene(SelfUID, this, this);
    sceneMap.insert(SelfUID, scene);
    scene = new MyScene(TeacherUID, this, this);
    sceneMap.insert(TeacherUID, scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMsgObject(this);

    connect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
            scene, &MyScene::setPenWidth);
    connect(ui->tbPalette, &ColorCombox::sigColorChanged,
            scene, &MyScene::setPenColor);
    connect(ui->tbShape, &CShapeChooser::signalShapeChanged,
            scene, &MyScene::changeShapeByUI);
    connect(ui->tbEraser, &QToolButton::clicked,
            scene, &MyScene::revocation);
    connect(ui->graphicsView, &MyView::screenMoved,
            scene, &MyScene::moveScreen);

    // move to UI thread
    connect(this, &MainWindow::enOrLeaveClass,
            this, &MainWindow::classIcon);
    connect(this, &MainWindow::drawShape,
            this, &MainWindow::drawScene);
    connect(this, &MainWindow::addScene,
            this, &MainWindow::addSceneSlot);
    connect(this, &MainWindow::promptSent,
            this, &MainWindow::showPrompt);

    ui->groupBox_2->setHidden(true);
    ui->gbCourseware->setHidden(true);

    connect(ui->tbLogin, &CLoginButton::loginClicked,
            this, &MainWindow::enterClass);
    connect(ui->tbLogin, &CLoginButton::logoutClicked,
            this, &MainWindow::leaveClass);
//    setWindowFlags(Qt::FramelessWindowHint |
//                   Qt::WindowSystemMenuHint |
//                   Qt::WindowStaysOnTopHint);

//    setAttribute(Qt::WA_TranslucentBackground, true);
//    showFullScreen();
}

MainWindow::~MainWindow() {
    isRunning = false;
    iop_thread_cancel(pthread_msg);
    delete ui;
}

void MainWindow::ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(lParam);
    if (!isRemote) {
        sendToAll(msg, 0, 0, false);
    } else {
        msgQueue.enQueue(msg);
        ReleaseSemaphore(sem_msg, 1, NULL);
	}
}

void MainWindow::changeScene(TS_UINT64 uid) {
    if (sceneMap[uid] == 0)
        return;

    if (scene == sceneMap[uid])
        return;

    disconnect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
            scene, &MyScene::setPenWidth);
    disconnect(ui->tbPalette, &ColorCombox::sigColorChanged,
            scene, &MyScene::setPenColor);
    disconnect(ui->tbShape, &CShapeChooser::signalShapeChanged,
            scene, &MyScene::changeShapeByUI);
    disconnect(ui->tbEraser, &QToolButton::clicked,
            scene, &MyScene::revocation);
    disconnect(ui->graphicsView, &MyView::screenMoved,
            scene, &MyScene::moveScreen);

    scene = sceneMap[uid];

    scene->setEraser(false);
    ui->tbEraser->setChecked(false);
    ui->graphicsView->setScene(scene);

    connect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
            scene, &MyScene::setPenWidth);
    connect(ui->tbPalette, &ColorCombox::sigColorChanged,
            scene, &MyScene::setPenColor);
    connect(ui->tbShape, &CShapeChooser::signalShapeChanged,
            scene, &MyScene::changeShapeByUI);
    connect(ui->tbEraser, &QToolButton::clicked,
            scene, &MyScene::revocation);
    connect(ui->graphicsView, &MyView::screenMoved,
            scene, &MyScene::moveScreen);
}

void MainWindow::enterClass(QString username, QString password) {
    ts_msg msg;

    UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
    up->head.type = ENTERCLASS;
    up->head.size = sizeof(UP_AGENTSERVICE);
    memcpy(up->username, username.toLatin1().data(), 20);
    memcpy(up->password, password.toLatin1().data(), 20);

    ui->tbLogin->menu()->setHidden(true);

    sendToAll(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::leaveClass() {
    ts_msg msg;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    head->type = LEAVECLASS;
    head->size = sizeof(UP_AGENTSERVICE);
    ui->tbLogin->menu()->setHidden(true);
    ui->listWidget->clear();

    sendToAll(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::enterClassResult(bool result) {
    if (result) {
        emit enOrLeaveClass(true);

        sem_msg = CreateSemaphore(NULL, 0, 10240, NULL);
        isRunning = true;
        Sleep(10);

        int rc = iop_thread_create(&pthread_msg, UIMsgProc, (void *) this, 0);
        if (0 == rc) {
            qDebug() << "enter class successfully";
        } else {
            isRunning = false;
        }
    }
}

void MainWindow::leaveClassResult(bool result) {
    if (result) {
        emit enOrLeaveClass(false);
        isRunning = false;
        CloseHandle(sem_msg);
        qDebug() << "leave class successfully";
    }
}

void MainWindow::classIcon(bool entered) {
    ui->tbLogin->setLoggedIn(entered);
}

void MainWindow::addUser(TS_UINT64 uid, QString username, bool isOnline) {
    ui->listWidget->addUser(uid, username, isOnline);
    emit addScene(uid >> 32, uid);
}

void MainWindow::removeUser(TS_UINT64 uid) {
    ui->listWidget->removeUser(uid);
    sceneMap.remove(uid);
}

void MainWindow::addSceneSlot(int uidh, int uidl) {
    TS_UINT64 uid = uidl;
    MyScene *s = new MyScene(uid, this, this);
    sceneMap.insert(uid, s);
}

void MainWindow::msgProc() {
    while (isRunning) {
        WaitForSingleObject(sem_msg, 30);
        emit drawShape();
    }
}

void MainWindow::drawScene() {
    ts_msg msg;
    if (msgQueue.deQueue(msg) == false) {
        return;
    }

    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    MyScene* theScene = sceneMap[gmsg->SceneID];
    if (theScene == NULL) {
        theScene = new MyScene(gmsg->SceneID, this, this);
        sceneMap.insert(gmsg->SceneID, theScene);
    }

    switch (gmsg->graphicsType) {
    case GraphicPacketBeginMove:
        theScene->actMoveBegin(*gmsg);
        break;
    case GraphicPacketNormal:
        theScene->actMove(*gmsg);
        break;
    case GraphicPacketPenBrush:
        theScene->setOthersPenBrush(*gmsg);
        break;
    case GraphicPacketEraser:
        theScene->actErase(*gmsg);
        break;
    case GraphicPacketCls:
        theScene->clear();
        theScene->update();
        break;
    case GraphicPacketMoveScreen:
    {
        int x = gmsg->data.PointX;
        int y = gmsg->data.PointY;
        ui->graphicsView->moveScreen(QPoint(x, y));
        break;
    }
    default:
        break;
    }
}

void MainWindow::sendPrompt(int result) {
    emit promptSent(result);
}

void MainWindow::setRole(enum RoleOfClass role) {
    m_userRole = role;
    qDebug() << (int) role;
}

void MainWindow::playPPT(QString filepath) {
    ui->graphicsView->playCourseware(filepath);
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.fillRect(this->rect(), QColor(0, 0, 0, 2));
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if (m_userRole == RoleTeacher)
        ui->listWidget->changeAuth(index.row());
}

void MainWindow::on_tbMyClass_clicked()
{
    ui->groupBox_2->setHidden(!ui->groupBox_2->isHidden());
}

void MainWindow::on_btClassInfo_clicked()
{
    ui->groupBox_2->setHidden(true);
}

void MainWindow::on_tbTeacherBoard_clicked()
{
    changeScene(TeacherUID);
}

void MainWindow::on_tbMyBoard_clicked()
{
    changeScene(SelfUID);
}

void MainWindow::on_tbCourseWare_clicked()
{
    ui->gbCourseware->setHidden(!ui->gbCourseware->isHidden());
    //playPPT("D:/xxxx2.ppt");
}

void MainWindow::on_tbBackground_clicked()
{
    CPromptFrame::prompt(PleaseWaiting);
}

void MainWindow::on_tbUpload_clicked()
{
    QString file = QFileDialog::getOpenFileName(
                this);
    QString tofile = file.split('/').last();
    if (tofile.isNull())
        return;

    if (tofile.split('.').last() != "ppt" &&
            tofile.split('.').last() != "pptx") {
        CPromptFrame::prompt(ErrorFormat);
        return;
    }

    QFile::copy(file, tofile);
    ui->lsWare->addItem(tofile);
}

void MainWindow::on_tbSync_clicked()
{
    for (int i = 0; i < ui->lsWare->count(); i++) {
        syncFile(ui->lsWare->item(i)->text());
    }
}

void MainWindow::syncFile(QString filename) {
    qDebug() << "syncing" << filename;
    if (!m_fmg.create(filename))
        return;

    ts_msg msg;
    TS_FILE_PACKET* fmsg = (TS_FILE_PACKET*) &msg;
    while (true) {
        bool finish = m_fmg.generateFileData(*fmsg);
        ProcessMessage(msg, 0, 0, false);
        if (finish)
            return;
    }
}

void MainWindow::on_lsWare_itemDoubleClicked(QListWidgetItem *item)
{
    if (!QFile::exists(item->text()))
        qDebug() << "fuck" << item->text();
    playPPT(item->text());
    ui->gbCourseware->setHidden(true);
    ui->graphicsView->scene()->clear();
}

void MainWindow::on_tbExitWare_clicked()
{
    ui->gbCourseware->setHidden(true);
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    // changeScene(ui->listWidget->getUIDByRow(index.row()));
}

void MainWindow::showPrompt(int result) {
    CPromptFrame::prompt(result);
}
