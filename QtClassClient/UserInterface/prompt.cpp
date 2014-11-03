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

//    switch (result) {
//    case Success:
//        ui->lbPrompt->setText(QStringLiteral("��¼�ɹ�"));
//        break;

//    case ErrorUsername:
//        ui->lbPrompt->setText(QStringLiteral("�û�������"));
//        break;
//    }

    this->setWindowFlags(Qt::FramelessWindowHint);
}

Prompt::~Prompt()
{
    delete ui;
}
