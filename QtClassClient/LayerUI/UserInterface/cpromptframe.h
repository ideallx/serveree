#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../../Reliable/DataUnit/CMessage.h"
#include "prompt.h"
#include "dialogbuildstatistics.h"

// #define _TEST_PROMPT_POS_

class CPromptFrame
{
private:
    CPromptFrame();
    static void changeDialog(QDialog* dialog);

    // complex dialog may call normal dialog
    // such as answer dialog call "answer right" prompt
    static void changeComplexDialog(QDialog* dialog);

public:
    static QDialog* prompt(int result, WORD pc = PromptControllerConfirm,
                           QWidget* parent = 0);

    static QDialog* prompt(QString prompt, WORD pc = PromptControllerConfirm,
                           QWidget* parent = 0);

    static QDialog* racePrompt(QWidget* parent = 0);

    static QDialog* answerDialog(WORD format, WORD correctAnswer = ChoiceUnset,
                                 QWidget* parent = 0);

    static QDialog* questionDialog(QWidget* parent = 0);

    static QDialog* statisticsDialog(WORD total, ScoreTable scores, QWidget* parent = 0);
};

#endif // CPROMPTFRAME_H
