#include <QDebug>
#include <QDir>
#include "pptplayer.h"

PPTPlayer::PPTPlayer(QString filepath, CMsgObject* parent)
    : AbsPlayer(filepath, parent)
    , opened(NULL)
    , lastSlideNum(0) {
    if (!m_controller->setControl("Powerpoint.Application"))
        return;
    m_controller->setProperty("Visible", false);
    m_transBackground = true;
    m_isLoadSuccess = true;
}
	

PPTPlayer::~PPTPlayer() {
    if (opened)
        opened->dynamicCall("Close()");
}


void PPTPlayer::slideNumberCheck(QAxObject* view) {
    if (NULL == view)
        return;
    auto slide = view->querySubObject("Slide");
    if (NULL == slide) {
        emit playerEnd();
        return;
    }

    bool ok;
    int slideNumThis = slide->dynamicCall("SlideIndex").toInt(&ok);
    if (!ok)
        return;

    if (lastSlideNum != slideNumThis) {
        lastSlideNum = slideNumThis;
        QString signal = QString("%1_%2").arg(getFileName(m_filepath)).arg(lastSlideNum);
        emit slideChanged(signal);
    }

}

bool PPTPlayer::isPostfixRight(QString filename) {
    QString postfix = filename.split('.').last();
    if (postfix == "ppt")
        return true;
    return false;
}

bool PPTPlayer::procRun() {
    presentation = m_controller->querySubObject("Presentations");
    opened = presentation->querySubObject("Open(QString, QVariant, QVariant, QVariant)", m_filepath, 1, 1, 0);
    if (!opened) {
        emit promptSent(getFileName(m_filepath) + QString::fromLocal8Bit("PPT ´ò¿ªÊ§°Ü"));
        return false;
    }
    opened->setProperty("IsFullScreen", false);

    sss = opened->querySubObject("SlideShowSettings");
    if (!sss) {
        emit promptSent(QString::fromLocal8Bit("PPT ÉèÖÃÊ§°Ü"));
        return false;
    }
    sss->setProperty("ShowWithAnimation", true);

    sss->querySubObject("Run()");
    window = opened->querySubObject("SlideShowWindow");
    if (!window) {
        emit promptSent(QString::fromLocal8Bit("PPT ²¥·ÅÊ§°Ü"));
        return false;
    }

    window->setProperty("Top", 40);
    window->setProperty("Left", 180);
    window->setProperty("Width", window->property("Width").toInt() - 180);
    window->setProperty("Height", window->property("Height").toInt() - 40);

    qDebug() << "windows property" << window->property("Top")
        << window->property("Left") << window->property("Width")
        << window->property("Height");

    auto view = window->querySubObject("View");
    slideNumberCheck(view);
//    auto slides = window->querySubObject("Presentation");
//    slides = slides->querySubObject("Slides(int)", 1);
//    if (!slides) {
//        return false;
//    }

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
	
    view->dynamicCall("Next()");
    view = window->querySubObject("View");
    if (!view) {
        m_filepath = QString::Null();
        emit playerEnd();
        return true;		// TODO return close() for emit
    }

    slideNumberCheck(view);
    return true;
}

bool PPTPlayer::procPrev() {
    auto view = window->querySubObject("View");
    if (!view)
        return false;

    view->dynamicCall("Previous()");

    slideNumberCheck(view);
    return true;
}

bool PPTPlayer::procClose() {
    qDebug() << "close";
    opened->dynamicCall("Close()");
    return true;
}

bool PPTPlayer::procStop() {
    return true;
}

bool PPTPlayer::procStart() {
    return procRun();
}
