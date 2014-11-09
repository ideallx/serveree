#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidgetItem>
#include <QPaintEvent>

#include "../Reliable/DataUnit/CMessage.h"

#include "myscene.h"
#include "cfilemsggenerator.h"
#include "cplayergenerator.h"
#include "../Message/CMsgObject.h"
#include "../Reliable/DataStructure/TSQueue.h"
#include <QVector>
#include <iop_thread.h>
#include "../player/absplayer.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CMsgObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote);

    void addUser(TS_UINT64 uid, QByteArray username, bool isOnline);

    void removeUser(TS_UINT64 uid);

    void msgProc();

    void paintEvent(QPaintEvent *e);


    void syncFile(QString filename);

    void setWriteable(TS_UINT64 toUID, DWORD sceneID, WORD writeable);

    bool playerPrev();
    bool playerNext();
    bool playerStart(QString filename);
    bool playerStop();

    void recvClassInfo();
    void playmodeEnd();
    void addWareList(QString filename);

    void setUserAccount(QString user, QString pass);

private:
    Ui::MainWindow*             ui;
    enum RoleOfClass            m_userRole;     // user role of the client, if teacher will be more powerful
    bool                        isRunning;

    MyScene*                    scene;          // the current shown scene
    QMap<TS_UINT64, MyScene*>   sceneMap;       // all available scene of this class

    HANDLE                      sem_msg;        // maintain the msgthread, but some problem
    iop_thread_t                pthread_msg;
    TSQueue<ts_msg>             msgQueue;
    CFileMsgGenerator           m_fmg;
    bool                        isPlayerPlaying;
    AbsPlayer*                  m_player;
    CPlayerGenerator            m_pg;


public slots:
    void changeScene(TS_UINT64 uid);

    void enterClass(QString username, QString password);
    void enterClassResult(bool result);

    void leaveClass();
    void leaveClassResult(bool result);

    void setRole(enum RoleOfClass role);

    void classIcon(bool entered);

    void drawScene();

    void sendPrompt(QString prompt);
    void sendResultPrompt(int result);

    void changeBackground(QPixmap newPix);

private:
    bool playerPlay(QString filepath);
    bool stopPlayer(void);


signals:
    void enOrLeaveClass(bool entered);
    void drawShape();
    void addScene(int uidh, int uidl);
    void promptSent(QString prompt);
    void promptResultSent(int result);
    void stopServerRespTimer();
    void wareItemRecv(QString filename);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_tbMyClass_clicked();
    void on_btClassInfo_clicked();
    void on_tbTeacherBoard_clicked();
    void on_tbMyBoard_clicked();

    void addSceneSlot(int uidh, int uidl);
    void showPrompt(QString prompt);
    void showResultPrompt(int result);
    void addWareItem(QString string);
    void deleteFile(QString filename);

    friend thread_ret_type thread_func_call UIMsgProc(LPVOID lpParam);
    void on_tbCourseWare_clicked();
    void on_tbBackground_clicked();
    void on_tbUpload_clicked();
    void on_tbSync_clicked();
    void on_lsWare_itemDoubleClicked(QListWidgetItem *item);
    void on_tbExitWare_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_tbPrev_clicked();
    void on_tbStart_clicked();
    void on_tbNext_clicked();
    void on_lsWare_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // MAINWINDOW_H
