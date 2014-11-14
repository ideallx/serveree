#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include "absplayer.h"

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
        if (procRun()) {
            return true;
        } else {
            m_filepath = QString::Null();
            return false;
        }
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::close() {
    m_isWaiting = false;
    if (m_isLoadSuccess) {
        if (procClose()) {
            m_filepath = QString::Null();
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool AbsPlayer::next() {
    if (m_isLoadSuccess) {
        m_isWaiting = false;
        if (procNext()) {
            return true;
        } else {
            m_filepath = QString::Null();
            return false;
        }
	}
	
	m_isWaiting = false;
    return false;
}


bool AbsPlayer::prev() {
    if (m_isLoadSuccess) {
        m_isWaiting = false;
        if (procPrev()) {
            return true;
        } else {
            m_filepath = QString::Null();
            return false;
        }
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::stop() {
    if (m_isLoadSuccess) {
        m_isWaiting = false;
        if (procStop()) {
            return true;
        } else {
            m_filepath = QString::Null();
            return false;
        }
	}
	
	m_isWaiting = false;
    return false;
}

bool AbsPlayer::start() {
    if (m_isLoadSuccess) {
        if (procStart()) {
            return true;
        } else {
            m_filepath = QString::Null();
            return false;
        }
	}
	
	m_isWaiting = false;
    return false;
}
