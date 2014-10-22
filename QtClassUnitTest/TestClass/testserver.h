#ifndef _TESTSERVER_H_
#define _TESTSERVER_H_

#include <QSet>
#include <QList>
#include "../QtClassClient/Reliable/Server/CServer.h"
#include "../QtClassClient/Reliable/Connections/CReliableConnection.h"

class TestServer : public CServer {
public:
    TestServer(TS_UINT64 uid);

    void sendProc();

    void recvProc();

    inline int getMissingNum() { return conn->getCurrentMissingNum(); }

    inline TS_UINT64 getMaxSeq(TS_UINT64 uid) { return conn->maxSeq(uid); }

    QSet<TS_UINT64> allReceived;
    QSet<TS_UINT64> allSent;

    QList<ts_msg> recved;
    QList<ts_msg> sent;

    TS_UINT64 uid;

    inline void addPeer(TS_UINT64 uid, sockaddr_in addr) { conn->addPeer(uid, addr); }

private:
    CReliableConnection* conn;
};

#endif
