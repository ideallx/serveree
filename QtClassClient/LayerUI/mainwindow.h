#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "myscene.h"
#include "../Message/CMsgObject.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CMsgObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote);

private:
    Ui::MainWindow *ui;

	MyScene* scene;

    bool isNextBegin;

    QVector<QPushButton*> buttons;

    void buttonsUnchecked();

public slots:
    void enterClass();

    void leaveClass();

    void changeTypeEllipse();
    void changeTypeRect();
    void changeTypeScripts();
    void changeTypeLine();

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_comboBox_2_currentIndexChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
