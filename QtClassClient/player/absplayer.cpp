#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include "absplayer.h"

#include "pptplayer.h"

AbsPlayer::AbsPlayer(QString filepath, CMsgObject *parent) :
    m_controller(NULL),
    m_parent(parent),
    m_filepath(filepath),

    m_isLoadSuccess(false),
    m_transBackground(false),
    m_isInnerPvNx(true) {
    m_controller = new QAxObject;
    m_fileList.append(filepath);

    QDesktopWidget *dwsktopwidget = QApplication::desktop();
    m_screenRect = dwsktopwidget->screenGeometry();
    m_screenRect.setHeight(m_screenRect.height() - 80);
    m_screenRect.setWidth(m_screenRect.width() - 300);
}

QRect AbsPlayer::screenSize() {
    QDesktopWidget *dwsktopwidget = QApplication::desktop();
    QRect result = dwsktopwidget->screenGeometry();
    result.setHeight(result.height() - 80);
    result.setWidth(result.width() - 300);
    return result;
}

AbsPlayer::~AbsPlayer() {
    if (m_controller)
        delete m_controller;
}

bool AbsPlayer::run() {
    if (m_isLoadSuccess)
        return procRun();

    return false;
}

bool AbsPlayer::close() {
    if (m_isLoadSuccess)
        return procClose();

    return false;
}

bool AbsPlayer::next() {
    if (m_isLoadSuccess)
        return procNext();

    return false;
}


bool AbsPlayer::prev() {
    if (m_isLoadSuccess)
        return procPrev();

    return false;
}

bool AbsPlayer::stop() {
    if (m_isLoadSuccess)
        return procStop();

    return false;
}

bool AbsPlayer::start() {
    if (m_isLoadSuccess)
        return procStart();

    return false;
}
