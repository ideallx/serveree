#include "dialoganswerquestion.h"
#include "ui_dialoganswerquestion.h"

DialogAnswerQuestion::DialogAnswerQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnswerQuestion)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

DialogAnswerQuestion::~DialogAnswerQuestion()
{
    delete ui;
}

void DialogAnswerQuestion::on_tbChoiceA_clicked()
{
    done(ChoiceA);
}

void DialogAnswerQuestion::on_tbChoiceC_clicked()
{
    done(ChoiceC);
}

void DialogAnswerQuestion::on_tbChoiceB_clicked()
{
    done(ChoiceB);
}

void DialogAnswerQuestion::on_tbChoiceD_clicked()
{
    done(ChoiceD);
}
