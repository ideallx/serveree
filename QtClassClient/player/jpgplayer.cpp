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

bool JpgPlayer::procRun() {
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

    return true;
}

bool JpgPlayer::procStop() {
    delete m_background;
    return true;
}

bool JpgPlayer::procStart() {

    return true;
}
