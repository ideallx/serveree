#ifndef COURSEWAREWIDGET_H
#define COURSEWAREWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "../../Message/CMsgObject.h"
#include "../../player/absplayer.h"
#include "../MsgGenerator/cfilemsggenerator.h"
#include "../MsgGenerator/cplayergenerator.h"

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

    inline void setRole(enum RoleOfClass role) { m_userRole = role; }

signals:
    void clearScreen(TS_UINT64 sceneID, int cleanOption);
    void paintModeChanged(int mode);
    void promptSent(int result);
    void changeBackground(QPixmap pic);
    void changeMedia(QMediaPlayer* player);

private:

    void syncFile(QString filename);
    void playFileByUser(QString filename);

private slots:
    void on_tbStart_clicked();
    void on_tbPrev_clicked();
    void on_tbNext_clicked();
    void on_tbUpload_clicked();
    void on_tbSync_clicked();
    void on_lsWare_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_tbExitWare_clicked();
    void on_lsWare_itemDoubleClicked(QListWidgetItem *item);

private:
    CMsgObject*             m_parent;
    bool                    m_isPlayerPlaying;
    AbsPlayer*              m_player;
    CPlayerGenerator        m_pg;
    CFileMsgGenerator       m_fmg;
    QList<QString>          m_syncedWares;
    enum RoleOfClass        m_userRole;
    Ui::CourseWareWidget *ui;
};

#endif // COURSEWAREWIDGET_H
