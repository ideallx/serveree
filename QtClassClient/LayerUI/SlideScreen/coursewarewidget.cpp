#include <QFileDialog>
#include <QDebug>
#include "coursewarewidget.h"
#include "ui_coursewarewidget.h"
#include "../../BizLogic/datasingleton.h"
#include "../../player/playerfactory.h"
#include "../UserInterface/widgetwarelistitem.h"

QString getFileName(QString filepath) {
    qDebug() << filepath;
    if (filepath.contains('\\')) {
        qDebug() << filepath.split('\\').last();
        return filepath.split('\\').last();
    } else
        return filepath.split('/').last();
}

QString getFilePath(QString filename) {
    QString path = QDir::currentPath();
    return path + "/" + filename;
}

CourseWareWidget::CourseWareWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseWareWidget)
    , m_isPlayerPlaying(false)
    , m_player(NULL)
    , m_userRole(RoleStudent)
    , m_raceTime(0)
    , m_raceOne(NobodyUID) {
    ui->setupUi(this);
    ui->tbSync->setHidden(true);

    m_raceTimer.setSingleShot(true);
    connect(&m_raceTimer, &QTimer::timeout,
            this, &CourseWareWidget::raceTimeOut);
    m_ds = DataSingleton::getInstance();
}

CourseWareWidget::~CourseWareWidget()
{
    delete ui;
    DESTROY(m_player);
}

int CourseWareWidget::checkUploadFile(QString filename) const {
    if (filename.isNull())
        return ErrorFormat;

    if (!PlayerFactory::checkFileFormat(filename)) {
        return ErrorFormat;
    }

    if (ui->lsWare->findItems(filename, Qt::MatchExactly).size() > 0) {
        return ErrorFileExist;
    }

    return Success;
}

int CourseWareWidget::addFileToList(QString filename) {
    QListWidgetItem *item = new QListWidgetItem(filename);
    if (item == 0) {
        return -1;
    }
    ui->lsWare->addItem(item);
    return ui->lsWare->count();
}


void CourseWareWidget::syncFileList() {
    for (int i = 0; i < ui->lsWare->count(); i++) {
        QString filename = ui->lsWare->item(i)->text();
        if (m_syncedWares.contains(filename))
            continue;
        syncFile(filename);
        m_syncedWares.append(filename);
    }
}

void CourseWareWidget::scanLocalCourseware() {
    // qDebug() << QDir::current().entryList();
    foreach (QString filename, QDir::current().entryList()) {
        if (PlayerFactory::checkFileFormat(filename)) {
            addWareItem(filename);
        }
    }
}

void CourseWareWidget::syncFile(QString filename) {
    if (!m_fmg.create(filename))
        return;

    emit promptMsgSent(QString::fromLocal8Bit("正在同步文件：") + filename);

    ts_msg msg;
    TS_FILE_PACKET* fmsg = (TS_FILE_PACKET*) &msg;
    while (true) {
        bool finish = m_fmg.generateFileData(*fmsg);
        m_parent->ProcessMessage(msg, 0, 0, false);
        if (finish)
            return;
    }
}

bool CourseWareWidget::playTest(QString filename) const {
    if (!QFile::exists(filename))
        return false;

    if (!m_isPlayerPlaying && !m_player)
        return true;

//    if (m_player->isMedia()
//            getFileName(m_player->filePath()) == filename)
//        return false;

    return true;
}

int CourseWareWidget::start(QString filename, bool isRemote) {
    if (!m_pg.create(filename))
        return FailedPlay;

    if (isRemote) {
        if (Success == checkUploadFile(filename)) {
            int result = addFileToList(filename);
            if (result >= 0) {
                ui->lbWareCount->setText(QString::number(result));
            }
        }
    }

    bool needNewMedia = true;
    if (m_player) {
		if (getFileName(m_player->filePath()) == filename) {
            if (m_player->isMedia()) {
				needNewMedia = false;
			} else {
				return Success;
			}
		}
	}

    if (needNewMedia) {
        DESTROY(m_player);

        QString filepath = getFilePath(filename);
        m_player = PlayerFactory::createPlayer(filepath, m_parent);
        if (!m_player)
            return FailedPlay;

        connect(m_player, &AbsPlayer::playerEnd,
                this, &CourseWareWidget::playmodeEnd);
        connect(m_player, SIGNAL(backgroundChanged(QPixmap)),
                this, SIGNAL(changeBackground(QPixmap)));
        connect(m_player, &AbsPlayer::playMedia,
                this, &CourseWareWidget::changeMedia);
        connect(m_player, &AbsPlayer::promptSent,
                this, &CourseWareWidget::promptMsgSent);

        emit clearScreen(TeacherUID, CleanShowWare | CleanHideClass | CleanScreen);
    }

    if (!isRemote) {
        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStart);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    }


    if (!m_player || !m_player->run()) {
        return FailedPlay;
    }

    m_isPlayerPlaying = true;
    if (m_player->isTransBackground())
        emit paintModeChanged(PaintPPT);
    else
        emit paintModeChanged(PaintNormal);

    return Success;
}

bool CourseWareWidget::stop(bool isRemote) {
    m_isPlayerPlaying = false;
    if (m_player) {
        if (m_player->isMedia()) {
            m_player->stop();
        } else {
            m_player->close();
        }
    }

    if (!isRemote) {
        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStop);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    }

    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/run.png"));

    if (m_player->isMedia() && !m_player->isMediaEnd()) {
        return true;
    }
    m_player->close();
    setHidden(true);
    emit paintModeChanged(PaintNormal);
    emit clearScreen(TeacherUID, CleanHideClass | CleanHideWare | CleanScreen);
    return true;
}

bool CourseWareWidget::prev(bool isRemote) {
    if (!m_isPlayerPlaying || !m_player)
        return false;

    if (m_player->isInnerNextPrev()) {
        if (!m_player->prev())
            return false;
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return false;
        int curRow = ui->lsWare->row(ui->lsWare->selectedItems()[0]);
		if (ui->lsWare->count() < 2)
			return true;
        for (int i = 1; i < ui->lsWare->count(); i++) {			// 0 is your self~
            int itemid = curRow - i;
            if (itemid < 0) {
                itemid += ui->lsWare->count();
            }
			if (itemid == curRow)								// nothing happen
				return true;

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }
    emit clearScreen(TeacherUID, CleanShowWare | CleanHideClass | CleanScreen);
    if (isRemote)
        return true;

    TS_PLAYER_PACKET pmsg;
    if (m_player->isInnerNextPrev()) {
        m_pg.generatePlayerData(pmsg, ActionPrev);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    } else {
        start(ui->lsWare->selectedItems()[0]->text(), isRemote);
    }
    return true;
}

bool CourseWareWidget::next(bool isRemote) {
    if (!m_isPlayerPlaying || !m_player)
        return false;

    if (m_player->isInnerNextPrev()) {
        if (!m_player->next())
            return false;
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return false;
        int curRow = ui->lsWare->row(ui->lsWare->selectedItems()[0]);
		if (ui->lsWare->count() < 2)
			return true;
        for (int i = 1; i < ui->lsWare->count(); i++) {      // 0 is your self~
            int itemid = curRow + i;
            if (itemid >= ui->lsWare->count()) {
                itemid -= ui->lsWare->count();
            }
			if (itemid == curRow)
				return true;

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }
    emit clearScreen(TeacherUID, CleanShowWare | CleanHideClass | CleanScreen);
    if (isRemote)
        return true;

    TS_PLAYER_PACKET pmsg;
    if (m_player->isInnerNextPrev()) {
        m_pg.generatePlayerData(pmsg, ActionNext);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    } else {
        start(ui->lsWare->selectedItems()[0]->text(), isRemote);
    }
    return true;
}

void CourseWareWidget::on_tbUpload_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    QString filepath = QFileDialog::getOpenFileName(this);
	if (filepath.isNull())
		return;

    QString filename = getFileName(filepath);

    int result = checkUploadFile(filename);		// we have to check it
    qDebug() << "result" << result;
    if (result != Success) {
        emit promptSent(result);
        return;
    }

    if (filepath != getFilePath(filename)) {		// if origin file is not dest file
		if (!QFile::copy(filepath, filename)) {		// cover if exists
			QFile::remove(filename);
			if (!QFile::copy(filepath, filename))
				return;
        }
    }
    addWareItem(filename);

    // TODO ELSE
}

void CourseWareWidget::on_tbSync_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    syncFileList();
}


void CourseWareWidget::on_lsWare_itemDoubleClicked(QListWidgetItem *item) {
    if (m_userRole != RoleTeacher)
        return;
    playFileByUser(item->text());
}

void CourseWareWidget::on_tbExitWare_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    if (m_isPlayerPlaying) {
        stop(false);
    }

    setHidden(true);
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/run.png"));
    emit paintModeChanged(PaintNormal);
    emit clearScreen(TeacherUID, CleanHideClass | CleanHideWare);
    return;
}

void CourseWareWidget::on_tbPrev_clicked()
{
    if (m_userRole != RoleTeacher)
        return;
    if (!prev(false))
        return;
}

void CourseWareWidget::on_tbNext_clicked()
{
    if (m_userRole != RoleTeacher)
        return;
    if (!next(false))
        return;
}


void CourseWareWidget::on_tbStart_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    if (isPlayerPlaying()) {
        stop(false);
        ui->tbStart->setIcon(QIcon(":/icon/ui/icon/run.png"));
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return;
        on_lsWare_itemDoubleClicked(ui->lsWare->selectedItems()[0]);
    }
}

void CourseWareWidget::playFileByUser(QString filename) {
    if (m_isPlayerPlaying && !m_player && getFileName(m_player->filePath()) == filename)
		return;
    //qDebug() << getFileName(m_player->filePath()) << filename << m_isPlayerPlaying;

    if (!playTest(filename)) {
        emit promptSent(FailedPlay);
        return;
    }

    if (Success != start(filename, false)) {
        emit promptSent(FailedPlay);
        return;
    }

    setHidden(false);

    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/s.png"));
}

bool CourseWareWidget::playerStop() {
//    if (!stop(false))
//        return false;
    stop(false);


    return true;
}


void CourseWareWidget::playmodeEnd() {
    // TODO client not end
    playerStop();
}


void CourseWareWidget::addWareItem(QString filename) {
    if (Success != checkUploadFile(filename))
        return;
    int result = addFileToList(filename);
    if (result >= 0) {
        ui->lbWareCount->setText(QString::number(result));
    }
}

void CourseWareWidget::deleteFile(QString filename) {
    auto list = ui->lsWare->findItems(filename, Qt::MatchExactly);
    ui->lsWare->removeItemWidget(list[0]);
    delete list[0];

    qDebug() << filename;
    QFile::remove(filename);
    ui->lbWareCount->setText(QString::number(ui->lsWare->count()));
}

void CourseWareWidget::on_lsWare_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (m_userRole != RoleTeacher) {
        return;
    }

    if (current) {
        WidgetWareListItem* wli = new WidgetWareListItem(current->text());
        ui->lsWare->setItemWidget(current, wli);
        connect(wli, &WidgetWareListItem::runFile,
                this, &CourseWareWidget::playFileByUser);
        connect(wli, &WidgetWareListItem::removeFile,
                this, &CourseWareWidget::deleteFile);
    }

    if (previous)
        ui->lsWare->removeItemWidget(previous);
}


const int MaxAllowedWriteTime = 10000;
void CourseWareWidget::on_tbRace_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    if (m_raceTimer.isActive())
        return;

    m_raceTime = getServerTime() + m_ds->getTimeDiff(); // getClientTime();
    TS_RACE_PACKET rmsg;
    m_rg.generateRaceData(rmsg, RaceInit, MaxAllowedWriteTime, NobodyUID);
    m_parent->ProcessMessage(*(ts_msg*) &rmsg, 0, 0, false);

    m_raceTimer.start(5000);
    emit promptMsgSent(QString::fromLocal8Bit("已发起抢答!"));

}

void CourseWareWidget::raceTimeOut() {
    m_raceTimer.stop();

    TS_RACE_PACKET rmsg;
    m_rg.generateRaceData(rmsg, RaceResult, MaxAllowedWriteTime, m_raceOne);
    m_parent->ProcessMessage(*(ts_msg*) &rmsg, 0, 0, false);

    emit someBodyRaceSuccess(m_raceOne);

    m_raceTime = 0;
    m_raceOne = NobodyUID;
}


void CourseWareWidget::sendRace() {
    TS_RACE_PACKET rmsg;
    m_rg.generateRaceData(rmsg, RaceRace, MaxAllowedWriteTime, m_ds->getUID());
    m_parent->ProcessMessage(*(ts_msg*) &rmsg, 0, 0, false);
    qDebug() << "send Race";
}


void CourseWareWidget::raceBegin(TS_UINT64 teacherUID) {
    if (m_userRole != RoleStudent)
        return;

    emit racePromptSent();
}

void CourseWareWidget::recvRace(TS_UINT64 studentUID, TS_UINT64 time) {
    if (time - m_raceTime < MaxAllowedWriteTime) {
        m_raceOne = studentUID;
        raceTimeOut();
    }
    qDebug() << studentUID << m_raceTime << time;
}

void CourseWareWidget::setRole(enum RoleOfClass role) {
    m_userRole = role;
    scanLocalCourseware();
    if (RoleStudent == role) {
        ui->tbNext->setHidden(true);
        ui->tbPrev->setHidden(true);
        ui->tbStart->setHidden(true);
        ui->tbUpload->setHidden(true);
        ui->tbRace->setHidden(true);
    } else {
        ui->tbNext->setHidden(false);
        ui->tbPrev->setHidden(false);
        ui->tbStart->setHidden(false);
        ui->tbUpload->setHidden(false);
        ui->tbRace->setHidden(false);
    }
}
