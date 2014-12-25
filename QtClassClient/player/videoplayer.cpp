
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent),
    mediaPlayer(0, QMediaPlayer::VideoSurface) {

    mediaPlayer.setMedia(QUrl::fromLocalFile(filepath));
    m_isLoadSuccess = true;
    m_isInnerPvNx = true;
    m_isMedia = true;
    step = 5000;
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
    if (mediaPlayer.state() == QMediaPlayer::PausedState) {
        mediaPlayer.play();
        return true;
    }

    m_isMediaEnd = false;
	if (mediaPlayer.isAvailable()) {
        qDebug() << "proc run";
        connect(&mediaPlayer, &QMediaPlayer::stateChanged,
                this, &VideoPlayer::checkStatus);
        emit playMedia(&mediaPlayer);
        return true;
    } else {
        return false;
    }
}

void VideoPlayer::checkStatus(QMediaPlayer::State status) {
    if (status == QMediaPlayer::StoppedState) {
        m_isMediaEnd = true;
        emit playerEnd();
    }
}

bool VideoPlayer::procNext() {
    mediaPlayer.setPosition(mediaPlayer.position() + step);
    if (mediaPlayer.position() >= mediaPlayer.duration()) {
        m_isMediaEnd = true;
        emit playerEnd();
    }
    return true;
}

bool VideoPlayer::procPrev() {
    qint64 pos = mediaPlayer.position() - step;
    if (pos < 0) pos = 1;
    mediaPlayer.setPosition(pos);
    return true;
}

bool VideoPlayer::procClose() {
    m_isMediaEnd = true;
    return true;
}

bool VideoPlayer::procStop() {
    mediaPlayer.pause();
    return true;
}

bool VideoPlayer::procStart() {
    return procRun();
}

