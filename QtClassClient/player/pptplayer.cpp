#include <QDebug>
#include <QDir>
#include "pptplayer.h"

PPTPlayer::PPTPlayer(QString filepath, CMsgObject* parent):
    AbsPlayer(filepath, parent) {
    if (!m_controller->setControl("Powerpoint.Application"))
        return;
    m_controller->setProperty("Visible", false);

    presentation = m_controller->querySubObject("Presentations");
    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", filepath, false, false, false);
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

    m_transBackground = true;
    m_isLoadSuccess = true;
}
	

PPTPlayer::~PPTPlayer() {
    opened->querySubObject("Close()");
}


bool PPTPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "ppt")
        return true;
    return false;
}

bool PPTPlayer::procRun() {
    sss->querySubObject("Run()");
    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        qDebug() << "ddfsas";
        return false;
    }

    window->setProperty("Top", 40);
    window->setProperty("Left", 180);
    window->setProperty("Width", window->property("Width").toInt() - 180);
    window->setProperty("Height", window->property("Height").toInt() - 40);

    auto slides = window->querySubObject("Presentation");
    slides = slides->querySubObject("Slides(int)", 1);
    if (!slides) {
        return false;
    }

//    QString fp = m_filepath + ".jpg";
//    qDebug() << fp;
//    slides->querySubObject("Export(QString, QString, int, int)", fp, "jpg", 1920, 1080);
//    if (!slides) {
//        return false;
//    }

//    qDebug() << "ppt pixmap";
//    QPixmap p(fp);
//    emit backgroundChanged(p);

    return true;
}

bool PPTPlayer::procNext() {
    auto view = window->querySubObject("View");
    if (!view) {
        m_filepath = QString::Null();
        emit playerEnd();
        return true;		// TODO return close() for emit
    }

    view->querySubObject("Next()");
    view = window->querySubObject("View");
    if (!view) {
        m_filepath = QString::Null();
        emit playerEnd();
        return true;		// TODO return close() for emit
    }

    return true;
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
    return procRun();
}
