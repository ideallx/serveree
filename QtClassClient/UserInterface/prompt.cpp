#include "prompt.h"
#include "ui_prompt.h"
#include <QTextCodec>

Prompt::Prompt(WORD index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt)
{
    ui->setupUi(this);

    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    ui->lbPrompt->setText(codec->toUnicode(AllPrompts[index]));
    setWindowFlags(Qt::FramelessWindowHint);

    setModal(true);
    setWindowModality(Qt::WindowModal);
}

Prompt::Prompt(QString prompt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt) {
    ui->setupUi(this);

    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    ui->lbPrompt->setText(codec->toUnicode(prompt.toLatin1()));
    setWindowFlags(Qt::FramelessWindowHint);

    setModal(true);
    setWindowModality(Qt::WindowModal);
}

Prompt::~Prompt()
{
    delete ui;
}
