#include <QTest>
#include <QTimer>
#include "../common.h"
#include "tst_cagentserver.h"

tst_CAgentServer::tst_CAgentServer() {

}

void tst_CAgentServer::initTestCase() {
    msg = new ts_msg();
    test = new CAgentServer();
    sequence = 1;
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    test->Start(2222);

    client = new CClientNet();
    client->SetServerAddr(0, "192.168.1.202", 2222);
    client->Start(0);

    QVERIFY(test != NULL);

}

void tst_CAgentServer::cleanupTestCase() {
    test->Stop();
    delete msg;
    delete test;

    client->Stop();
    delete client;

}

void tst_CAgentServer::init() {

}

void tst_CAgentServer::cleanup() {

}

void tst_CAgentServer::enterclass() {
    buildMessage(1111, ENTERCLASS);

    TS_PEER_MESSAGE p;
    client->ReadIn(p);
}

void tst_CAgentServer::leaveclass() {

}

void tst_CAgentServer::createclass() {

}

void tst_CAgentServer::destroyclass() {

}

void tst_CAgentServer::heartbeat() {

}

void tst_CAgentServer::buildMessage(TS_UINT64 uid, int type) {
    TS_PEER_MESSAGE pmsg;
    UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) msg;
    up->classid = 10000;
    up->head.size = sizeof(UP_AGENTSERVICE);
    up->head.time = getServerTime();
    up->head.type = type;
    up->head.UID = uid;
    up->role = RoleTeacher;
    char* username = "abcdefg";
    char* password = "hijklmn";
    memcpy(up->username, username, 20);
    memcpy(up->password, password, 20);
	
    pmsg.msg = *msg;
    client->WriteOut(pmsg);
}


