#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../../Reliable/DataUnit/CMessage.h"
#include "prompt.h"

// #define _TEST_PROMPT_POS_


class CPromptFrame
{
public:
    CPromptFrame();

    static QDialog* prompt(int result, WORD pc = PromptControllerConfirm,
                           QWidget* parent = 0);

    static QDialog* prompt(QString prompt, WORD pc = PromptControllerConfirm,
                           QWidget* parent = 0);

    static QDialog* racePrompt(QWidget* parent);
};

#endif // CPROMPTFRAME_H
