#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <iop_util.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DrawingScreen/myscene.h"
#include "cpromptframe.h"

#include "../player/playerfactory.h"
#include "UserInterface/cpromptframe.h"


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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_userRole(RoleStudent)
    , ui(new Ui::MainWindow)
    , isRunning(false) {
    ui->setupUi(this);
    ui->wgtCourse->setHidden(true);

    scene = new MyScene(SelfUID, this, this);
    sceneMap.insert(SelfUID, scene);
    scene->setWriteable(true);
    scene = new MyScene(TeacherUID, this, this);
    sceneMap.insert(TeacherUID, scene);

    ui->graphicsView->setScene(scene);

    connect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
            this, &MainWindow::setPenWidth);
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
    connect(this, &MainWindow::promptResultSent,
            this, &MainWindow::showResultPrompt);
    connect(this, &MainWindow::promptSent,
            this, &MainWindow::showPrompt);
    connect(this, &MainWindow::wareItemRecv,
            ui->wgtCourse, &CourseWareWidget::addWareItem);

    connect(this, &MainWindow::playerPreved,
            ui->wgtCourse, &CourseWareWidget::prev);
    connect(this, &MainWindow::playerStoped,
            ui->wgtCourse, &CourseWareWidget::stop);
    connect(this, &MainWindow::playerNexted,
            ui->wgtCourse, &CourseWareWidget::next);
    connect(this, &MainWindow::playerStarted,
            ui->wgtCourse, &CourseWareWidget::start);

    ui->groupBox_2->setHidden(true);

    connect(ui->tbLogin, &CLoginButton::loginClicked,
            this, &MainWindow::enterClass);
    connect(ui->tbLogin, &CLoginButton::logoutClicked,
            this, &MainWindow::leaveClass);
    connect(ui->tbLogin, &CLoginButton::sendResultPrompt,
            this, &MainWindow::showResultPrompt);
    connect(this, &MainWindow::stopServerRespTimer,
            ui->tbLogin, &CLoginButton::stopTimer);

    sem_msg = CreateSemaphore(NULL, 0, 102400, NULL);


#define _DEBUG_UI_
#ifdef _DEBUG_UI_
    setRole(RoleTeacher);
#else
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);
    showFullScreen();
#endif
}

MainWindow::~MainWindow() {
    isRunning = false;
    iop_thread_cancel(pthread_msg);
    CloseHandle(sem_msg);
    qDeleteAll(sceneMap);
    sceneMap.clear();
    delete ui;
}

void MainWindow::ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(event);
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
               this, &MainWindow::setPenWidth);
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
            this, &MainWindow::setPenWidth);
    connect(ui->tbPalette, &ColorCombox::sigColorChanged,
            scene, &MyScene::setPenColor);
    connect(ui->tbShape, &CShapeChooser::signalShapeChanged,
            scene, &MyScene::changeShapeByUI);
    connect(ui->tbEraser, &QToolButton::clicked,
            scene, &MyScene::revocation);
    connect(ui->graphicsView, &MyView::screenMoved,
            scene, &MyScene::moveScreen);
}

// 1 msg trans
void MainWindow::enterClass(QString username, QString password) {
    ts_msg msg;

    UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
    up->head.type = ENTERCLASS;
    up->head.size = sizeof(UP_AGENTSERVICE);
	memcpy(up->username, username.toLocal8Bit().data(), 20);
    memcpy(up->password, password.toLocal8Bit().data(), 20);

    ui->tbLogin->menu()->setHidden(true);

    ui->tbLogin->setAccount(username, password);

    qDebug() << "login" << username;
    sendToAll(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::leaveClass() {
    ts_msg msg;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    head->type = LEAVECLASS;
    head->size = sizeof(UP_AGENTSERVICE);
	ui->tbLogin->menu()->close();

    ui->listWidget->clear();

    sendToAll(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::enterClassResult(bool result) {
    if (result) {
        emit enOrLeaveClass(true);

        isRunning = true;
        iop_usleep(10);

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
        ui->listWidget->init();
        qDebug() << "leave class successfully";
    }
}

void MainWindow::classIcon(bool entered) {
    ui->tbLogin->setLoggedIn(entered);
}

void MainWindow::msgProc() {
    while (isRunning) {
        WaitForSingleObject(sem_msg, 30);
        emit drawShape();
    }
}

// 1 msg trans

// 2 my class
void MainWindow::addUser(TS_UINT64 uid, QString username, bool isOnline) {
    ui->listWidget->addUser(uid, username, isOnline);
    emit addScene(uid >> 32, uid);
}

void MainWindow::removeUser(TS_UINT64 uid) {
    ui->listWidget->removeUser(uid);
    sceneMap.remove(uid);
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if (m_userRole != RoleTeacher)
        return;

    bool writeable = ui->listWidget->changeAuth(index.row());

    ts_msg msg;
    SET_USER_WRITE_AUTH* up = (SET_USER_WRITE_AUTH*) &msg;
    up->head.type = SETWRITEAUTH;
    up->head.size = sizeof(SET_USER_WRITE_AUTH);
    up->head.sequence = 0;

    up->toUID = ui->listWidget->getUIDByRow(index.row());
    up->sceneID = TeacherUID;
    up->writeable = writeable;

    setWriteable(up->toUID, up->sceneID, up->writeable);

    sendToAll(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::on_tbMyClass_clicked()
{
    ui->groupBox_2->setHidden(!ui->groupBox_2->isHidden());
}

void MainWindow::on_btClassInfo_clicked()
{
    ui->groupBox_2->setHidden(true);
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    // TODO
    // changeScene(ui->listWidget->getUIDByRow(index.row()));
}

void MainWindow::setWriteable(TS_UINT64 toUID, DWORD sceneID, WORD writeable) {
    ui->listWidget->changeAuth(toUID, writeable);

    if (toUID != globalUID)
        return;

    if (sceneID == globalUID) {
        if (!sceneMap[SelfUID])
            return;
        sceneMap[SelfUID]->setWriteable(writeable);
    } else {
        if (!sceneMap[sceneID])
            return;
        sceneMap[sceneID]->setWriteable(writeable);
    }
}
// 2 my class

// 3 my scene
void MainWindow::setPenWidth(int width) {
    scene->setPenWidth(width);
    ui->tbEraser->setChecked(false);
}

void MainWindow::addSceneSlot(int uidh, int uidl) {
    Q_UNUSED(uidh);
    // TODO
    TS_UINT64 uid = uidl;
	if (sceneMap.find(uid) == sceneMap.end()) {
		MyScene *s = new MyScene(uid, this, this);
		sceneMap.insert(uid, s);
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
// 3 my scene

// 4 prompt
void MainWindow::sendResultPrompt(int result) {
    emit promptResultSent(result);
}

void MainWindow::sendPrompt(QString prompt) {
    emit promptSent(prompt);
}

void MainWindow::showResultPrompt(int result) {
    CPromptFrame::prompt(result, this);
}

void MainWindow::showPrompt(QString prompt) {
    CPromptFrame::prompt(prompt, this);
}

void MainWindow::recvClassInfo() {
    emit stopServerRespTimer();
}

// 4 prompt

// 5 teacher ware


void MainWindow::addWareList(QString filename) {
    emit wareItemRecv(filename);
}


void MainWindow::on_tbCourseWare_clicked()
{
    if (ui->wgtCourse->isPlayerPlaying())
        return;

    if (m_userRole == RoleTeacher)
        ui->wgtCourse->setHidden(!ui->wgtCourse->isHidden());
}


void MainWindow::changeBackground(QPixmap newPix) {
    static_cast<MyScene*> (ui->graphicsView->scene())->setBackground(newPix);
}

void MainWindow::changeMedia(QMediaPlayer *player) {
    static_cast<MyScene*> (ui->graphicsView->scene())->playMedia(player);
}


void MainWindow::signalPlayerMove(WORD move) {
    switch (move) {
    case ActionPrev:
        emit playerPreved(true);
        break;
    case ActionNext:
        emit playerNexted(true);
        break;
    case ActionStop:
        emit playerStoped(true);
        break;
    default:
        break;
    }
}


void MainWindow::signalPlayerStart(QString filename) {
    emit playerStarted(filename, true);
}

// 5 teacher ware

// 6 others
void MainWindow::debuginfo(QString str) {

}

void MainWindow::setRole(enum RoleOfClass role) {
    m_userRole = role;
    if (role == RoleTeacher) {
        sceneMap[TeacherUID]->setWriteable(true);
    }
}

void MainWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QPainter p(this);
    p.fillRect(this->rect(), QColor(0, 0, 0, 2));   // alpha = 2 transparent
}


void MainWindow::on_tbTeacherBoard_clicked()
{
    changeScene(TeacherUID);
}

void MainWindow::on_tbMyBoard_clicked()
{
    changeScene(SelfUID);
}

void MainWindow::on_tbBackground_clicked()
{
    CPromptFrame::prompt(PleaseWaiting, this);
}

// 6 others
