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
    test = new CReliableConnection();
    msg = new ts_msg();
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    sequence = 1;

    QVERIFY(test != NULL);
}

void tst_Reliable::cleanup() {
    delete msg;
    delete test;
}

void tst_Reliable::testRecv() {
    for (int j = 0; j < 10; j++) {
//        for (int i = 0; i < 10240; i++) {
//            generateNormalMsg(*msg);
//            test->msgQueue->enQueue(*msg);
//            sem_post((sem_t*) &test->semMsg);
//        }
//        cleanup();
//        init();
    }
}
