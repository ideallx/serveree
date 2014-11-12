
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent),
    mediaPlayer(0, QMediaPlayer::VideoSurface) {

    mediaPlayer.setMedia(QUrl::fromLocalFile(filepath));
    m_isLoadSuccess = true;
    m_isInnerPvNx = false;
    return;
}


bool VideoPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "mp4" || postfix == "rmvb" || \
            postfix == "avi" || postfix == "rm" || \
            postfix == "wmv")
        return true;
    return false;
}


bool VideoPlayer::procRun() {
	if (mediaPlayer.isAvailable()) {
        qDebug() << "proc run";
        emit playMedia(&mediaPlayer);
        return true;
    } else {
        return false;
    }
}

bool VideoPlayer::procNext() {
    return true;
}

bool VideoPlayer::procPrev() {
    return true;
}

bool VideoPlayer::procClose() {
    return true;
}

bool VideoPlayer::procStop() {
    return true;
}

bool VideoPlayer::procStart() {
    return true;
}

