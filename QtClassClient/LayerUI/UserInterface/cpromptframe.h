#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../../Reliable/DataUnit/CMessage.h"


class CPromptFrame
{
public:
    CPromptFrame();

    static QDialog* prompt(int result, QWidget* parent = 0);

    static QDialog* prompt(QString prompt, QWidget* parent = 0);

    static QDialog* racePrompt(QWidget* parent);
};

#endif // CPROMPTFRAME_H
