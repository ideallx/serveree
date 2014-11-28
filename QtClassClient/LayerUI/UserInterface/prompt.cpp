#include "prompt.h"
#include "ui_prompt.h"
#include <QTextCodec>
#include <QDebug>

Prompt::Prompt(WORD index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt) {
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

void Prompt::setPrompt(int result) {
    ui->lbPrompt->setText(ui->lbPrompt->text() + "\n" +
                          QString::fromLocal8Bit(AllPrompts[result]));
    ui->pbConfirm->setEnabled(true);
}

void Prompt::setPrompt(QString prompt) {
    ui->lbPrompt->setText(ui->lbPrompt->text() + "\n" + prompt);
    ui->pbConfirm->setEnabled(true);
}

QString Prompt::getPrompt(int index) {
    return QString::fromLocal8Bit(AllPrompts[index]);
}

Prompt::~Prompt()
{
    delete ui;
}

void Prompt::on_pbConfirm_clicked()
{
    accept();
}
