#ifndef _PLAYER_ABSPLAYER_H_
#define _PLAYER_ABSPLAYER_H_

#include <QAxObject>
#include <QString>
#include <QPixmap>
#include <QMediaPlayer>
#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"

class AbsPlayer : public QObject {
    Q_OBJECT

public:
    AbsPlayer(QString filepath, CMsgObject* parent);
    virtual ~AbsPlayer();

	inline const QString filePath() { return m_filepath; }

    virtual bool isLoadSuccess() { return m_isLoadSuccess; }
    // virtual void addFile(QString filename);

    // if true, set the graphicsview background stylesheet as transparent
    inline bool isTransBackground() { return m_transBackground; }

    // if true, prev and next process was done by player class
    // if false, process was done by mainwindow
    inline bool isInnerNextPrev() { return m_isInnerPvNx; }

	inline bool isWaiting() { return m_isWaiting; }

    virtual bool isPostfixRight(QString filename) { return false; }

    static QRect screenSize();

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
    void backgroundChanged(QPixmap);
    void playMedia(QMediaPlayer*);


protected:
    QAxObject*  m_controller;
    CMsgObject* m_parent;
    QString     m_filepath;
    bool        m_isLoadSuccess;
    QList<QString> m_fileList;
    QRect       m_screenRect;
    bool        m_transBackground;
    bool        m_isInnerPvNx;
	bool		m_isWaiting;
};




#endif
