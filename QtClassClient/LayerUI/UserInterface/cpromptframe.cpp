#include "cpromptframe.h"
#include <QMessageBox>
#include "dialogpixmap.h"
#include "dialoganswerquestion.h"
#include "dialogbuildquestion.h"

static QDialog* preDialog = NULL;
static QDialog* preComplexDialog = NULL;

CPromptFrame::CPromptFrame()
{

}

void CPromptFrame::changeDialog(QDialog *dialog) {
    if (preDialog) {
        delete preDialog;
        preDialog = NULL;
    }
    preDialog = dialog;

#ifdef _TEST_PROMPT_POS_
    dialog->setGeometry(0, 0, dialog->geometry().width(), dialog->geometry().height());
#endif
}

void CPromptFrame::changeComplexDialog(QDialog *dialog) {
    if (preComplexDialog) {
        delete preComplexDialog;
        preComplexDialog = NULL;
    }
    preComplexDialog = dialog;

#ifdef _TEST_PROMPT_POS_
    dialog->setGeometry(0, 0, dialog->geometry().width(), dialog->geometry().height());
#endif
}



QDialog* CPromptFrame::prompt(int result, WORD pc, QWidget *parent) {
    QDialog* d = new Prompt(result, pc, parent);
    changeDialog(d);
    return d;
}

QDialog* CPromptFrame::prompt(QString prompt, WORD pc, QWidget* parent) {
    QDialog* d = new Prompt(prompt, pc, parent);
    changeDialog(d);
    return d;
}

QDialog* CPromptFrame::racePrompt(QWidget* parent) {
    QDialog* d = new DialogPixmap(parent);
    changeDialog(d);
    return d;
}

QDialog* CPromptFrame::answerDialog(WORD format, WORD correctAnswer, QWidget* parent) {
    DialogAnswerQuestion* d = new DialogAnswerQuestion(format, parent);
    d->setCorrectAnswer(correctAnswer);
    changeComplexDialog(d);
    return d;
}

QDialog* CPromptFrame::questionDialog(QWidget* parent) {
    QDialog* d = new DialogBuildQuestion(parent);
    changeComplexDialog(d);
    return d;
}

QDialog* CPromptFrame::statisticsDialog(ScoreTable scores, QWidget* parent) {
    DialogBuildStatistics* d = new DialogBuildStatistics(parent);
    d->setScoreTable(scores);
    changeComplexDialog(d);
    return d;
}
