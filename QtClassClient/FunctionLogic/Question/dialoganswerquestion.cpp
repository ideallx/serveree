#include "dialoganswerquestion.h"
#include "ui_dialoganswerquestion.h"
#include "../../LayerUI/UserInterface/cpromptframe.h"
#include "cquestionlogicmodule.h"

DialogAnswerQuestion::DialogAnswerQuestion(WORD format, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAnswerQuestion)
    , format(format)
    , correctAnswer(ChoiceUnset) {
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    if (format == QuestionBool) {
        ui->tbChoiceA->setText("T");
        ui->tbChoiceC->setText("F");
        ui->tbChoiceB->setVisible(false);
        ui->tbChoiceD->setVisible(false);
    } else {
        ui->tbChoiceA->setText("A");
        ui->tbChoiceC->setText("C");
        ui->tbChoiceB->setVisible(true);
        ui->tbChoiceD->setVisible(true);
    }

#ifdef _TEST_PROMPT_POS_
    setGeometry(0, 0, geometry().width(), geometry().height());
#endif
}

bool DialogAnswerQuestion::answerCheck(WORD stuAnswer) {
    if (stuAnswer == correctAnswer) {
        CPromptFrame::prompt(QString::fromLocal8Bit("恭喜你，回答正确"), 
                             dynamic_cast<QWidget*> (parent()))->show();
        return true;
    } else {
        CPromptFrame::prompt(QString::fromLocal8Bit("很可惜，回答错误"), 
                             dynamic_cast<QWidget*> (parent()))->show();
        return false;
    }
}

void DialogAnswerQuestion::returnAnswer(WORD stuAnswer) {
    if (ChoiceUnset != correctAnswer) {
        answerCheck(stuAnswer);
    }
    done(stuAnswer);
}

DialogAnswerQuestion::~DialogAnswerQuestion()
{
    delete ui;
}

void DialogAnswerQuestion::on_tbChoiceA_clicked()
{
    if (format == QuestionBool) {
        returnAnswer(ChoiceTrue);
    } else {
        returnAnswer(ChoiceA);
    }
}

void DialogAnswerQuestion::on_tbChoiceC_clicked()
{
    if (format == QuestionBool) {
        returnAnswer(ChoiceFalse);
    } else {
        returnAnswer(ChoiceC);
    }
}

void DialogAnswerQuestion::on_tbChoiceB_clicked()
{
    returnAnswer(ChoiceB);
}

void DialogAnswerQuestion::on_tbChoiceD_clicked()
{
    returnAnswer(ChoiceD);
}
