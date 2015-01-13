#include <QFile>
#include <QDir>
#include "dialogchoosereplay.h"
#include "ui_dialogchoosereplay.h"

#include <QDebug>
DialogChooseReplay::DialogChooseReplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogChooseReplay)
    , sm(new QSignalMapper)
{
    ui->setupUi(this);
    QList<QString> addedList;

    allButton[0] = ui->toolButton;
    allButton[1] = ui->toolButton2;
    allButton[2] = ui->toolButton3;
    allButton[3] = ui->toolButton4;
    allButton[4] = ui->toolButton5;
    allButton[5] = ui->toolButton6;
    allButton[6] = ui->toolButton7;
    allButton[7] = ui->toolButton8;
    allButton[8] = ui->toolButton9;
    allButton[9] = ui->toolButton10;
    allButton[10] = ui->toolButton11;
    allButton[11] = ui->toolButton12;
    allButton[12] = ui->toolButton13;
    allButton[13] = ui->toolButton14;
    allButton[14] = ui->toolButton15;
    allButton[15] = ui->toolButton16;
    allButton[16] = ui->toolButton17;
    allButton[17] = ui->toolButton18;
    allButton[18] = ui->toolButton19;
    allButton[19] = ui->toolButton20;

    int buttonid = 0;
    QStringList nameFilter;
    nameFilter << "20??_????_????_??";
    foreach (QString filename, QDir::current().entryList(nameFilter, QDir::Dirs)) {
        qDebug() << "filtered filename" << filename;
        if (buttonid > 19)
            break;
        if (addedList.contains(filename))
            continue;
        allButton[buttonid]->setText(filename);
        //ui->listWidget->addItem(filename);
        addedList.append(filename);
        buttonid++;
    }

    for (int i = 0; i < buttonid; i++) {
        connect(allButton[i], SIGNAL(clicked()),
                sm, SLOT(map()));
        sm->setMapping(allButton[i], allButton[i]->text());
    }

    connect(sm, SIGNAL(mapped(QString)),
            this, SLOT(clickButton(QString)));



    setWindowFlags(Qt::FramelessWindowHint);
}

DialogChooseReplay::~DialogChooseReplay()
{
    delete ui;
    delete sm;
}

void DialogChooseReplay::takeBack() {
    emit goBack();
    done(0);
}

void DialogChooseReplay::on_tbBack_clicked()
{
    takeBack();
}

void DialogChooseReplay::on_tbExit_clicked()
{
    takeBack();
}

void DialogChooseReplay::clickButton(QString className) {
    emit classChosen(className);
    done(0);
}
