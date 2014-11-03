#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../Reliable/DataUnit/CMessage.h"


class CPromptFrame
{
public:
    CPromptFrame();

    static void prompt(int result, QWidget* parent = 0);
};

#endif // CPROMPTFRAME_H
