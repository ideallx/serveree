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

    void msgProc();

private:
    void setMyPanel();

    Ui::MainWindow *ui;

    MyScene* scene;
    QList<MyScene*> sceneList;

    bool aNewShape;

    HANDLE sem_msg;
    pthread_t msgThread;
    bool isRunning;
    TSQueue<ts_msg> msgQueue;

public slots:
    void changeScene(int n);

    void enterClass();
    void enterClassResult(bool result);

    void leaveClass();
    void leaveClassResult(bool result);

    void classIcon(bool entered);

signals:
    void enOrLeaveClass(bool entered);

private slots:
    void on_actionExit_triggered();
    void on_listWidget_clicked(const QModelIndex &index);
};

void* UIMsgProc(LPVOID lpParam);

#endif // MAINWINDOW_H