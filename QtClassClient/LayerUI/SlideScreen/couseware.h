#ifndef _COURSEWARE_H_
#define _COURSEWARE_H_

#include <QList>
#include <QString>
#include <QListWidget>

#include "../../Message/CMsgObject.h"
#include "../../player/absplayer.h"
#include "../MsgGenerator/cfilemsggenerator.h"
#include "../MsgGenerator/cplayergenerator.h"

QString getFileName(QString filepath);


class CourseWareData  {

public:
    CourseWareData(CMsgObject* msgParent);
    virtual ~CourseWareData();

    inline void setListWidget(QListWidget* that) { m_listWidget = that; }

    inline bool isPlayerPlaying() { return m_isPlayerPlaying; }

    // return errno
    int checkUploadFile(QString filename) const;

    // return number of file
    int addFileToList(QString filename);

    void syncFileList();

    // return false when can't be played
    bool playTest(QString filename) const;

    int play(QString filename, bool isRemote);

    bool stop(bool isRemote);

    bool next(bool isRemote);

    bool prev(bool isRemote);

private:
    void syncFile(QString filename);


private:
    CMsgObject*             m_parent;
    bool                    m_isPlayerPlaying;
    AbsPlayer*              m_player;
    CPlayerGenerator        m_pg;
    CFileMsgGenerator       m_fmg;
    QList<QString>          m_syncedWares;
    QListWidget*            m_listWidget;
};

#endif
