#include "testserver.h"

TestServer::TestServer(TS_UINT64 uid) :
    uid(uid) {
    conn = static_cast<CReliableConnection*> (pConnect);
    conn->setUID(uid);
}

void TestServer::sendProc() {
    TS_PEER_MESSAGE pmsg;
    memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

    while (isRunning()) {
        ReadOut(pmsg);
        conn->send(pmsg.msg.Body, sizeof(ts_msg));
        allSent.insert(getSeq(pmsg.msg));
        sent.append(pmsg.msg);
    }
}

void TestServer::recvProc() {
    ULONG msglen = sizeof(ts_msg);
    TS_PEER_MESSAGE pmsg;
    memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

    while (isRunning()) {
        if (conn->recv(pmsg.msg.Body, msglen) > 0) {
            memcpy(&pmsg.peeraddr, conn->getRecvAddr(), sizeof(struct sockaddr_in));
            WriteIn(pmsg);
            allReceived.insert(getSeq(pmsg.msg));
            recved.append(pmsg.msg);
        }
    }
#ifdef _DEBUG_INFO_
    cout << "recv thread exit" << endl;
#endif
}
