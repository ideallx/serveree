#include <QString>
#include <QStringList>
#include "playerfactory.h"

#include "docplayer.h"
#include "pptplayer.h"
#include "jpgplayer.h"
#include "videoplayer.h"

AbsPlayer* PlayerFactory::createPlayer(QString filepath, CMsgObject *parent) {
    QString postfix = filepath.split('.').last();

    if (postfix == "ppt") {
        return new PPTPlayer(filepath, parent);
    } /*else if (postfix == "doc" || postfix == "docx") {
        return new DocPlayer(filepath, parent);
    }*/ else if (postfix == "jpg" || postfix == "jpeg" || \
               postfix == "png" || postfix == "bmp") {
        return new JpgPlayer(filepath, parent);
    } else if (postfix == "mp4" || postfix == "rmvb" || \
               postfix == "avi" || postfix == "rm" || \
               postfix == "wmv") {
        return new VideoPlayer(filepath, parent);
    }

    return NULL;
}

QString allowedList[] = {"ppt", /*"doc", "docx",*/ "jpg", "jpeg", "png", "bmp",
                        "avi", "rmvb", "rm", "mp4", "wmv"};

bool PlayerFactory::checkFileFormat(QString filename) {
    QString postfix = filename.split('.').last();
    for (int i = 0; i < 9; i++) {
        if (allowedList[i] == postfix)
            return true;
    }
    return false;
}
