#ifndef DIALOGCHOOSEREPLAY_H
#define DIALOGCHOOSEREPLAY_H

#include <QDialog>
#include <QSignalMapper>
#include <QToolButton>

namespace Ui {
class DialogChooseReplay;
}

class DialogChooseReplay : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseReplay(QWidget *parent = 0);
    ~DialogChooseReplay();

    void addCourse(QString className);

private slots:
    void on_tbBack_clicked();

    void on_tbExit_clicked();

    void clickButton(QString className);

private:
    void takeBack();

private:
    Ui::DialogChooseReplay *ui;

    QSignalMapper* sm;

    QToolButton* allButton[20];


signals:
    void classChosen(QString classname);

    void goBack();
};

#endif // DIALOGCHOOSEREPLAY_H
