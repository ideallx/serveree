#include "dialogstatisticdetail.h"
#include "ui_dialogstatisticdetail.h"

#include "cquestionlogicmodule.h"

const int MaxColumn = 3;

DialogStatisticDetail::DialogStatisticDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStatisticDetail)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(MaxColumn * 2);

    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setShowGrid(false);
}

DialogStatisticDetail::~DialogStatisticDetail()
{
    delete ui;
}

void DialogStatisticDetail::on_tbDialogExit_clicked()
{
    done(0);
}

void DialogStatisticDetail::setTitle(const QString title) {
    ui->lbDialogTitle->setText(title);
}


// keys are arranged like this
// k1  xx  k2   xx
// k3  xx  k4  xx
void DialogStatisticDetail::setKeys(QVector<QString> keys) {
    int i = 0;
    int column = 0;
    ui->tableWidget->setRowCount((keys.size() + MaxColumn - 1) / MaxColumn);
    for (auto iter = keys.begin(); iter != keys.end(); ++iter) {
        QTableWidgetItem* item = new QTableWidgetItem(*iter);
        ui->tableWidget->setItem(i, column, item);
        if (column == MaxColumn * 2 - 2) {
            column = 0;
            i++;
        } else {
            column += 2;
        }
    }
}

// values are arranged like this
// xx  v1  xx  v2
// xx  v3  xx  v4

void DialogStatisticDetail::setValues(QVector<WORD> values) {
    int i = 0;
    int column = 1;
    ui->tableWidget->setRowCount((values.size() + MaxColumn - 1) / MaxColumn);
    for (auto iter = values.begin(); iter != values.end(); ++iter) {
        QString filePath;
        if (*iter == ScoreCorrect) {
            filePath = ":/icon/ui/icon/blockcorrect.png";
        } else if (*iter == ScoreUncorrect) {
            filePath = ":/icon/ui/icon/blockwrong.png";
        } else {
            filePath = ":/icon/ui/icon/blockblank.png";
        }
        QTableWidgetItem* item = new QTableWidgetItem(QIcon(filePath), "");
        ui->tableWidget->setItem(i, column, item);
        if (column == MaxColumn * 2 - 1) {
            column = 1;
            i++;
        } else {
            column += 2;
        }
    }
}
