#include <QDebug>
#include <QTextCodec>
#include <QListWidgetItem>
#include "cuserlistwidget.h"

const int OnlineList = 4;
const int OfflineList = 5;

CUserListWidget::CUserListWidget(QWidget *parent) :
    QListWidget(parent) {
    init();

    setIconSize(QSize(36, 36));

    connect(this, &CUserListWidget::changeIcon,
            this, &CUserListWidget::setRowIcon);
}

void CUserListWidget::init() {
    userList.clear();
    clear();
    userList.append(OnlineList);
    userList.append(OfflineList);

    addItem(QStringLiteral("---在线用户---"));
    addItem(QStringLiteral("---离线用户---"));
}


void CUserListWidget::addUser(TS_UINT64 uid, QString username, bool isOnline) {
    int offlineRow = userList.indexOf(OfflineList);
    int userRow = userList.indexOf(uid);

    if (userRow > 0) {                              // list contain user
        if ((userRow < offlineRow) ^ isOnline) {    // Offline User Online or OnlineUser offline
            userList.removeAt(userRow);
            takeItem(userRow);
        } else {
            return;
        }
    }
    if (isOnline) {
        userList.insert(1, uid);
        insertItem(1, username);
    } else {
        userList.insert(offlineRow + 1, uid);
        insertItem(offlineRow + 1, username);
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

bool CUserListWidget::changeAuth(int row) {
    if (userList[row] == OnlineList ||
            userList[row] == OfflineList) {
        return true;
    }
    if (item(row)->icon().isNull()) {
        emit changeIcon(row, ":/icon/ui/icon/pencil.png");
        return true;
    } else {
        emit changeIcon(row, "");
        return false;
    }
}

bool CUserListWidget::changeAuth(int row, bool writeable) {
    if (userList[row] == OnlineList ||
            userList[row] == OfflineList) {
        return true;
    }

    if (writeable) {
        emit changeIcon(row, ":/icon/ui/icon/pencil.png");
        return true;
    } else {
        emit changeIcon(row, "");
        return false;
    }
}

bool CUserListWidget::changeAuth(TS_UINT64 uid, bool writeable) {
    int row = userList.indexOf(uid);
    return changeAuth(row, writeable);
}

bool CUserListWidget::isOffline(TS_UINT64 uid) {
    if (userList.indexOf(uid) > userList.indexOf(OfflineList)) {
        return true;
    } else {
        return false;
    }
}

void CUserListWidget::setRowIcon(int row, QString file) {
    item(row)->setIcon(QIcon(file));
}

QString CUserListWidget::getUserName(TS_UINT64 uid) {
    int row = userList.indexOf(uid);
    if (-1 == row)
        return QString();
    return item(row)->text();
}
