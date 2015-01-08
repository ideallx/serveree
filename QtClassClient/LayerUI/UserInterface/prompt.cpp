#include "prompt.h"
#include "ui_prompt.h"
#include <QDebug>

Prompt::Prompt(WORD index, WORD controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt) {
    ui->setupUi(this);

    changeLayout(controller);
    ui->lbPrompt->setText(QString::fromLocal8Bit(AllPrompts[index]));
    setWindowFlags(Qt::FramelessWindowHint);
}

Prompt::Prompt(QString prompt, WORD controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prompt) {
    ui->setupUi(this);

    changeLayout(controller);
    ui->lbPrompt->setText(prompt);
    setWindowFlags(Qt::FramelessWindowHint);
}

void Prompt::changeLayout(WORD controller) {
    if (controller & PromptControllerConfirm)
        ui->pbConfirm->setVisible(true);
    else
        ui->pbConfirm->setVisible(false);

    if (controller & PromptControllerCancel)
        ui->pbCancel->setVisible(true);
    else
        ui->pbCancel->setVisible(false);

    if (controller & PromptControllerProgressBar) {
        ui->progressBar->setVisible(true);
        connect(this, &Prompt::progressChanged,
                ui->progressBar, &QProgressBar::setValue);
    } else
        ui->progressBar->setVisible(false);
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

void Prompt::setProgress(int v) {
    if (v >= 0 && v <= 100)
        emit progressChanged(v);
}

Prompt::~Prompt()
{
    delete ui;
}

void Prompt::on_pbConfirm_clicked()
{
    accept();
}

void Prompt::on_pbCancel_clicked()
{
    reject();
}
