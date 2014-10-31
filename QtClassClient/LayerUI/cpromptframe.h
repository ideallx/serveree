#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../Reliable/DataUnit/CMessage.h"

const QString AllPrompts[] = {
    "�ɹ�",
    "��¼�ɹ�",
    "logout success",
    "already logged in",
    "username error",
    "password error",
    "unknown error"
};

class CPromptFrame
{
public:
    CPromptFrame();

    static void prompt(int result, QWidget* parent = 0);
};

#endif // CPROMPTFRAME_H
