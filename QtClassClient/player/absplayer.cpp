#include <QDebug>
#include "absplayer.h"

#include "pptplayer.h"

AbsPlayer::AbsPlayer(QString filepath, CMsgObject *parent) :
    m_controller(NULL),
    m_parent(parent),
    m_filepath(filepath),
    m_isLoadSuccess(false) {
    m_controller = new QAxObject;
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
