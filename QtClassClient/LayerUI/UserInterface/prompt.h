#ifndef PROMPT_H
#define PROMPT_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QDialog>

namespace Ui {
class Prompt;
}


const QByteArray AllPrompts[] = {
    "�ɹ�",
    "��¼�ɹ�",
    "�ǳ��ɹ�",
    "�μ����سɹ�",

    "�Ѿ���¼",

    "�û���������",
    "�������",
    "δ֪����",
    "����ʧ��",

    "�ݲ�֧�ָø�ʽ���ļ�",
    "�����ڴ�",
    "������û����Ӧ",
    "�ļ��Ѵ���"
};

class Prompt : public QDialog
{
    Q_OBJECT

public:
    explicit Prompt(WORD index, QWidget *parent = 0);
    explicit Prompt(QString prompt, QWidget *parent = 0);

    ~Prompt();

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
