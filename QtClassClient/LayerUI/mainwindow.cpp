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
#include "../BizLogic/datasingleton.h"

thread_ret_type thread_func_call UIMsgProc(LPVOID lpParam) {
    iop_thread_detach_self();
    MainWindow* m = reinterpret_cast<MainWindow*> (lpParam);
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
    , isRunning(false)
	, isLoading(true) {
    ui->setupUi(this);
    ui->wgtCourse->setHidden(true);
    ui->wgtCourse->setMsgParent(this);
    ui->tbLogin->setHidden(true);

    m_ds = DataSingleton::getInstance();

    scene = new MyScene(SelfUID, ui->graphicsView, this, this);
    sceneMap.insert(SelfUID, scene);
    scene->setWriteable(true);

    scene = new MyScene(CoursewareUID, ui->graphicsView, this, this);
    sceneMap.insert(CoursewareUID, scene);

    scene = new MyScene(TeacherUID, ui->graphicsView, this, this);
    sceneMap.insert(TeacherUID, scene);

    ui->graphicsView->setScene(scene);

    Bridge::connect(this, &questionModule);
    Bridge::connect(this, ui->wgtCourse);

    buildSceneConnection(true);


    // move to UI thread
    connect(this, &MainWindow::enOrLeaveClass,
            this, &MainWindow::classIcon);
    connect(this, &MainWindow::msgReceived,
            this, &MainWindow::msgExcute);
    connect(this, &MainWindow::addScene,
            this, &MainWindow::addSceneSlot);
    connect(this, &MainWindow::promptResultSent,
            this, &MainWindow::showResultPrompt);
    connect(this, &MainWindow::promptSent,
            this, &MainWindow::showPrompt);
    connect(this, &MainWindow::racePromptSent,
            this, &MainWindow::buildRaceDialog);
    connect(this, &MainWindow::wareItemRecv,
            ui->wgtCourse, &CourseWareWidget::recvNewItem);


    ui->gbUserlist->setHidden(true);

    connect(ui->tbLogin, &CLoginButton::loginClicked,
            this, &MainWindow::enterClass);
    connect(ui->tbLogin, &CLoginButton::logoutClicked,
            this, &MainWindow::leaveClass);
    connect(ui->tbLogin, &CLoginButton::sendResultPrompt,
            this, &MainWindow::showResultPrompt);
    connect(this, &MainWindow::stopServerRespTimer,
            ui->tbLogin, &CLoginButton::stopTimer);

    connect(ui->wgtCourse, &CourseWareWidget::changeSide,
            ui->graphicsView, &MyView::moveToSlide);


    sem_msg = CreateSemaphore(NULL, 0, 102400, NULL);

    isRunning = true;
    int rc = iop_thread_create(&pthread_msg, UIMsgProc, (void *) this, 0);
    if (0 == rc) {
        qDebug() << "enter class successfully";
    } else {
        isRunning = false;
    }

    on_tbBackground_clicked();
    on_tbTeacherBoard_clicked();
    ui->listWidget->updateUserInfo();

    l_naviButtons.append(ui->tbCourseWare);
    l_naviButtons.append(ui->tbMyBoard);
    l_naviButtons.append(ui->tbTeacherBoard);

    blankScreen = new QProcess();

#define _DEBUG_UI_

#ifdef _DEBUG_UI_
    setRole(RoleTeacher);
#else
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);
    showFullScreen();
    blankScreen->start("BlankScreen.exe");
#endif
}

MainWindow::~MainWindow() {
    CloseHandle(sem_msg);
    blankScreen->close();
    delete blankScreen;
    leaveClass();
    isRunning = false;
    delete ui;
    sceneMap.clear();
    qDeleteAll(sceneMap);
    iop_thread_cancel(pthread_msg);
}

void MainWindow::ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(event);
    Q_UNUSED(lParam);
    if (!isRunning)
        return;
    if (!isRemote) {
        sendToDown(msg, 0, 0, false);
        if (getType(msg) == GRAPHICS) {
            // hide the userlist to keep resolution
            ui->gbUserlist->setHidden(true);
        }
    } else {
        if (isLoading) {
            TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
            switch (head->type) {
            case GRAPHICS:
                {
                    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
                    if (gmsg->graphicsType == GraphicPacketCls)
                        loadingbuffer.clean();
                }
                break;
            case PLAYERCONTROL:
                {
                    TS_PLAYER_PACKET* pmsg = (TS_PLAYER_PACKET*) &msg;
                    if (pmsg->pa == ActionStart || pmsg->pa == ActionStop)
                        loadingbuffer.clean();
                }
                break;
            case RACE:      // not recv race
            // case QUESTION:  // same as race but now i cant accont all the answer in loading >.<
                return;
            default:
                break;
            }
            loadingbuffer.enQueue(msg);
            return;
        } else {
            // TODO access after destroyed
            msgQueue.enQueue(msg);
            ReleaseSemaphore(sem_msg, 1, NULL);
        }
	}
}

void MainWindow::buildSceneConnection(bool isCreate) {
    if (isCreate) {
        connect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
                this, &MainWindow::setScenePenWidth);
        connect(ui->tbPalette, &ColorCombox::sigColorChanged,
                this, &MainWindow::setScenePenColor);
        connect(ui->tbShape, &CShapeChooser::signalShapeChanged,
                this, &MainWindow::changeSceneShape);
        connect(ui->tbEraser, &QToolButton::clicked,
                scene, &MyScene::revocation);
        connect(ui->graphicsView, &MyView::screenMoved,
                scene, &MyScene::moveScreen);
        connect(scene, &MyScene::changeSide,
                ui->graphicsView, &MyView::moveToSlide);
    } else {
        disconnect(ui->tbBrush, &LineWidthCombox::signalWidthChanged,
                   this, &MainWindow::setScenePenWidth);
        disconnect(ui->tbPalette, &ColorCombox::sigColorChanged,
                   this, &MainWindow::setScenePenColor);
        disconnect(ui->tbShape, &CShapeChooser::signalShapeChanged,
                   this, &MainWindow::changeSceneShape);
        disconnect(ui->tbEraser, &QToolButton::clicked,
                   scene, &MyScene::revocation);
        disconnect(ui->graphicsView, &MyView::screenMoved,
                   scene, &MyScene::moveScreen);
    }
}

void MainWindow::changeBoard(TS_UINT64 sceneID) {
    if (sceneMap[sceneID] == 0 || scene == sceneMap[sceneID])
        return;

    if (sceneID == CoursewareUID)
        on_tbCourseWare_clicked();
    else if (sceneID == TeacherUID)
        on_tbTeacherBoard_clicked();
}

void MainWindow::changeScene(TS_UINT64 sceneID) {
    if (sceneMap[sceneID] == 0)
        return;

    if (scene == sceneMap[sceneID])
        return;

    buildSceneConnection(false);

    scene = sceneMap[sceneID];

    scene->setEraser(false);
    ui->tbEraser->setChecked(false);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->initViewBySceneID(sceneID);

    buildSceneConnection(true);
}

void MainWindow::changeSlide(QString slideInfo) {
    on_tbCourseWare_clicked();
    ui->graphicsView->setNewSlideName(slideInfo);
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
    sendToDown(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::leaveClass() {
    ts_msg msg;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    head->type = LEAVECLASS;
    head->size = sizeof(UP_AGENTSERVICE);
	ui->tbLogin->menu()->close();

    ui->listWidget->clear();

    sendToDown(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::enterClassResult(bool result) {
    if (result) {
        emit enOrLeaveClass(true);
    }
}

void MainWindow::leaveClassResult(bool result) {
    if (result) {
        emit enOrLeaveClass(false);
        ui->listWidget->init();
        qDebug() << "leave class successfully";
    }
}

void MainWindow::classIcon(bool entered) {
    ui->tbLogin->setLoggedIn(entered);
}

void MainWindow::msgProc() {
    while (isRunning) {
        WaitForSingleObject(sem_msg, INFINITE);
        emit msgReceived();
        //qDebug() << "msg recevied";
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
    //sceneMap.remove(uid);
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if (m_userRole != RoleTeacher)
        return;

    if (ui->listWidget->getUIDByRow(index.row()) == m_ds->getUID())
        return;

    bool writeable = ui->listWidget->changeAuth(index.row());

    ts_msg msg;
    // subseq is not needed
    SET_USER_WRITE_AUTH* up = (SET_USER_WRITE_AUTH*) &msg;
    up->head.type = SETWRITEAUTH;
    up->head.size = sizeof(SET_USER_WRITE_AUTH);\

    up->toUID = ui->listWidget->getUIDByRow(index.row());
    up->sceneID = TeacherUID;
    up->writeable = writeable;
    setWriteable(up->toUID, up->sceneID, up->writeable);
    sendToDown(*(ts_msg*) &msg, 0, 0, false);

    // change teacher and courseware rights
    up->sceneID = CoursewareUID;
    setWriteable(up->toUID, up->sceneID, up->writeable);

    sendToDown(*(ts_msg*) &msg, 0, 0, false);
}

void MainWindow::on_tbMyClass_clicked()
{
    ui->gbUserlist->setHidden(!ui->gbUserlist->isHidden());
}

void MainWindow::on_btClassInfo_clicked()
{
    ui->gbUserlist->setHidden(true);
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    // TODO
    changeScene(ui->listWidget->getUIDByRow(index.row()));
}

void MainWindow::setWriteable(TS_UINT64 toUID, DWORD sceneID, WORD writeable) {
    ui->listWidget->changeAuth(toUID, writeable);

    if (toUID != m_ds->getUID())
        return;

    if (sceneID == m_ds->getUID()) {
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
void MainWindow::changeModule(TS_UINT64 sceneid) {
    if (CoursewareUID == sceneid) {
        on_tbCourseWare_clicked();
    } else if (TeacherUID == sceneid) {
        on_tbTeacherBoard_clicked();
    } else if (SelfUID == sceneid) {
        on_tbMyBoard_clicked();
    }

}

void MainWindow::setScenePenWidth(int width) {
    scene->setPenWidth(width);
    ui->tbEraser->setChecked(false);
}

void MainWindow::setScenePenColor(QColor color) {
    scene->setPenColor(color);
    ui->tbEraser->setChecked(false);
}

void MainWindow::changeSceneShape(int shapeType) {
    scene->changeShapeByUI(shapeType);
    ui->tbEraser->setChecked(false);
}


void MainWindow::addSceneSlot(int uidh, int uidl) {
    Q_UNUSED(uidh);
    // TODO
    TS_UINT64 uid = uidl;
	if (sceneMap.find(uid) == sceneMap.end()) {
        MyScene *s = new MyScene(uid, ui->graphicsView, this, this);
		sceneMap.insert(uid, s);
	}
}

void MainWindow::msgExcute() {
    ts_msg msg;
    if (msgQueue.deQueue(msg) == false) {
        return;
    }

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    switch (head->type) {
    case GRAPHICS:
        {
            // hide the userlist to keep resolution
            ui->gbUserlist->setHidden(true);
            TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
            MyScene* theScene = sceneMap[gmsg->SceneID];	// TODO waste time here
            if (theScene == NULL) {
                theScene = new MyScene(gmsg->SceneID, ui->graphicsView, this, this);
                sceneMap.insert(gmsg->SceneID, theScene);
            }

            if (m_ds->getSelfRole() == RoleStudent) {
                if (gmsg->SceneID == TeacherUID || gmsg->SceneID == CoursewareUID) {
                    changeBoard(gmsg->SceneID);
                }
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
                theScene->cls();
                theScene->update();
                break;
            case GraphicPacketMoveScreen:
            {
                theScene->actMoveScreen(*gmsg);
//                int x = gmsg->data.PointX;
//                int y = gmsg->data.PointY;
//                ui->graphicsView->moveScreen(QPoint(x, y));
                break;
            }
            default:
                break;
            }
        }
        break;
    case ENTERCLASS:
    case LEAVECLASS:
        {
            DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;
            switch (down->result) {
            case SuccessEnterClass:
                enterClassResult(true);
                setRole(down->role);
                break;
            case SuccessLeaveClass:
                leaveClassResult(true);
            }
            recvClassInfo();
            emit promptResultSent(down->result);
        }
        break;
    case ADDUSER:
    case USERLIST:
    case REMOVEUSER:
        ui->listWidget->updateUserInfo();
        break;
    case COURSEWARE:
        {
            TS_FILE_PACKET* fmsg = (TS_FILE_PACKET*) &msg;
            QString filename = QString::fromLocal8Bit(reinterpret_cast<char*> (fmsg->content));
            addWareList(filename);
            sendPrompt(QString::fromLocal8Bit("课件:") + filename + QString::fromLocal8Bit("下载成功"));
            changeBoard(CoursewareUID);
        }
		break;
	case PLAYERCONTROL:
		{
            TS_PLAYER_PACKET* pmsg = (TS_PLAYER_PACKET*) &msg;
            signalPlayerMove(QString::fromLocal8Bit(reinterpret_cast<char*> (pmsg->filename)),
                             pmsg->pa);
            on_tbCourseWare_clicked();
		}
        break;
	case SETWRITEAUTH:
		{
            ui->listWidget->updateUserInfo();
            SET_USER_WRITE_AUTH* down = (SET_USER_WRITE_AUTH*) &msg;
            setWriteable(down->toUID, down->sceneID, down->writeable);
		}
        break;
    case RACE:
        {
            TS_RACE_PACKET* rmsg = (TS_RACE_PACKET*) &msg;
            if (RaceInit == rmsg->raceType)
                raceBegin(rmsg->teacherUID);
            else if (RaceRace == rmsg->raceType)
                raceRun(rmsg->studentUID, rmsg->head.time);
            else if (RaceResult == rmsg->raceType)
                raceResult(rmsg->teacherUID, rmsg->studentUID, rmsg->writingTime);
        }
        break;
    case QUESTION:
        questionModule.process(*reinterpret_cast<TS_QUESTION_PACKET*> (&msg));
        break;
    default:
        break;
    }
}

void MainWindow::cleanCentralArea(TS_UINT64 sceneID, int cleanOption) {
    MyScene* theScene = sceneMap[sceneID];
    if (theScene == NULL) {
        return;
    }

    if (CleanShowWare & cleanOption) {
        if (RoleTeacher == m_userRole)
            ui->wgtCourse->setHidden(false);
    }
    if (CleanHideWare & cleanOption) {
        ui->wgtCourse->setHidden(true);
    }
    if (CleanShowClass & cleanOption) {
        ui->gbUserlist->setHidden(false);
    }
    if (CleanHideClass & cleanOption) {
        ui->gbUserlist->setHidden(true);
    }
    if (CleanScreen & cleanOption) {
        theScene->cls();
    }
    if (CleanCourse & cleanOption) {
        if (sceneID == CoursewareUID) {
            scene->cleanFirstPage();
        }
    }
}

void MainWindow::setViewPaintMode(int mode) {
    ui->graphicsView->setPaintMode(mode);
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
    auto pDialog = CPromptFrame::prompt(result, PromptControllerConfirm, this);
    pDialog->exec();
}

void MainWindow::showPrompt(QString prompt) {
    auto pDialog = CPromptFrame::prompt(prompt, PromptControllerConfirm, this);
    pDialog->exec();
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
    foreach (QToolButton* tb, l_naviButtons) {
        tb->setChecked(false);
    }
    ui->tbCourseWare->setChecked(true);

    changeScene(CoursewareUID);
    ui->wgtCourse->setHidden(false);
    //if (ui->wgtCourse->isPlayerPlaying())
    //    return;

    // if (m_userRole == RoleTeacher)
}


void MainWindow::changeBackground(QPixmap newPix) {
    static_cast<MyScene*> (ui->graphicsView->scene())->setBackground(newPix);
}

void MainWindow::changeMedia(QMediaPlayer *player) {
    static_cast<MyScene*> (ui->graphicsView->scene())->playMedia(player);
}


void MainWindow::signalPlayerMove(QString filename, WORD move) {
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
	case ActionStart:
		emit playerStarted(filename, true);
    default:
        break;
    }
}

// 5 teacher ware

// 6 others
void MainWindow::debuginfo(QString str) {

}

void MainWindow::setRole(enum RoleOfClass role) {
    m_userRole = role;
    ui->wgtCourse->setRole(role);
    if (role == RoleTeacher) {
        sceneMap[TeacherUID]->setWriteable(true);
        sceneMap[CoursewareUID]->setWriteable(true);
        ui->tbQuestion->setVisible(true);
    } else {
        sceneMap[TeacherUID]->setWriteable(false);
        sceneMap[CoursewareUID]->setWriteable(false);
        ui->tbQuestion->setVisible(false);
    }
}

void MainWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QPainter p(this);
    p.fillRect(this->rect(), QColor(0, 0, 0, 2));   // alpha = 2 transparent
}


void MainWindow::on_tbTeacherBoard_clicked()
{
    foreach(QToolButton* tb, l_naviButtons) {
        tb->setChecked(false);
    }
    ui->tbTeacherBoard->setChecked(true);

    ui->gbUserlist->setHidden(true);
    ui->wgtCourse->setHidden(true);
    changeScene(TeacherUID);
}

void MainWindow::on_tbMyBoard_clicked()
{
    foreach(QToolButton* tb, l_naviButtons) {
        tb->setChecked(false);
    }
    ui->tbMyBoard->setChecked(true);

    ui->gbUserlist->setHidden(true);
    ui->wgtCourse->setHidden(true);
    changeScene(SelfUID);
}

static int backStyle = 1;
void MainWindow::on_tbBackground_clicked()
{
    backStyle++;
    if (backStyle == 2)
        backStyle = 0;

    if (0 == backStyle) {
        QFile qss(":/stylesheets/GreenMainwindow.qss");
        qss.open(QFile::ReadOnly);
        ui->centralWidget->setStyleSheet(qss.readAll());
        qss.close();

        QFile qss2(":/stylesheets/GreenGroupIcon.qss");
        qss2.open(QFile::ReadOnly);
        ui->gbCommandbar->setStyleSheet(qss2.readAll());
        qss2.close();

        QFile qss3(":/stylesheets/GreenCourseWare.qss");
        qss3.open(QFile::ReadOnly);
        ui->wgtCourse->setStyleSheet(qss3.readAll());
        qss3.close();
    } else {
        QFile qss(":/stylesheets/OrangeMainwindow.qss");
        qss.open(QFile::ReadOnly);
        ui->centralWidget->setStyleSheet(qss.readAll());
        qss.close();

        QFile qss2(":/stylesheets/OrangeGroupIcon.qss");
        qss2.open(QFile::ReadOnly);
        ui->gbCommandbar->setStyleSheet(qss2.readAll());
        qss2.close();

        QFile qss3(":/stylesheets/OrangeCourseWare.qss");
        qss3.open(QFile::ReadOnly);
        ui->wgtCourse->setStyleSheet(qss3.readAll());
        qss3.close();
    }
}
// 6 others

// 7 race
void MainWindow::raceBegin(TS_UINT64 teacherUID) {
    teacherUID = 0;     // unused ><
    if (m_userRole != RoleStudent)
        return;

    emit racePromptSent();
}

void MainWindow::raceRun(TS_UINT64 studentUID, TS_UINT64 time) {
    if (m_userRole != RoleTeacher)
        return;

    ui->wgtCourse->recvRace(studentUID, time);
    qDebug() << "race student uid is" << studentUID;
}

void MainWindow::raceResult(TS_UINT64 teacherUID, TS_UINT64 studentUID, WORD writingTime) {
    writingTime = 0;    // unused
    teacherUID = 0;     // unused
    qDebug() << "race result";
    if (studentUID == m_ds->getUID()) {
        sceneMap[TeacherUID]->setWriteable(true);
        sceneMap[CoursewareUID]->setWriteable(true);
    }

    ui->listWidget->changeAuth(studentUID, true);
    raceSuccessPrompt(studentUID);
}

void MainWindow::buildRaceDialog() {
    auto pDialog = CPromptFrame::racePrompt(this);
    connect(pDialog, &QDialog::accepted,
            this, &MainWindow::studentRaced);
    pDialog->exec();
}

void MainWindow::studentRaced() {
    ui->wgtCourse->sendRace();
}

void MainWindow::raceSuccessPrompt(TS_UINT64 uid) {
    QString prompt;
    if (NobodyUID == uid) {
        prompt = QString::fromLocal8Bit("无人抢答。。。");
    } else if (uid == m_ds->getUID()) {
        prompt = QString::fromLocal8Bit("您抢答成功！！");
    } else {
        QString stu = ui->listWidget->getUserName(uid);     // TODO ds
        if (stu.isNull()) {
            stu = QString::fromLocal8Bit("有人");
        }
        prompt = stu + QString::fromLocal8Bit("抢答成功");
    }
    emit promptSent(prompt);
}
// 7 race

// 8 question
void MainWindow::buildQuestion(WORD format, WORD correctAnswer) {
    QDialog* d = CPromptFrame::answerDialog(format, correctAnswer, this);
    int userAnswer = d->exec();
    TS_QUESTION_PACKET qmsg;
    questionGenerator.generateQuestionData(qmsg, QuestionAnswer,
                                           format, userAnswer);
    ProcessMessage(*reinterpret_cast<ts_msg*> (&qmsg), 0, 0, false);
    questionModule.process(qmsg);
}

void MainWindow::buildQuestionStatistics(ScoreTable st) {
    return;
}

void MainWindow::loadComplete() {
	isLoading = false;
	ts_msg msg;
    qDebug() << "load complete";
	while (!loadingbuffer.isEmpty()) {
		if (!loadingbuffer.deQueue(msg))
            continue;
		ProcessMessage(msg, 0, 0, true);
    }
    setRole(static_cast<enum RoleOfClass> (m_ds->getSelfRole()));
}


void Bridge::connect(MainWindow* mw, CQuestionModule* qm) {
    QObject::connect(qm, &CQuestionModule::questionSented,
                     mw, &MainWindow::buildQuestion);
}

void Bridge::connect(MainWindow* mw, CourseWareWidget* cww) {
    QObject::connect(mw, &MainWindow::playerPreved,
                     cww, &CourseWareWidget::prev);
    QObject::connect(mw, &MainWindow::playerStoped,
                     cww, &CourseWareWidget::stop);
    QObject::connect(mw, &MainWindow::playerNexted,
                     cww, &CourseWareWidget::next);
    QObject::connect(mw, &MainWindow::playerStarted,
                     cww, &CourseWareWidget::start);

    QObject::connect(cww, &CourseWareWidget::clearScreen,
                     mw, &MainWindow::cleanCentralArea);
    QObject::connect(cww, &CourseWareWidget::paintModeChanged,
                     mw, &MainWindow::setViewPaintMode);
    QObject::connect(cww, &CourseWareWidget::promptSent,
                     mw, &MainWindow::showResultPrompt);
    QObject::connect(cww, &CourseWareWidget::changeBackground,
                     mw, &MainWindow::changeBackground);
    QObject::connect(cww, &CourseWareWidget::changeMedia,
                     mw, &MainWindow::changeMedia);
    QObject::connect(cww, &CourseWareWidget::promptMsgSent,
                     mw, &MainWindow::showPrompt);
    QObject::connect(cww, &CourseWareWidget::someBodyRaceSuccess,
                     mw, &MainWindow::raceSuccessPrompt);
    QObject::connect(cww, &CourseWareWidget::askChangeScene,
                     mw, &MainWindow::changeBoard);
    QObject::connect(cww, &CourseWareWidget::slideChanged,
                     mw, &MainWindow::changeSlide);
}

void MainWindow::on_tbQuestion_clicked()
{
    if (RoleTeacher != m_userRole)
        return;

    QDialog* d = CPromptFrame::questionDialog(this);
    int answer = d->exec();
    int format = -1;
    if (answer == ChoiceStatistics) {       // choose statistics
        format = ChoiceStatistics;
    } else if (answer > ChoiceBoolWall) {   // choose bool question
        format = QuestionBool;
    } else if (answer > 0) {                // choose choice question
        format = QuestionChoice;
    } else if (answer == ChoiceUnset) {     // choose exit
        return;
    }

    if (-1 == format) {
        return;
    } else if (format == ChoiceStatistics) {             // build statistics
        ScoreTable st = questionModule.getScoreTable();
        QDialog* d = CPromptFrame::statisticsDialog(st, this);
        d->exec();
    } else {
        TS_QUESTION_PACKET qmsg;
        questionGenerator.init();
        questionGenerator.generateQuestionData(qmsg, QuestionInit, format, answer);
        ProcessMessage(*reinterpret_cast<ts_msg*> (&qmsg), 0, 0, false);
        questionModule.process(qmsg);
    }
}

#include <qscrollbar.h>
void MainWindow::show() {
    QMainWindow::show();
    ui->graphicsView->horizontalScrollBar()->setValue(0);
}
