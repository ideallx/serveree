#include <QDebug>
#include "cuserlistwidget.h"

CUserListWidget::CUserListWidget(QWidget *parent) :
    QListWidget(parent) {
}

void CUserListWidget::addUser(TS_UINT64 uid, QString username) {
    userList.append(uid);
    addItem(username);
}

void CUserListWidget::removeUser(TS_UINT64 uid) {
    int row = userList.indexOf(uid);
    takeItem(row);
    userList.removeAt(row);
}
