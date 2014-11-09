#include <QDebug>
#include "pptplayer.h"

PPTPlayer::PPTPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent),
    totalSlide(0),
    curSlide(1) {
    if (!m_controller->setControl("Powerpoint.Application"))
        return;
    m_controller->setProperty("Visible", false);

    presentation = m_controller->querySubObject("Presentations");
    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filepath, true, false, true);
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

    m_transBackground = true;
    m_isLoadSuccess = true;
}

bool PPTPlayer::procRun() {
    sss->querySubObject("Run()");
    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        return false;
    }

    auto presentation = window->querySubObject("Presentation");
    auto Slides = presentation->querySubObject("Slides");
    bool ok;
    totalSlide = Slides->dynamicCall("Count").toInt(&ok);
    if (!ok) {
        return false;
    }
    curSlide = 1;
    window->setProperty("Top", 50);
    window->setProperty("Left", 200);
    window->setProperty("Width", window->property("Width").toInt() - 200);
    //window->setProperty("Height", window->property("Height").toInt() - 50);
    return true;
}

bool PPTPlayer::procNext() {
    auto view = window->querySubObject("View");
    if (!view)
        return false;

    view->querySubObject("Next()");
    if (curSlide > totalSlide) {
        emit playerEnd();
        return close();
    }
    qDebug() << curSlide << totalSlide;
    curSlide++;
    return true;
}

bool PPTPlayer::procPrev() {
    auto view = window->querySubObject("View");
    if (!view)
        return false;
    if (curSlide > 1) {
        curSlide--;
    }
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
    return procRun();
}

PPTPlayer::~PPTPlayer() {

}
