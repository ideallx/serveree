#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAxObject>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAxObject* controller;
    QAxObject* docu;
};

#endif // MAINWINDOW_H
