#ifndef DOCPLAYER_H
#define DOCPLAYER_H

#include <QAxObject>
#include <QString>
#include "../Reliable/DataUnit/CMessage.h"
#include "absplayer.h"

class DocPlayer : public AbsPlayer {
public:
    DocPlayer(QString filepath, CMsgObject* parent);

    bool procRun();
    bool procNext();
    bool procPrev();
    bool procClose();
    bool procStop();
    bool procStart();

    virtual ~DocPlayer();

protected:
    QAxObject* doc;

    int totalSlide;
    int curSlide;
};


#endif // DOCPLAYER_H
