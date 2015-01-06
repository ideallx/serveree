#include "widgetansweraccountitem.h"
#include "ui_widgetansweraccountitem.h"

const int BlankWidth = 0;
WidgetAnswerAccountItem::WidgetAnswerAccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAnswerAccountItem)
{
    ui->setupUi(this);
}

WidgetAnswerAccountItem::~WidgetAnswerAccountItem()
{
    delete ui;
}

void setLabelText(QLabel* label, int number, int totalNum, int totalWidth) {
    if (0 == number) {
        label->setText(QString::null);
        label->setFixedWidth(BlankWidth);
    } else {
        label->setText(QString::number(number));
        label->setFixedWidth(number * totalWidth / totalNum);
    }
}

#include <QDebug>
void WidgetAnswerAccountItem::setValue(int correct, int wrong, int total) {
    int blank = total - correct - wrong;
    if (correct < 0 || wrong < 0 || blank < 0)  // error check
        return;

    int totalWidth = width() - 110;     // 110 is layout left marine

    if (total == 0) {
        ui->lbCorrect->setText("0");
        ui->lbCorrect->setFixedWidth(totalWidth);
        ui->lbWrong->setFixedWidth(BlankWidth);
        ui->lbBlank->setFixedWidth(BlankWidth);
    } else {
        setLabelText(ui->lbCorrect, correct, total, totalWidth);
        setLabelText(ui->lbWrong, wrong, total, totalWidth);

        if (0 == blank) {
            ui->lbBlank->setText(QString::null);
            ui->lbBlank->setFixedWidth(BlankWidth);
        } else {
            ui->lbBlank->setText(QString::number(blank));
            ui->lbBlank->setFixedWidth(
                        totalWidth - ui->lbCorrect->width() - ui->lbWrong->width());
        }
    }
}
