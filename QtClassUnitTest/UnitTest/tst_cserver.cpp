#include <QTest>
#include "tst_cserver.h"
#include "../common.h"

tst_CServer::tst_CServer()
{
}

void tst_CServer::initTestCase()
{
    clientUID = 11223344;
    clientPort = 4444;

}

void tst_CServer::cleanupTestCase()
{

}

void tst_CServer::generateClient() {
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("192.168.1.202");
    clientAddr.sin_port = htons(clientPort + clientList.size());

    TestServer* client = new TestServer(clientUID + clientList.size());
    client->Start(clientPort + clientList.size());

    QCOMPARE(client->allReceived.size(), 0);
    QCOMPARE(client->allSent.size(), 0);

    server->addPeer(clientUID + clientList.size(), clientAddr);
    client->addPeer(ServerUID, serverAddr);

    clientList.append(client);
}

void tst_CServer::generateServer() {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.202");
    serverAddr.sin_port = htons(2222);

    server = new TestServer(ServerUID);
    server->Start(2222);
    QCOMPARE(server->allReceived.size(), 0);
    QCOMPARE(server->allSent.size(), 0);
}

void tst_CServer::sendMessage(TestServer* ts, int times) {
    TS_PEER_MESSAGE pmsg;
    pmsg.peeraddr = serverAddr;
    for (int i = 0; i < times; i++) {
        generateNormalMsg(*msg, ts->uid);
        pmsg.msg = *msg;
        ts->WriteOut(pmsg);
        if (i % 10 == 0)
            Sleep(1);
    }
    Sleep(200);
}

void tst_CServer::init() {
    generateServer();
    generateClient();


    msg = new ts_msg();
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    sequence = 1;
}

void tst_CServer::cleanup() {
    delete msg;
    delete server;
    foreach (TestServer* client, clientList) {
        delete client;
    }
    clientList.clear();

    Sleep(100);
}

// so simple client send 1 message and server receive it
void tst_CServer::run1ClientEasy() {
    int total = 1500;
    TestServer* client = clientList[0];
    sendMessage(client, total);

    QCOMPARE(server->getMaxSeq(clientUID), (TS_UINT64) server->allReceived.size());
    QCOMPARE(server->allReceived.size(), total);
}

void tst_CServer::run1ClientHard() {
    int total = 15000;
    TestServer* client = clientList[0];
    sendMessage(client, total);

    QCOMPARE(server->getMaxSeq(clientUID), (TS_UINT64) server->allReceived.size());
    QCOMPARE(server->allReceived.size(), total);
}

void tst_CServer::run2ClientHard() {
    int total = 15000;
    generateClient();

    TestServer* sendClient = clientList[0];
    TestServer* recvClient = clientList[1];

    sendMessage(sendClient, total);

    QCOMPARE(recvClient->getMaxSeq(sendClient->uid), (TS_UINT64) recvClient->allReceived.size());
    QCOMPARE(recvClient->allReceived.size(), total);
}


void tst_CServer::run5ClientEasy() {
    int total = 500;
    int userNum = 5;

    for (int i = 0; i < userNum; i++)
        generateClient();

    for (int j = 0; j < userNum; j++) {
        sendMessage(clientList[j], total);
    }
    QCOMPARE(clientList[2]->allReceived.size(), total * 4);
}


void tst_CServer::run5ClientHard() {
    int total = 15000;

    int userNum = 5;
    for (int i = 0; i < userNum; i++)
        generateClient();

    for (int j = 0; j < userNum; j++) {
        sendMessage(clientList[j], total);
    }
    QCOMPARE(clientList[2]->allReceived.size(), total * (userNum - 1));
}

/*
void tst_CServer::run10ClientNightmare() {
    int total = 15000;

    int userNum = 10;
    for (int i = 0; i < userNum; i++)
        generateClient();

    for (int j = 0; j < userNum; j++) {
        sendMessage(clientList[j], total);
    }
    QCOMPARE(clientList[2]->allReceived.size(), total * (userNum - 1));
}
*/

