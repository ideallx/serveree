#include <QDebug>
#include "docplayer.h"

DocPlayer::DocPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent) {
    if (!m_controller->setControl("Word.Application"))
        qDebug() << "sfsf";
}

DocPlayer::~DocPlayer() {

}


bool DocPlayer::procRun() { return true; }
bool DocPlayer::procNext() { return true; }
bool DocPlayer::procPrev() { return true; }
bool DocPlayer::procClose() { return true; }
bool DocPlayer::procStop() { return true; }
bool DocPlayer::procStart() { return true; }
