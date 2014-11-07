#ifndef _PLAYER_ABSPLAYER_H_
#define _PLAYER_ABSPLAYER_H_

#include <QAxObject>
#include <QString>
#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"

class AbsPlayer : public QObject {
    Q_OBJECT

public:
    AbsPlayer(QString filepath, CMsgObject* parent);
    virtual ~AbsPlayer();

    virtual bool isLoadSuccess() { return m_isLoadSuccess; }

    bool run();
    bool next();
    bool prev();
    bool close();
    bool stop();
    bool start();

protected:
    virtual bool procRun() = 0;
    virtual bool procNext() = 0;
    virtual bool procPrev() = 0;
    virtual bool procClose() = 0;
    virtual bool procStop() = 0;
    virtual bool procStart() = 0;

signals:
    void playerEnd();


protected:
    QAxObject*  m_controller;
    CMsgObject* m_parent;
    QString     m_filepath;
    bool        m_isLoadSuccess;
};




#endif
