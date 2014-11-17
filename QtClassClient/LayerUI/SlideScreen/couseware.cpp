#include <QDebug>
#include "couseware.h"
#include "../../player/playerfactory.h"

QString getFileName(QString filepath) {
    return filepath.split('/').last();
}


CourseWareData::CourseWareData(CMsgObject* parent) :
    m_parent(parent),
    m_isPlayerPlaying(false),
    m_player(NULL) {
}

CourseWareData::~CourseWareData() {
    delete m_player;
}

int CourseWareData::checkUploadFile(QString filename) const {
    if (filename.isNull())
        return ErrorFormat;

    if (!PlayerFactory::checkFileFormat(filename)) {
        return ErrorFormat;
    }
    if (m_listWidget->findItems(filename, Qt::MatchExactly).size() > 0) {
        return ErrorFileExist;
    }

    return Success;
}

int CourseWareData::addFileToList(QString filename) {
    QListWidgetItem *item = new QListWidgetItem(filename);
    if (item == 0) {
        return -1;
    }
    m_listWidget->addItem(item);
    return m_listWidget->count();
}


void CourseWareData::syncFileList() {
    for (int i = 0; i < m_listWidget->count(); i++) {
        QString filename = m_listWidget->item(i)->text();
        if (m_syncedWares.contains(filename))
            continue;
        syncFile(filename);
        m_syncedWares.append(filename);
    }
}

void CourseWareData::syncFile(QString filename) {
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

bool CourseWareData::playTest(QString filename) const {
    if (!QFile::exists(filename))
        return false;

    if (m_isPlayerPlaying && m_player &&
            getFileName(m_player->filePath()) == filename)
        return false;

    return true;
}

int CourseWareData::play(QString filename, bool isRemote) {
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
//    if (m_player->isTransBackground())
//        ui->graphicsView->setPaintMode(PaintPPT);

    return true;
}

bool CourseWareData::stop(bool isRemote) {
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

bool CourseWareData::prev(bool isRemote) {
    if (!m_isPlayerPlaying || !m_player)
        return false;

    if (m_player->isInnerNextPrev()) {
        if (!m_player->prev())
            return false;
    } else {
        if (m_listWidget->selectedItems().size() == 0)
            return false;
        int curRow = m_listWidget->row(m_listWidget->selectedItems()[0]);
        for (int i = 1; i <m_listWidget->count(); i++) {      // 0 is your self~
            int itemid = curRow - i;
            if (itemid < 0) {
                itemid += m_listWidget->count();
            }

            if (m_player->isPostfixRight(m_listWidget->item(itemid)->text())) {
                m_listWidget->setCurrentRow(itemid);
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
        play(m_listWidget->selectedItems()[0]->text(), isRemote);
    }
    return true;
}

bool CourseWareData::next(bool isRemote) {
    if (!m_isPlayerPlaying || !m_player)
        return false;

    if (m_player->isInnerNextPrev()) {
        if (!m_player->next())
            return false;
    } else {
        if (m_listWidget->selectedItems().size() == 0)
            return false;
        int curRow = m_listWidget->row(m_listWidget->selectedItems()[0]);
        for (int i = 1; i < m_listWidget->count(); i++) {      // 0 is your self~
            int itemid = curRow + i;
            if (itemid >= m_listWidget->count()) {
                itemid -= m_listWidget->count();
            }

            if (m_player->isPostfixRight(m_listWidget->item(itemid)->text())) {
                m_listWidget->setCurrentRow(itemid);
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
        play(m_listWidget->selectedItems()[0]->text(), isRemote);
    }
    return true;
}
