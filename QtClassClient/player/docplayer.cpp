#include <QDebug>
#include "docplayer.h"

DocPlayer::DocPlayer(QByteArray filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent) {
    if (!m_controller->setControl("Word.Application"))
        qDebug() << "sfsf";
}

DocPlayer::~DocPlayer() {

}

bool DocPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "doc")
        return true;
    return false;
}

bool DocPlayer::procRun() { return true; }
bool DocPlayer::procNext() { return true; }
bool DocPlayer::procPrev() { return true; }
bool DocPlayer::procClose() { return true; }
bool DocPlayer::procStop() { return true; }
bool DocPlayer::procStart() { return true; }
