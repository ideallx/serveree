#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>
#include "../Reliable/DataUnit/CMessage.h"

const QString AllPrompts[] = {
    "成功",
    "登录成功",
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
