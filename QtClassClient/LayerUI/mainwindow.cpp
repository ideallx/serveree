#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "cpromptframe.h"

#include "../UserInterface/widgetwarelistitem.h"
#include "../player/playerfactory.h"
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
    isRunning(false),
    isPlayerPlaying(false),
    m_player(NULL) {
    ui->setupUi(this);

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
            this, &MainWindow::addWareItem);

    connect(this, &MainWindow::playerPreved,
            this, &MainWindow::playerPrev);
    connect(this, &MainWindow::playerStoped,
            this, &MainWindow::playerStop);
    connect(this, &MainWindow::playerNexted,
            this, &MainWindow::playerNext);
    connect(this, &MainWindow::playerStarted,
            this, &MainWindow::playerStart);

    ui->groupBox_2->setHidden(true);
    ui->gbCourseware->setHidden(true);

    connect(ui->tbLogin, &CLoginButton::loginClicked,
            this, &MainWindow::enterClass);
    connect(ui->tbLogin, &CLoginButton::logoutClicked,
            this, &MainWindow::leaveClass);
    connect(ui->tbLogin, &CLoginButton::sendResultPrompt,
            this, &MainWindow::showResultPrompt);
    connect(this, &MainWindow::stopServerRespTimer,
            ui->tbLogin, &CLoginButton::stopTimer);

    sem_msg = CreateSemaphore(NULL, 0, 102400, NULL);

    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);
    showFullScreen();
    // setRole(RoleTeacher);
}

MainWindow::~MainWindow() {
    isRunning = false;
    iop_thread_cancel(pthread_msg);
    delete ui;
    if (m_player) {
        m_player->close();
        delete m_player;
		m_player = 0;
    }
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
void MainWindow::on_tbCourseWare_clicked()
{
    if (isPlayerPlaying)
        return;

    if (m_userRole == RoleTeacher)
        ui->gbCourseware->setHidden(!ui->gbCourseware->isHidden());
}

void MainWindow::on_tbUpload_clicked()
{
	if (m_userRole != RoleTeacher)
		return;

    QString file = QFileDialog::getOpenFileName(this);
    QString tofile = file.split('/').last();
    if (tofile.isNull())
        return;

    if (!PlayerFactory::checkFileFormat(tofile)) {
        CPromptFrame::prompt(ErrorFormat, this);
        return;
    }
    if (ui->lsWare->findItems(tofile, Qt::MatchExactly).size() > 0) {
        CPromptFrame::prompt(ErrorFileExist, this);
        return;
    }

    QFile::copy(file, tofile);
    addWareItem(tofile);
}

void MainWindow::on_tbSync_clicked()
{
	if (m_userRole != RoleTeacher)
		return;
    qDebug() << ui->lsWare->count();
    for (int i = 0; i < ui->lsWare->count(); i++) {
        QString filename = ui->lsWare->item(i)->text();
        if (m_syncedWares.contains(filename))
            continue;
        syncFile(filename);
        m_syncedWares.append(filename);
    }
}

void MainWindow::syncFile(QString filename) {
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
	if (m_userRole != RoleTeacher)
		return;

    if (!QFile::exists(item->text())) {
        qDebug() << "fuck" << item->text();
        return;
    }

    QString str = item->text();
    qDebug() << "play" << str;

    if (!playerPlay(item->text()))
        return;

    TS_PLAYER_PACKET pmsg;
    m_pg.generatePlayerData(pmsg, ActionStart);
    ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
}

void MainWindow::on_tbExitWare_clicked()
{
	if (m_userRole != RoleTeacher)
		return;
    qDebug() << isPlayerPlaying;
    if (isPlayerPlaying) {
        isPlayerPlaying = false;
        if (!stopPlayer())
            return;

        qDebug() << "stop success";
        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStop);
        ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    }
    ui->gbCourseware->setHidden(true);
}

bool MainWindow::playerPlay(QString filepath) {
    if (!playerStart(filepath))
        return false;
    m_pg.create(filepath);
    return true;
}

bool MainWindow::stopPlayer(void) {
    ui->graphicsView->setPaintMode(PaintNormal);
    ui->gbCourseware->setHidden(true);
    ui->graphicsView->scene()->clear();
    isPlayerPlaying = false;
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/start.png"));
    m_player->close();
    return true;
}

void MainWindow::on_tbPrev_clicked()
{
	if (m_userRole != RoleTeacher)
		return;
    if (!playerPrev())
        return;

    TS_PLAYER_PACKET pmsg;
    if (m_player->isInnerNextPrev()) {
        m_pg.generatePlayerData(pmsg, ActionPrev);
        ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    } else {
        on_lsWare_itemDoubleClicked(ui->lsWare->selectedItems()[0]);
    }
}

void MainWindow::on_tbStart_clicked()
{
	if (m_userRole != RoleTeacher)
		return;
    if (isPlayerPlaying) {
        if (!playerStop())
            return;

        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStop);
        ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return;

        on_lsWare_itemDoubleClicked(ui->lsWare->selectedItems()[0]);
    }
}

void MainWindow::itemPlay_clicked(QString filename) {
	if (ui->lsWare->selectedItems().size() == 0)
        return;
	auto selectedItem = ui->lsWare->selectedItems()[0];
	if (m_player) {
        if (m_player->filePath() == filename)
			return;
	}
	
    on_lsWare_itemDoubleClicked(selectedItem);
}

void MainWindow::on_tbNext_clicked()
{
	if (m_userRole != RoleTeacher)
		return;
    if (!playerNext())
        return;

    TS_PLAYER_PACKET pmsg;

    if (m_player->isInnerNextPrev()) {
        m_pg.generatePlayerData(pmsg, ActionNext);
        ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    } else {
		if (ui->lsWare->selectedItems().size() == 0)
			return;

		on_lsWare_itemDoubleClicked(ui->lsWare->selectedItems()[0]);
    }
}

bool MainWindow::playerPrev() {
    if (!isPlayerPlaying)
        return false;

    scene->clear();
    if (m_player->isInnerNextPrev()) {
        if (!m_player->prev())
            return false;
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return false;
        int curRow = ui->lsWare->row(ui->lsWare->selectedItems()[0]);
        for (int i = 1; i <ui->lsWare->count(); i++) {      // 0 is your self~
            int itemid = curRow - i;
            if (itemid < 0) {
                itemid += ui->lsWare->count();
            }

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
//                if (!playerPlay(ui->lsWare->item(itemid)->text())
//                    return false;
//                playerStart(ui->lsWare->item(itemid)->text());
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }

    return true;
}

bool MainWindow::playerNext() {
    if (!isPlayerPlaying || !m_player)
        return false;

    scene->clear();
    if (m_player->isInnerNextPrev()) {
        if (!m_player->next())
            return false;
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return false;
        int curRow = ui->lsWare->row(ui->lsWare->selectedItems()[0]);
        for (int i = 1; i <ui->lsWare->count(); i++) {      // 0 is your self~
            int itemid = i + curRow;
            if (itemid >= ui->lsWare->count()) {
                itemid -= ui->lsWare->count();
            }

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
//                if (!playerPlay(ui->lsWare->item(itemid)->text())
//                    return false;
//                playerStart(ui->lsWare->item(itemid)->text());
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }

    return true;
}

bool MainWindow::playerStart(QString filename) {
    if (m_player) {
		QString filePath = m_player->filePath();
		if (filename == filePath.split('/').last())
			return false;

        m_player->close();
        delete m_player;
		m_player = NULL;
    }

    QString path = QDir::currentPath();
    QString file = path + "/" + filename;
    qDebug() << file;

    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/stop.png"));
    isPlayerPlaying = true;

    m_player = PlayerFactory::createPlayer(file, this);
    connect(m_player, &AbsPlayer::playerEnd,
            this, &MainWindow::playmodeEnd);
    connect(m_player, &AbsPlayer::backgroundChanged,
            this, &MainWindow::changeBackground);
    connect(m_player, &AbsPlayer::playMedia,
            this, &MainWindow::changeMedia);

    ui->graphicsView->scene()->clear();
    if (!m_player || !m_player->run()) {
        sendResultPrompt(FailedPlay);
        isPlayerPlaying = false;
        return false;
    }

    if (m_player->isTransBackground())
        ui->graphicsView->setPaintMode(PaintPPT);

    ui->gbCourseware->setHidden(false);
    if (m_userRole == RoleTeacher)
        ui->groupBox_2->setHidden(true);
    return true;
}

bool MainWindow::playerStop() {
    isPlayerPlaying = false;
    scene->clear();
    ui->graphicsView->setPaintMode(PaintNormal);
    ui->gbCourseware->setHidden(true);
    ui->graphicsView->scene()->clear();
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/start.png"));

    if (!m_player || !m_player->stop())
        return false;

    m_player->close();
	// always delete on create
	//delete m_player;
	//m_player = 0;
    return true;
}


void MainWindow::playmodeEnd() {
    playerStop();
}

void MainWindow::addWareList(QString filename) {
    emit wareItemRecv(filename);
    if (m_userRole != RoleTeacher) {
        ui->gbCourseware->setHidden(true);
    }
}

void MainWindow::addWareItem(QString filename) {
    if (ui->lsWare->findItems(filename, Qt::MatchExactly).size() > 0) {
        return;
    }
    QListWidgetItem *item = new QListWidgetItem(filename);
    ui->lsWare->addItem(item);
    ui->lbWareCount->setText(QString::number(ui->lsWare->count()));
}

void MainWindow::on_lsWare_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (m_userRole != RoleTeacher) {
		ui->gbCourseware->setHidden(true);
        return;
	}

    if (current) {
        WidgetWareListItem* wli = new WidgetWareListItem(current->text());
        ui->lsWare->setItemWidget(current, wli);
        connect(wli, &WidgetWareListItem::runFile,
                this, &MainWindow::itemPlay_clicked);
        connect(wli, &WidgetWareListItem::removeFile,
                this, &MainWindow::deleteFile);
    }

    if (previous)
        ui->lsWare->removeItemWidget(previous);
}

void MainWindow::deleteFile(QString filename) {
    auto list = ui->lsWare->findItems(filename, Qt::MatchExactly);
    ui->lsWare->removeItemWidget(list[0]);
    delete list[0];

    qDebug() << filename;
    QFile::remove(filename);
    ui->lbWareCount->setText(QString::number(ui->lsWare->count()));
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
        emit playerPreved();
        break;
    case ActionNext:
        emit playerNexted();
        break;
    case ActionStop:
        emit playerStoped();
        break;
    default:
        break;
    }
}

void MainWindow::signalPlayerStart(QString filename) {
    emit playerStarted(filename);
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
