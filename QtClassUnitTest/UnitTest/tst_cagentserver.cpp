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
    normalEnterClass(0, 0);
}

void tst_CAgentServer::leaveclass() {
    normalEnterClass(0, 0);

    // leave class
    normalLeaveClass(0, 1);
    Sleep(1000);
    QCOMPARE(server->isClassExist(10000), false);

    // leave class which you are not in, still reply leave success
    normalLeaveClass(0, 2);
    QCOMPARE(server->isClassExist(10000), false);
}

void tst_CAgentServer::createclass() {
    normalEnterClass(0, 0);
}

void tst_CAgentServer::destroyclass() {
    // enter class
    normalEnterClass(0, 0);

    // leave class
    normalLeaveClass(0, 1);
    Sleep(1000);
    QCOMPARE(server->isClassExist(10000), false);
}

void tst_CAgentServer::heartbeat() {

}

void tst_CAgentServer::halfwayUser() {
    ts_msg msg;
    normalEnterClass(0, 0);
    sequence = 1;
    for (int i = 0; i < 1000; i++) {
        generateNormalMsg(msg, clientList[0]->uid);
    }

    generateClient();
    normalEnterClass(1, 0);
    sequence = 1;
    for (int i = 0; i < 1000; i++) {
        generateNormalMsg(msg, clientList[1]->uid);
    }


    generateClient();
    normalEnterClass(2, 0);
    sequence = 1;
    for (int i = 0; i < 1000; i++) {
        generateNormalMsg(msg, clientList[2]->uid);
    }

    generateClient();
    normalEnterClass(3, 0);
    Sleep(100);
    QCOMPARE(clientList[3]->recved.size(), 2);
}


void tst_CAgentServer::normalEnterClass(int userseq, int messSeq) {
    buildMessage(clientList[userseq], ENTERCLASS);
    Sleep(100);

    QVERIFY(clientList[userseq]->recved.size() >= messSeq + 1);
    DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &clientList[userseq]->recved[messSeq];
    QCOMPARE((int) down->result, (int) SuccessEnterClass);
    QCOMPARE(server->isClassExist(10000), true);

	// userlist
}

void tst_CAgentServer::normalLeaveClass(int userseq, int messSeq) {
    buildMessage(clientList[userseq], LEAVECLASS);
    Sleep(100);
    QCOMPARE(clientList[userseq]->recved.size(), messSeq + 1);
    DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &clientList[0]->recved[messSeq];
    QCOMPARE((int) down->result, (int) SuccessLeaveClass);
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


