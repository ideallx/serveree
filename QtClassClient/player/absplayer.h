#ifndef _PLAYER_ABSPLAYER_H_
#define _PLAYER_ABSPLAYER_H_

#include <QAxObject>
#include <QString>
#include <QPixmap>
#include <QMediaPlayer>
#include <qdir.h>
#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"

QString getFileName(QString filepath);
QString getFilePath(QString filename);


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

    inline bool isFinished() { return m_filepath == QString::null; }

    inline bool isMedia() { return m_isMedia; }

    inline bool isMediaEnd() { return m_isMediaEnd; }

    virtual bool isPostfixRight(QString filename) { return false; }

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
    void promptSent(QString prompt);
    void slideChanged(QString slideInfo);   // slide info was concat by filename and slideNum as xxx.ppt_1 

protected:
    QAxObject*  m_controller;
    CMsgObject* m_parent;
    QString     m_filepath;
    bool        m_isLoadSuccess;
    QRect       m_screenRect;
    bool        m_transBackground;      // does media need a transparent background
    bool        m_isInnerPvNx;          // inner previos and next like ppt and media others like png 
	bool		m_isWaiting;            // unused
    bool        m_isMedia;              // media: pause start
    bool        m_isMediaEnd;

    QList<QString> m_fileList;
};




#endif
