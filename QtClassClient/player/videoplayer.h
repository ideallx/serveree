#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include "../Reliable/DataUnit/CMessage.h"
#include "absplayer.h"

class VideoPlayer : public AbsPlayer {
public:
    VideoPlayer(QString filepath, CMsgObject *parent);
    bool isPostfixRight(QString filename);

    bool procRun();
    bool procNext();
    bool procPrev();
    bool procClose();
    bool procStop();
    bool procStart();

    int step;

    void checkStatus(QMediaPlayer::State status);
    virtual ~VideoPlayer() {}

private:
    QMediaPlayer mediaPlayer;
};

#endif // VIDEOPLAYER_H
