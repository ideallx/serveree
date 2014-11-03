#ifndef CUSERLISTWIDGET_H
#define CUSERLISTWIDGET_H

#include <QListWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include "../Reliable/DataUnit/CMessage.h"

class CUserListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit CUserListWidget(QWidget *parent = 0);

    void addUser(TS_UINT64 uid, QString username, bool isOnline);

    void removeUser(TS_UINT64 uid);

    TS_UINT64 getUIDByRow(int row) { return userList[row]; }

    void changeAuth(int row);

private:
    QList<TS_UINT64> userList;

signals:

public slots:

};

#endif // CUSERLISTWIDGET_H
