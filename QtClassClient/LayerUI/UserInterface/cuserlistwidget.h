#ifndef CUSERLISTWIDGET_H
#define CUSERLISTWIDGET_H

#include <QListWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include "../../Reliable/DataUnit/CMessage.h"
#include "../../BizLogic/datasingleton.h"

#include "kineticlistwidget.h"

class CUserListWidget : public KineticListWidget
{
    Q_OBJECT
public:
    explicit CUserListWidget(QWidget *parent = 0);

    void addUser(TS_UINT64 uid, QString username, bool isOnline);

    void removeUser(TS_UINT64 uid);

    TS_UINT64 getUIDByRow(int row) { return userList[row]; }

    bool changeAuth(int row);
    bool changeAuth(int row, bool writeable);

    bool changeAuth(TS_UINT64 uid, bool writeable);

    void init();
    QString getUserName(TS_UINT64 uid);

    void updateUserInfo();

private:
    QList<TS_UINT64> userList;
    DataSingleton* ds;


private:
    bool isOffline(TS_UINT64 uid);

public slots:
    void setRowIcon(int row, QString file);

signals:
    void changeIcon(int row, QString file);

};

#endif // CUSERLISTWIDGET_H
