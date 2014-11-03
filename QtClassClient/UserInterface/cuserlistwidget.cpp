#include <QDebug>
#include <QListWidgetItem>
#include "cuserlistwidget.h"

const int OnlineList = 4;
const int OfflineList = 5;

CUserListWidget::CUserListWidget(QWidget *parent) :
    QListWidget(parent) {
    userList.append(OnlineList);
    userList.append(OfflineList);
    setIconSize(QSize(36, 36));
}


void CUserListWidget::addUser(TS_UINT64 uid, QString username, bool isOnline) {
    if (isOnline) {
        if (userList.contains(uid)) {
            userList.removeOne(uid);
        }
        userList.insert(1, uid);
        insertItem(1, username);
    } else {
        if (userList.contains(uid)) {
            userList.removeOne(uid);
        }
        userList.insert(count(), uid);
        insertItem(count(), username);
    }
}

void CUserListWidget::removeUser(TS_UINT64 uid) {
    int row = userList.indexOf(uid);
    QString username = item(row)->text();
    takeItem(row);
    userList.removeAt(row);

    userList.insert(count(), uid);
    insertItem(count(), username);
}

void CUserListWidget::changeAuth(int row) {
    if (userList[row] == OnlineList ||
            userList[row] == OfflineList) {
        return;
    }
    if (item(row)->icon().isNull())
        item(row)->setIcon(QIcon(":/icon/ui/icon/pencil.png"));
    else
        item(row)->setIcon(QIcon());
}
