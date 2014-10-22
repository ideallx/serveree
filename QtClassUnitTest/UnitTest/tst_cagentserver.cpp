#include <QTest>
#include <QTimer>
#include "../common.h"
#include "tst_cagentserver.h"

tst_CAgentServer::tst_CAgentServer() {

}

void tst_CAgentServer::initTestCase() {
    clientUID = 11223344;
    clientPort = 4444;

}

void tst_CAgentServer::cleanupTestCase() {


}

void tst_CAgentServer::init() {
    generateServer();
    generateClient();


    msg = new ts_msg();
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    sequence = 1;
}

void tst_CAgentServer::cleanup() {
    delete msg;
    delete server;
    foreach (TestServer* client, clientList) {
        delete client;
    }
    clientList.clear();

    Sleep(100);
}

void tst_CAgentServer::generateClient() {
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("192.168.1.202");
    clientAddr.sin_port = htons(clientPort + clientList.size());

    TestServer* client = new TestServer(clientUID + clientList.size());
    client->Start(clientPort + clientList.size());

    QCOMPARE(client->allReceived.size(), 0);
    QCOMPARE(client->allSent.size(), 0);

    client->addPeer(ServerUID, serverAddr);

    clientList.append(client);
}

void tst_CAgentServer::generateServer() {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.202");
    serverAddr.sin_port = htons(2222);

    server = new CAgentServer();
    server->Start(2222);
}


void tst_CAgentServer::enterclass() {
    buildMessage(clientList[0], ENTERCLASS);
    Sleep(10);

    QCOMPARE(clientList[0]->recved.size(), 1);
}

void tst_CAgentServer::leaveclass() {

}

void tst_CAgentServer::createclass() {

}

void tst_CAgentServer::destroyclass() {

}

void tst_CAgentServer::heartbeat() {

}

void tst_CAgentServer::buildMessage(TestServer* ts, int type) {
    TS_PEER_MESSAGE pmsg;
    UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) msg;
    up->classid = 10000;
    up->head.size = sizeof(UP_AGENTSERVICE);
    up->head.time = getServerTime();
    up->head.type = type;
    up->head.UID = ts->uid;
    up->role = RoleTeacher;
    char* username = "abcdefg";
    char* password = "hijklmn";
    memcpy(up->username, username, 20);
    memcpy(up->password, password, 20);
	
    pmsg.msg = *msg;

    ts->WriteOut(pmsg);
}


