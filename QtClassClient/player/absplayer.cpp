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
    m_isInnerPvNx(true),
	m_isWaiting(false) {
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
	m_isWaiting = true;
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procRun();
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::close() {
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procClose();
	}
	
	m_filepath = QString::Null();
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::next() {
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procNext();
	}
	
	m_isWaiting = false;
    return false;
}


bool AbsPlayer::prev() {
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procPrev();
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::stop() {
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procStop();
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::start() {
    if (m_isLoadSuccess) {
		m_isWaiting = false;
        return procStart();
	}
	
	m_isWaiting = false;
    return false;
}
