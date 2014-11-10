#ifndef JPGPLAYER_H
#define JPGPLAYER_H

#include <QString>
#include "../Reliable/DataUnit/CMessage.h"
#include "absplayer.h"

class JpgPlayer : public AbsPlayer {
public:
    JpgPlayer(QString filepath, CMsgObject *parent);
    bool isPostfixRight(QString filename);

    bool procRun();
    bool procNext();
    bool procPrev();
    bool procClose();
    bool procStop();
    bool procStart();

    virtual ~JpgPlayer() {}

private:
    QPixmap pixmapCut(QPixmap& pix);


private:
    QPixmap* m_background;
};

#endif // JPGPLAYER_H
