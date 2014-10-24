#ifndef TST_CSERVER_H
#define TST_CSERVER_H

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../QtClassClient/Reliable/Server/CServer.h"
#include "../TestClass/testserver.h"
#include <QObject>

class tst_CServer : public QObject
{
    Q_OBJECT
public:
    tst_CServer();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void workserver();
    void run1ClientEasy();
    void run1ClientHard();
    void run2ClientHard();
    void run5ClientEasy();
    void run5ClientHard();

    /*
    void run10ClientNightmare();
    */

private:
    void generateClient();
    void generateServer();
    void sendMessage(TestServer* ts, int times);

private:
    TestServer* server;
    QList<TestServer*> clientList;

	sockaddr_in serverAddr;
	sockaddr_in clientAddr;

    unsigned short clientPort;
    TS_UINT64 clientUID;
    ts_msg* msg;
};

#endif // TST_CSERVER_H
