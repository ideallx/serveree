#ifndef PROMPT_H
#define PROMPT_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QDialog>

namespace Ui {
class Prompt;
}


enum PromptController {
    PromptControllerConfirm         = 1,
    PromptControllerCancel          = 2,
    PromptControllerProgressBar     = 4,
};


const QByteArray AllPrompts[] = {
    "�ɹ�",
    "��¼�ɹ�",
    "�ǳ��ɹ�",
    "�μ����سɹ�",

    "�Ѿ���¼",
    "�����˺����ڱ𴦵�¼�����Ժ�����",

    "�û���������",
    "�������",
    "δ֪����",
    "�ÿ��ò�����",
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
    explicit Prompt(WORD index, WORD controller, QWidget *parent = 0);
    explicit Prompt(QString prompt, WORD controller, QWidget *parent = 0);

    void setPrompt(int result);
    void setPrompt(QString prompt);

    static QString getPrompt(int index);

    void setProgress(int);


    ~Prompt();

signals:
    void progressChanged(int value);

private slots:
    void on_pbConfirm_clicked();

    void on_pbCancel_clicked();


private:
    void changeLayout(WORD controller);

private:
    static bool isExist;
    Ui::Prompt *ui;
};

#endif // PROMPT_H
