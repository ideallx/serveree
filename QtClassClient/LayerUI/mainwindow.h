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

friend void* MsgFFProc(LPVOID lpParam);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote);

    void msgProc();

private:
    Ui::MainWindow *ui;

	MyScene* scene;

    void setMyPanel();

    bool aNewShape;

    HANDLE sem_msg;
    pthread_t msgThread;
    bool isRunning;
    TSQueue<ts_msg> msgQueue;

public slots:
    void enterClass();
    void enterClassResult(bool result);

    void leaveClass();
    void leaveClassResult(bool result);


private slots:
    void on_actionExit_triggered();
};

void* MsgFFProc(LPVOID lpParam);

#endif // MAINWINDOW_H
