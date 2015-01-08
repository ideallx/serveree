#include "dialogbuildquestion.h"
#include "ui_dialogbuildquestion.h"
#include "../../Reliable/DataUnit/CMessage.h"
#include "cpromptframe.h"

int transAnswerToInt(WORD type, WORD answer) {
    return type + (answer << 8);
}

DialogBuildQuestion::DialogBuildQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBuildQuestion)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this); 
#ifdef _TEST_PROMPT_POS_
        setGeometry(0, 0, geometry().width(), geometry().height());
#endif
}

DialogBuildQuestion::~DialogBuildQuestion()
{
    delete ui;
}


void DialogBuildQuestion::on_tbChoiceA_clicked()
{
    return done(ChoiceA);
}

void DialogBuildQuestion::on_tbChoiceB_clicked()
{
    return done(ChoiceB);
}

void DialogBuildQuestion::on_tbChoiceC_clicked()
{
    return done(ChoiceC);
}

void DialogBuildQuestion::on_tbChoiceD_clicked()
{
    return done(ChoiceD);
}

void DialogBuildQuestion::on_tbBoolTrue_clicked()
{
    return done(ChoiceTrue);
}

void DialogBuildQuestion::on_tbBoolFalse_clicked()
{
    return done(ChoiceFalse);
}

void DialogBuildQuestion::on_pbAccount_clicked()
{
    return done(ChoiceStatistics);
}

void DialogBuildQuestion::on_tbDialogExit_clicked()
{
    return done(ChoiceUnset);
}
