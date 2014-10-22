#ifndef TST_RELIABLE_H
#define TST_RELIABLE_H

#include <QObject>
#include "../QtClassClient/Reliable/Connections/CReliableConnection.h"

class tst_Reliable : public QObject
{
    Q_OBJECT
public:
    tst_Reliable();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

	void connection();
    void recv();
    void missingRate();
    void resendFragment();

    void init();
    void cleanup();

private:
    CReliableConnection* client;
    CReliableConnection* server;
    ts_msg* msg;
};

#endif // TST_RELIABLE_H
