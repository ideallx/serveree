#include <QDebug>
#include "jpgplayer.h"

JpgPlayer::JpgPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent) {
    m_background = new QPixmap(m_filepath);
    if (m_background->isNull())
        return;

    m_isLoadSuccess = true;
    m_isInnerPvNx = false;
}

QPixmap JpgPlayer::pixmapCut(QPixmap& pix) {
    return pix.scaled(m_screenRect.width(), m_screenRect.height(),
               Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

bool JpgPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "jpg" || postfix == "jpeg" || \
            postfix == "png" || postfix == "bmp")
        return true;
    return false;
}

bool JpgPlayer::procRun() {
    emit slideChanged(getFileName(m_filepath));
    emit backgroundChanged(pixmapCut(*m_background));
    return true;
}

bool JpgPlayer::procNext() {
    return true;
}

bool JpgPlayer::procPrev() {
    return true;
}

bool JpgPlayer::procClose() {
    emit backgroundChanged(QPixmap());
    return true;
}

bool JpgPlayer::procStop() {
    emit backgroundChanged(QPixmap());
    delete m_background;
    return true;
}

bool JpgPlayer::procStart() {

    return true;
}
