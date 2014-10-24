#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myscene.h"
#include "../Message/CMsgObject.h"
#include "../Reliable/DataStructure/TSQueue.h"
#include <QVector>
#include <iop_thread.h>
#include <semaphore.h>

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

    void addUser(TS_UINT64 uid, QString username);

    void removeUser(TS_UINT64 uid);

    void msgProc();

private:
    Ui::MainWindow *ui;

    MyScene* scene;
    QMap<TS_UINT64, MyScene*> sceneMap;

    HANDLE sem_msg;
    iop_thread_t pthread_msg;
    bool isRunning;
    TSQueue<ts_msg> msgQueue;

public slots:
    void changeScene(TS_UINT64 uid);

    void enterClass(QString username, QString password);
    void enterClassResult(bool result);

    void leaveClass();
    void leaveClassResult(bool result);

    void classIcon(bool entered);

    void drawScene();

signals:
    void enOrLeaveClass(bool entered);
    void drawShape();
    void addScene(int uidh, int uidl);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_tbMyClass_clicked();
    void on_btClassInfo_clicked();
    void on_tbTeacherBoard_clicked();
    void on_tbMyBoard_clicked();

    void addSceneSlot(int uidh, int uidl);

    friend thread_ret_type thread_func_call UIMsgProc(LPVOID lpParam);
};

#endif // MAINWINDOW_H
