#include <QString>
#include "playerfactory.h"

#include "pptplayer.h"

AbsPlayer* PlayerFactory::createPlayer(QString filepath, CMsgObject *parent) {
    QString postfix = filepath.split('.').last();

    if (postfix == "ppt") {
        return new PPTPlayer(filepath, parent);
    }
}
