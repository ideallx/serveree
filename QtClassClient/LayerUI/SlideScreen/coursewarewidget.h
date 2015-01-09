#ifndef COURSEWAREWIDGET_H
#define COURSEWAREWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QListWidgetItem>
#include <QtConcurrent>
#include "../../Message/CMsgObject.h"
#include "../../player/absplayer.h"
#include "../MsgGenerator/cfilemsggenerator.h"
#include "../MsgGenerator/cplayergenerator.h"
#include "../MsgGenerator/cracegenerator.h"
#include "cpromptframe.h"

class DataSingleton;

namespace Ui {
class CourseWareWidget;
}


QString getFileName(QString filepath);

class CourseWareWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CourseWareWidget(QWidget *parent = 0);
    virtual ~CourseWareWidget();

    inline bool isPlayerPlaying() { return m_isPlayerPlaying; }
    inline void setMsgParent(CMsgObject* msg) { m_parent = msg; }

    // return errno
    int checkUploadFile(QString filename) const;

    // return number of file
    int addFileToList(QString filename);

    void syncFileList();

    // return false when can't be played
    bool playTest(QString filename) const;

    bool playerStop();

    int start(QString filename, bool isRemote);
    bool stop(bool isRemote);
    bool next(bool isRemote);
    bool prev(bool isRemote);

    void playmodeEnd();

    void addWareItem(QString filename);
    void deleteFile(QString filename);

    void raceBegin(TS_UINT64 teacherUID);
    void raceRun(TS_UINT64 studentUID);
    void raceResult(TS_UINT64 teacherUID, TS_UINT64 studentUID, WORD writingTime);

    void setRole(enum RoleOfClass role);
    void sendRace();
    void recvRace(TS_UINT64 studentUID, TS_UINT64 time);

    // recvied new item shoule be added to synced file list
    void recvNewItem(QString filename);


signals:
    void clearScreen(TS_UINT64 sceneID, int cleanOption);
    void paintModeChanged(int mode);
    void promptSent(int result);
    void promptMsgSent(QString prompt);
    void changeBackground(QPixmap pic);
    void changeMedia(QMediaPlayer* player);
    void racePromptSent();
    void changeUserAuth(TS_UINT64 uid, bool set);
    void someBodyRaceSuccess(TS_UINT64 uid);
    void askChangeScene(TS_UINT64 sceneid);
    void slideChanged(QString slideInfo);
    void changeSide(bool isCoursewareSlide);
    void syncFileComplete(QString filename);

private:
    void scanLocalCourseware();
    void syncFile(QString filename, bool hasPrompt = false);
    void playFileByUser(QString filename);

    QDialog* getDialog(QString prompt, WORD controller);


private slots:
    void on_tbStart_clicked();
    void on_tbPrev_clicked();
    void on_tbNext_clicked();
    void on_tbUpload_clicked();
    void on_tbSync_clicked();
    void on_lsWare_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_tbExitWare_clicked();
    void on_lsWare_itemDoubleClicked(QListWidgetItem *item);

    void on_tbRace_clicked();

    void raceTimeOut();
    void syncComplete(QString filename);

private:
    CMsgObject*             m_parent;
    bool                    m_isPlayerPlaying;
    AbsPlayer*              m_player;
    CPlayerGenerator        m_pg;
    CFileMsgGenerator       m_fmg;
    CRaceGenerator          m_rg;
    QSet<QString>           m_syncedWares;
    enum RoleOfClass        m_userRole;
    Ui::CourseWareWidget    *ui;
    QTimer                  m_raceTimer;
    TS_UINT64               m_raceTime;
    TS_UINT64               m_raceOne;
    DataSingleton           *m_ds;
    QFutureWatcher<void>    threadSync;

friend void syncThread(CourseWareWidget* cww, Prompt* p);
};

#endif // COURSEWAREWIDGET_H
