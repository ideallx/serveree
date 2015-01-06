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
    explicit DialogAnswerQuestion(WORD format, QWidget *parent = 0);
    ~DialogAnswerQuestion();

    inline void setCorrectAnswer(WORD answer) { correctAnswer = answer; }


private slots:
    void on_tbChoiceA_clicked();

    void on_tbChoiceC_clicked();

    void on_tbChoiceB_clicked();

    void on_tbChoiceD_clicked();

private:
    bool answerCheck(WORD stuAnswer);

    void returnAnswer(WORD stuAnswer);

private:
    Ui::DialogAnswerQuestion    *ui;
    WORD                        format;
    WORD                        correctAnswer;
};

#endif // DIALOGANSWERQUESTION_H
