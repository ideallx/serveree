#include <QString>
#include <QStringList>
#include "playerfactory.h"

#include "docplayer.h"
#include "pptplayer.h"
#include "jpgplayer.h"

AbsPlayer* PlayerFactory::createPlayer(QString filepath, CMsgObject *parent) {
    QString postfix = filepath.split('.').last();

    if (postfix == "ppt") {
        return new PPTPlayer(filepath, parent);
    } else if (postfix == "doc") {
        return new DocPlayer(filepath, parent);
    } else if (postfix == "jpg" || postfix == "jpeg" || \
               postfix == "png" || postfix == "bmp") {
        return new JpgPlayer(filepath, parent);
    }

    return NULL;
}

QString allowedList[] = {"ppt", "doc", "jpg", "jpeg", "png", "bmp"};

bool PlayerFactory::checkFileFormat(QString filename) {
    QString postfix = filename.split('.').last();
    for (int i = 0; i < 5; i++) {
        if (allowedList[i] == postfix)
            return true;
    }
    return false;
}
