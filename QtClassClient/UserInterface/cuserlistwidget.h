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

    void addUser(TS_UINT64 uid, QByteArray username, bool isOnline);

    void removeUser(TS_UINT64 uid);

    TS_UINT64 getUIDByRow(int row) { return userList[row]; }

    bool changeAuth(int row);
    bool changeAuth(int row, bool writeable);

    bool changeAuth(TS_UINT64 uid, bool writeable);

    void init();

private:
    QList<TS_UINT64> userList;

    bool isOffline(TS_UINT64 uid);

public slots:
    void setRowIcon(int row, QString file);

signals:
    void changeIcon(int row, QString file);

};

#endif // CUSERLISTWIDGET_H
