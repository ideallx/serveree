#ifndef CPROMPTFRAME_H
#define CPROMPTFRAME_H

#include <QMessageBox>
#include <QString>
#include <QObject>

const QString AllPrompts[] = {
    QObject::tr("success"),
    QObject::tr("login success"),
    QObject::tr("logout success"),
    QObject::tr("already logged in"),
    QObject::tr("username error"),
    QObject::tr("password error"),
    QObject::tr("unknown error")
};

class CPromptFrame
{
public:
    CPromptFrame();

    static void prompt(int result, QWidget* parent = 0);
};

#endif // CPROMPTFRAME_H
