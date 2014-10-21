#ifndef TST_CAGENTSERVER_H
#define TST_CAGENTSERVER_H

#include <QObject>
#include "../QtClassClient/Reliable/Server/CAgentServer.h"
#include "../QtClassClient/Net/CClientNet.h"

class tst_CAgentServer : public QObject
{
    Q_OBJECT
public:
    tst_CAgentServer();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void enterclass();
    void leaveclass();
    void createclass();
    void destroyclass();
    void heartbeat();

//    void getOfflineUsers();
//    void userLoginNotify();
//    void userLogoutNotify();
//    void getServerByUID();

private:
    void buildMessage(TS_UINT64 uid, int type);

    CAgentServer* test;
    CClientNet* client;
    ts_msg* msg;
};

#endif // TST_CAGENTSERVER_H
