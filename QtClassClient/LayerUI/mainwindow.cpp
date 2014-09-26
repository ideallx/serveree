#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new MyScene(this, this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);

    connect(ui->actionEnterClass, &QAction::triggered,
            this, &MainWindow::enterClass);
    connect(ui->actionLeaveClass, &QAction::triggered,
            this, &MainWindow::leaveClass);
    connect(ui->actionClearScreen, &QAction::triggered,
            scene, &MyScene::clear);

    connect(ui->buttonEllipse, &QPushButton::clicked,
            this, &MainWindow::changeTypeEllipse);
    connect(ui->buttonRect, &QPushButton::clicked,
            this, &MainWindow::changeTypeRect);
    connect(ui->buttonLine, &QPushButton::clicked,
            this, &MainWindow::changeTypeLine);
    connect(ui->buttonScripts, &QPushButton::clicked,
            this, &MainWindow::changeTypeScripts);

    ui->buttonScripts->setChecked(true);
    buttons.append(ui->buttonEllipse);
    buttons.append(ui->buttonLine);
    buttons.append(ui->buttonRect);
    buttons.append(ui->buttonScripts);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote) {
    if (!isRemote) {
        sendToAll(msg, wParam, lParam, false);
    } else {
		TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
        if (wParam == 1) {
            scene->actMoveBegin(*gmsg);
        }  else {
			scene->actMove(*gmsg);
		}
	}
}

void MainWindow::enterClass() {
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

void MainWindow::buttonsUnchecked() {
    foreach (QPushButton* pb, buttons) {
        pb->setChecked(false);
    }
}

void MainWindow::changeTypeEllipse() {
    buttonsUnchecked();
    static_cast<QPushButton*> (sender())->setChecked(true);
    scene->changeType(ELLIPSE);
}

void MainWindow::changeTypeRect() {
    buttonsUnchecked();
    static_cast<QPushButton*> (sender())->setChecked(true);
    scene->changeType(RECTANGLE);

}

void MainWindow::changeTypeScripts() {
    buttonsUnchecked();
    static_cast<QPushButton*> (sender())->setChecked(true);
    scene->changeType(SCRIPTS);
}

void MainWindow::changeTypeLine() {
    buttonsUnchecked();
    static_cast<QPushButton*> (sender())->setChecked(true);
    scene->changeType(LINE);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    scene->setPenWidth(arg1);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    scene->setPenColor(arg1);
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    scene->setBrushColor(arg1);
}
