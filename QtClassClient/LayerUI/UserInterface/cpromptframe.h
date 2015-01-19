#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../../Reliable/DataUnit/CMessage.h"
#include "prompt.h"
#include "../../FunctionLogic/Question/dialoganswerquestion.h"

#define _TEST_PROMPT_POS_

class ScoreTable;   // TODO better way

class CPromptFrame
{
private:
    CPromptFrame();
    static void changeDialog(QDialog* dialog);

    // complex dialog may call normal dialog
    // such as answer dialog call "answer right" prompt
    static void changeComplexDialog(QDialog* dialog);

public:
    static QDialog* prompt(int result, QWidget* parent = 0, 
                           WORD pc = PromptControllerConfirm);

    static QDialog* prompt(QString prompt, QWidget* parent = 0,
                           WORD pc = PromptControllerConfirm);

    static QDialog* racePrompt(QWidget* parent = 0);

    static QDialog* answerDialog(WORD format, WORD correctAnswer = QDialog::Rejected,
                                 QWidget* parent = 0);

    static QDialog* questionDialog(QWidget* parent = 0);

    static QDialog* statisticsDialog(ScoreTable* scores, QWidget* parent = 0);
};

#endif // CPROMPTFRAME_H
