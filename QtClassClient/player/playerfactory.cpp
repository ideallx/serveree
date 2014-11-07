#include <QString>
#include <QStringList>
#include "playerfactory.h"

#include "docplayer.h"
#include "pptplayer.h"

AbsPlayer* PlayerFactory::createPlayer(QString filepath, CMsgObject *parent) {
    QString postfix = filepath.split('.').last();

    if (postfix == "ppt") {
        return new PPTPlayer(filepath, parent);
    } else if (postfix == "doc") {
        return new DocPlayer(filepath, parent);
    } else {
        return NULL;
    }

    return NULL;
}
