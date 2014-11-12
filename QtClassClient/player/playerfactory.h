#ifndef _PLAYER_PLAYERFACTORY_H_
#define _PLAYER_PLAYERFACTORY_H_

#include "absplayer.h"

class PlayerFactory
{
public:
    explicit PlayerFactory() {}

    static AbsPlayer* createPlayer(QByteArray filepath, CMsgObject *parent);

    static bool checkFileFormat(QString filename);

signals:

public slots:

};


#endif
