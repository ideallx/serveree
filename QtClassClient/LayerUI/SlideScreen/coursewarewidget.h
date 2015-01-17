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

    void setRole(enum RoleOfClass role);

    // recvied new item shoule be added to synced file list
    void recvNewItem(QString filename);


signals:
    void clearScreen(TS_UINT64 sceneID, int cleanOption);
    void paintModeChanged(int mode);
    void promptSent(int result);
    void promptMsgSent(QString prompt);
    void changeBackground(QPixmap pic);
    void changeMedia(QMediaPlayer* player);
    void changeUserAuth(TS_UINT64 uid, bool set);
    void askChangeScene(TS_UINT64 sceneid);
    void slideChanged(QString slideInfo);
    void changeSide(bool isCoursewareSlide);
    void syncFileComplete(QString filename);

private:
    void scanLocalCourseware();

    // return isAllowed to play
    // when first synced not allowed
    // when synced or dont sync allowed
    bool syncFile(QString filename, bool hasPrompt = false);
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


public slots:
    void syncComplete(QString filename);

private:
    CMsgObject*             m_parent;
    bool                    m_isPlayerPlaying;
    AbsPlayer*              m_player;
    CPlayerGenerator        m_pg;
    CFileMsgGenerator       m_fmg;
    QSet<QString>           m_syncedWares;
    enum RoleOfClass        m_userRole;
    Ui::CourseWareWidget    *ui;
    DataSingleton           *m_ds;
    QFutureWatcher<void>    threadSync;

friend void syncThread(CourseWareWidget* cww, Prompt* p);
};

#endif // COURSEWAREWIDGET_H
