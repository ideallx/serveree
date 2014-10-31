#include "cpromptframe.h"
#include <QMessageBox>

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    QMessageBox *box = new QMessageBox(parent);
    box->setText(QStringLiteral("�ɹ�"));
    box->setFont(QFont(box->font().family(), 16));
    box->setWindowFlags(Qt::FramelessWindowHint);
    box->setStyleSheet("width: 200px;"
                       "height: 100px;"
                       "background-color: white;"
                       "color: red;"
                       "QPushButton { color: black; }"
                       );
    box->show();
}
