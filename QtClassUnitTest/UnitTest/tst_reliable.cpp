#include <QTest>
#include "tst_reliable.h"
#include "../common.h"

tst_Reliable::tst_Reliable()
{

}

void tst_Reliable::initTestCase()
{
}

void tst_Reliable::cleanupTestCase()
{
}

void tst_Reliable::init() {
    msg = new ts_msg();
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    sequence = 1;

    server = new CReliableConnection;
    server->setUID(ServerUID);
    server->create(2222);

    client = new CReliableConnection();
    client->setUID(12342234);
    client->create(3320);

    sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = inet_addr("192.168.1.202");
    sock.sin_port = htons(2222);

    client->addPeer(ServerUID, sock);
	
	sock.sin_port = htons(3320);
	server->addPeer(12342234, sock);
}

void tst_Reliable::cleanup() {
    delete msg;
    delete server;
    delete client;
}

void tst_Reliable::connection() {
	QVERIFY(client->isWorking());
	QVERIFY(server->isWorking());
}

void tst_Reliable::recv() {
    for (int i = 0; i < 10240; i++) {
        generateNormalMsg(*msg);
        QVERIFY(client->send(msg->Body, packetSize(*msg)) > 0);

        ULONG size = sizeof(ts_msg);
        QVERIFY(server->recv(msg->Body, size) > 0);
    }
}

void tst_Reliable::missingRate() {
	for (int i = 0; i < 1024; i++) {
		if (i % 10 == 0) {
			sequence++;
			continue;
		}

		generateNormalMsg(*msg);
		QVERIFY(client->send(msg->Body, packetSize(*msg)) > 0);

		ULONG size = sizeof(ts_msg);
		QVERIFY(server->recv(msg->Body, size) > 0);

	}
	Sleep(200);
    QVERIFY(server->getMissingRate() >= 100);
}

void tst_Reliable::resendFragment() {
//    int total = 1024;
//    ULONG size = sizeof(ts_msg);

//    for (int i = 0; i < total; i++) {
//        generateNormalMsg(*msg);
//        if (i % 100 != 0) {
//            QVERIFY(client->send(msg->Body, packetSize(*msg)) > 0);
//            QVERIFY(server->recv(msg->Body, size) > 0);
//        } else {
//            QVERIFY(client->send(msg->Body, packetSize(*msg), 3345) < 0);
//        }
//    }
}
