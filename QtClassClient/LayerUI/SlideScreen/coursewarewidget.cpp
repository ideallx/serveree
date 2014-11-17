#include <QFileDialog>
#include "coursewarewidget.h"
#include "ui_coursewarewidget.h"
#include "../../player/playerfactory.h"
#include "../UserInterface/widgetwarelistitem.h"

QString getFileName(QString filepath) {
    return filepath.split('/').last();
}


CourseWareWidget::CourseWareWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CourseWareWidget)
    , m_isPlayerPlaying(false)
    , m_player(NULL)
    , m_userRole(RoleStudent) {
    ui->setupUi(this);
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

void CourseWareWidget::syncFile(QString filename) {
    if (!m_fmg.create(filename))
        return;

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

    if (m_isPlayerPlaying && m_player &&
            getFileName(m_player->filePath()) == filename)
        return false;

    return true;
}

int CourseWareWidget::start(QString filename, bool isRemote) {
    if (!m_pg.create(filename))
        return FailedPlay;

    m_player = PlayerFactory::createPlayer(filename, m_parent);
    if (!m_player)
        return FailedPlay;

    if (!isRemote) {
        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStart);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    }


//    connect(m_player, &AbsPlayer::playerEnd,
//            this, &MainWindow::playmodeEnd);
//    connect(m_player, &AbsPlayer::backgroundChanged,
//            this, &MainWindow::changeBackground);
//    connect(m_player, &AbsPlayer::playMedia,
//            this, &MainWindow::changeMedia);

    if (!m_player || !m_player->run()) {
        return FailedPlay;
    }

    m_isPlayerPlaying = true;
    if (m_player->isTransBackground())
        emit paintModeChanged(PaintPPT);

    return true;
}

bool CourseWareWidget::stop(bool isRemote) {
    m_isPlayerPlaying = false;
    if (m_player) {
        m_player->close();
    }

    if (!isRemote) {
        TS_PLAYER_PACKET pmsg;
        m_pg.generatePlayerData(pmsg, ActionStop);
        m_parent->ProcessMessage(*(ts_msg*) &pmsg, 0, 0, false);
    }
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
        for (int i = 1; i <ui->lsWare->count(); i++) {      // 0 is your self~
            int itemid = curRow - i;
            if (itemid < 0) {
                itemid += ui->lsWare->count();
            }

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }
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
        for (int i = 1; i < ui->lsWare->count(); i++) {      // 0 is your self~
            int itemid = curRow + i;
            if (itemid >= ui->lsWare->count()) {
                itemid -= ui->lsWare->count();
            }

            if (m_player->isPostfixRight(ui->lsWare->item(itemid)->text())) {
                ui->lsWare->setCurrentRow(itemid);
                break;
            }
        }
    }
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
    QString filename = getFileName(filepath);

    int result = checkUploadFile(filename);
    if (result != Success) {
        emit promptSent(result);
        return;
    }

    if (QFile::copy(filepath, filename))
        addFileToList(filename);
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

    if (isPlayerPlaying()) {
        stop(false);
    }

    setHidden(true);
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/start.png"));
    emit paintModeChanged(PaintNormal);
    return;
}

void CourseWareWidget::on_tbPrev_clicked()
{
    if (m_userRole != RoleTeacher)
        return;
    if (prev(false))
        return;

    emit clearScreen();
}

void CourseWareWidget::on_tbStart_clicked()
{
    if (m_userRole != RoleTeacher)
        return;

    if (isPlayerPlaying()) {
        stop(false);
        ui->tbStart->setIcon(QIcon(":/icon/ui/icon/start.png"));
    } else {
        if (ui->lsWare->selectedItems().size() == 0)
            return;
        on_lsWare_itemDoubleClicked(ui->lsWare->selectedItems()[0]);
    }
}

void CourseWareWidget::playFileByUser(QString filename) {
    if (!playTest(filename)) {
        emit promptSent(FailedPlay);
        return;
    }

    if (!start(filename, false)) {
        emit promptSent(FailedPlay);
        return;
    }

    setHidden(false);

    emit clearScreen();
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/stop.png"));
}

void CourseWareWidget::on_tbNext_clicked()
{
    if (m_userRole != RoleTeacher)
        return;
    if (!next(false))
        return;

    emit clearScreen();
}


bool CourseWareWidget::playerStop() {
    if (!stop(false))
        return false;


    setHidden(true);
    ui->tbStart->setIcon(QIcon(":/icon/ui/icon/start.png"));
    emit paintModeChanged(PaintNormal);
    return true;
}


void CourseWareWidget::playmodeEnd() {
    playerStop();
}


void CourseWareWidget::addWareItem(QString filename) {
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
        ui->gbCourseware->setHidden(true);
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
