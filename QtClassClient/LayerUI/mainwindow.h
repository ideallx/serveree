#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myscene.h"
#include "../Message/CMsgObject.h"
#include "../DataStructure/TSQueue.h"
#include <QVector>
#include <pthread.h>
#include <semaphore.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CMsgObject
{
    Q_OBJECT

friend void* UIMsgProc(LPVOID lpParam);

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

    bool aNewShape;

    HANDLE sem_msg;
    pthread_t msgThread;
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
};

void* UIMsgProc(LPVOID lpParam);

#endif // MAINWINDOW_H
