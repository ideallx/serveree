#include <QHBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "qeclass.h"
#include "../DataUnit/CMessage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    aNewShape(true),
    isRunning(false) {
    ui->setupUi(this);

    scene = new MyScene(this, this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);

    connect(ui->actionEnterClass, &QAction::triggered,
            this, &MainWindow::enterClass);
    connect(ui->actionLeaveClass, &QAction::triggered,
            this, &MainWindow::leaveClass);
    connect(ui->actionClearScreen, &QAction::triggered,
            scene, &MyScene::cls);
    connect(ui->comboxPenWidth, &LineWidthCombox::signalWidthChanged,
            scene, &MyScene::setPenWidth);
    connect(ui->ComboxPenColor, &ColorCombox::sigColorChanged,
            scene, &MyScene::setPenColor);
    connect(ui->ComboxBrushColor, &ColorCombox::sigColorChanged,
            scene, &MyScene::setBrushColor);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            scene, SLOT(changeShapeByUI(int)));

    //setWindowFlags(Qt::FramelessWindowHint);
    setMyPanel();
}

MainWindow::~MainWindow() {
    if (ui->actionLeaveClass->isVisible()) {
        leaveClass();
        Sleep(10);
    }
    delete ui;
}

const int scrollAreaHeight = 200;
void MainWindow::setMyPanel() {
    QHBoxLayout* layout = new QHBoxLayout();

    for (int i = 0; i < 10; i++) {
        QLabel* label1 = new QLabel(this);
        QPixmap pix = QPixmap(QString("D:/%1.jpg").arg(i));
        label1->setPixmap(pix.scaledToHeight(scrollAreaHeight - 20));
        layout->addWidget(label1);
    }

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    ui->scrollArea->setFixedHeight(scrollAreaHeight);
    ui->scrollArea->setWidget(widget);

}

void MainWindow::ProcessMessage(ts_msg& msg, WPARAM event, LPARAM lParam, BOOL isRemote) {
    Q_UNUSED(lParam);
    if (!isRemote) {
        sendToAll(msg, 0, 0, false);
    } else {
        msgQueue.enQueue(msg);
        ReleaseSemaphore(sem_msg, 1, NULL);
	}
}

void MainWindow::enterClass() {
    QEClass e;
    e.setWindowFlags(Qt::FramelessWindowHint);
    e.exec();
    ts_msg msg;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    head->type = ENTERCLASS;
    head->size = sizeof(UP_AGENTSERVICE);

    sendToAll(*(ts_msg*) &msg, 0, 0, false);

}

void MainWindow::leaveClass() {
    ts_msg msg;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    head->type = LEAVECLASS;
    head->size = sizeof(UP_AGENTSERVICE);

    sendToAll(*(ts_msg*) &msg, 0, 0, false);

}

void MainWindow::enterClassResult(bool result) {
    if (result) {
        ui->actionEnterClass->setVisible(false);
        ui->actionLeaveClass->setVisible(true);

        sem_msg = CreateSemaphore(NULL, 0, 1024, NULL);
        isRunning = true;
        int rc = pthread_create(&msgThread, NULL, MsgFFProc, (void*) this);
        if (0 == rc) {
            Sleep(10);
            qDebug() << "enter class successfully";
        } else {
            isRunning = false;
        }
    }
}

void MainWindow::leaveClassResult(bool result) {
    if (result) {
        ui->actionEnterClass->setVisible(true);
        ui->actionLeaveClass->setVisible(false);
        isRunning = false;
        CloseHandle(sem_msg);
        qDebug() << "leave class successfully";
    }
}

void MainWindow::on_actionExit_triggered()
{
    deleteLater();
    qApp->exit(0);
}

void MainWindow::msgProc() {
    ts_msg msg;

    while (isRunning) {
        qDebug() << "draw";
        WaitForSingleObject(sem_msg, INFINITE);
        msgQueue.deQueue(msg);

        TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
        switch (gmsg->graphicsType) {
        case GraphicPacketEndMove:
            aNewShape = true;
            scene->actMove(*gmsg);
            break;
        case GraphicPacketNormal:
            if (aNewShape) {
                scene->actMoveBegin(*gmsg);
                aNewShape = false;
            } else {
                scene->actMove(*gmsg);
            }
            break;
        case GraphicPacketPenBrush:
            scene->setOthersPenBrush(*gmsg);
            break;
        case GraphicPacketCls:
            scene->clear();
            scene->update();
            break;
        default:
            break;
        }
    }
}

void* MsgFFProc(LPVOID lpParam) {
    pthread_detach(pthread_self());
    MainWindow* m = (MainWindow*) lpParam;
    if (NULL == m) {
        return 0;
    }
    m->msgProc();
    return 0;
}
