#ifndef TST_CAGENTSERVER_H
#define TST_CAGENTSERVER_H

#include <QObject>
#include "../QtClassClient/Reliable/Server/CAgentServer.h"
#include "../QtClassClient/BizLogic/CBusinessLogic.h"
#include "../QtClassClient/Net/CClientNet.h"
#include "../TestClass/testserver.h"

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

    void halfwayUser();

private:
    void generateClient();
    void generateServer();

    void normalEnterClass(int userseq, int messSeq);
    void normalLeaveClass(int userseq, int messSeq);

    void buildMessage(TestServer *ts, int type);

    CAgentServer* server;
    QList<TestServer*> clientList;

    sockaddr_in serverAddr;
    sockaddr_in clientAddr;

    unsigned short clientPort;
    TS_UINT64 clientUID;
    ts_msg* msg;
};

#endif // TST_CAGENTSERVER_H
