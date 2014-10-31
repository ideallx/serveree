#include <QDebug>
#include "pptplayer.h"

PPTPlayer::PPTPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent){
    m_controller->setControl("Powerpoint.Application");
    m_controller->setProperty("Visible", false);

    presentation = m_controller->querySubObject("Presentations");
    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filepath, 1, 0, 0);
    if (!opened) {
        qDebug() << "open error";
        return;
    }
    opened->setProperty("IsFullScreen", false);
    opened->setProperty("ShowType", "ppShowTypeWindow");

    sss = opened->querySubObject("SlideShowSettings");
    if (!sss) {
        qDebug() << "SlideShowSettings error";
        return;
    }
    sss->setProperty("ShowType", 1);

    m_isLoadSuccess = true;
}

bool PPTPlayer::procRun() {
    sss->querySubObject("Run()");
    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        return false;
    }

    auto view = window->querySubObject("View");
    view->querySubObject("GotoSlide(int)", 2);
    view->querySubObject("Previous()");

    int interval = 50;
    window->setProperty("Top", interval);
    window->setProperty("Height", window->property("Height").toInt() - interval);
    return true;
}

bool PPTPlayer::procNext() {
    auto view = window->querySubObject("View");
    if (!view)
        return false;

    auto test = view->querySubObject("Next()");
    if (test) {
        return true;
    }
    return false;
}

bool PPTPlayer::procPrev() {
    auto view = window->querySubObject("View");
    if (!view)
        return false;
    view->querySubObject("Previous()");

    return true;
}

bool PPTPlayer::procClose() {
    qDebug() << "close";
    opened->querySubObject("Close()");
    return true;
}

bool PPTPlayer::procStop() {
    return true;
}

bool PPTPlayer::procStart() {
    return procNext();
}

PPTPlayer::~PPTPlayer() {

}
