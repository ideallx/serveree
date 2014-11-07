#ifndef _PLAYER_PLAYERFACTORY_H_
#define _PLAYER_PLAYERFACTORY_H_

#include "absplayer.h"

class PlayerFactory
{
public:
    explicit PlayerFactory() {}

    static AbsPlayer* createPlayer(QString filepath, CMsgObject *parent);

signals:

public slots:

};


#endif
