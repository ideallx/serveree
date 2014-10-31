#ifndef _PLAYER_PPTPLAYER_H_
#define _PLAYER_PPTPLAYER_H_

#include <QAxObject>
#include <QString>
#include "../Reliable/DataUnit/CMessage.h"
#include "absplayer.h"

class PPTPlayer : public AbsPlayer {
public:
    PPTPlayer(QString filepath, CMsgObject* parent);

    bool procRun();
    bool procNext();
    bool procPrev();
    bool procClose();
    bool procStop();
    bool procStart();

    virtual ~PPTPlayer();

protected:
    QAxObject* presentation;
    QAxObject* opened;
    QAxObject* sss;
    QAxObject* window;
};




#endif
