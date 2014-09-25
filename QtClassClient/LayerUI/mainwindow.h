#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Message/CMsgObject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CMsgObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
