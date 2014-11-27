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
    "�ļ��Ѵ���",

    "�γ�װ����"
};

class Prompt : public QDialog
{
    Q_OBJECT

public:
    explicit Prompt(WORD index, QWidget *parent = 0);
    explicit Prompt(QString prompt, QWidget *parent = 0);

    void setPrompt(int result);
    void setPrompt(QString prompt);

    static QString getPrompt(int index);

    ~Prompt();

private slots:
    void on_pbConfirm_clicked();

private:
    static bool isExist;
    Ui::Prompt *ui;
};

#endif // PROMPT_H
