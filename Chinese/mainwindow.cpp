#include <QDebug>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QByteArray AllPrompts[] = {
    "�ɹ�",
    "��¼�ɹ�",
    "�ǳ��ɹ�",
    "�μ����سɹ�",

    "�Ѿ���¼",

    "�û�������",
    "�������",
    "δ֪����",
    "����ʧ��",

    "�ݲ�֧�ָø�ʽ���ļ�",
    "�����ڴ�",
    "������û����Ӧ",
    "�ļ��Ѵ���"
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str;
    str = QString::fromLocal8Bit("������");
    qDebug() << str;

//    tr = QFileDialog::getOpenFileName();
    qDebug() << QString::fromLocal8Bit(AllPrompts[2]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
