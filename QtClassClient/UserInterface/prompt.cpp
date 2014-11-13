#include "prompt.h"
#include "ui_prompt.h"
#include <QTextCodec>
#include <QDebug>

Prompt::Prompt(WORD index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt)
{
    ui->setupUi(this);

    ui->lbPrompt->setText(QString::fromLocal8Bit(AllPrompts[index]));
    setWindowFlags(Qt::FramelessWindowHint);

    setModal(true);
    setWindowModality(Qt::WindowModal);
}

Prompt::Prompt(QString prompt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt) {
    ui->setupUi(this);

    ui->lbPrompt->setText(prompt);
    setWindowFlags(Qt::FramelessWindowHint);

    setModal(true);
    setWindowModality(Qt::WindowModal);
}

Prompt::~Prompt()
{
    delete ui;
}
