#include <QDebug>
#include "docplayer.h"

DocPlayer::DocPlayer(QString filepath, CMsgObject* parent)
    : AbsPlayer(filepath, parent)
    , opened(NULL) {
    if (!m_controller->setControl("Word.Application"))
        return;
    m_controller->setProperty("Visible", true);
    m_transBackground = true;
    m_isLoadSuccess = true;

    procRun();
}

DocPlayer::~DocPlayer() {
    if (opened)
        opened->querySubObject("Close()");
    m_controller->querySubObject("Quit()");
}

bool DocPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "doc" || postfix == "docx")
        return true;
    return false;
}

bool DocPlayer::procRun() {
    auto documents = m_controller->querySubObject("Documents");
    opened = documents->querySubObject("Open(QString, bool, bool)", m_filepath, true, true);
    if (!opened) {
        emit promptSent(getFileName(m_filepath) + QString::fromLocal8Bit("ÎÄµµ´ò¿ªÊ§°Ü"));
    }
    return true; 
}

bool DocPlayer::procNext() { return true; }
bool DocPlayer::procPrev() { return true; }
bool DocPlayer::procClose() { return true; }
bool DocPlayer::procStop() { return true; }
bool DocPlayer::procStart() { return true; }
