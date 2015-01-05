#ifndef DIALOGANSWERQUESTION_H
#define DIALOGANSWERQUESTION_H

#include <QDialog>
#include "../../Reliable/DataUnit/CMessage.h"

namespace Ui {
class DialogAnswerQuestion;
}

class DialogAnswerQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnswerQuestion(QWidget *parent = 0);
    ~DialogAnswerQuestion();

private slots:
    void on_tbChoiceA_clicked();

    void on_tbChoiceC_clicked();

    void on_tbChoiceB_clicked();

    void on_tbChoiceD_clicked();

private:
    Ui::DialogAnswerQuestion *ui;
};

#endif // DIALOGANSWERQUESTION_H
