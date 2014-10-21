#include <QTest>
#include "tst_cblockmanager.h"
#include "../common.h"

tst_CBlockManager::tst_CBlockManager()
{

}

void tst_CBlockManager::initTestCase()
{

}

void tst_CBlockManager::cleanupTestCase()
{

}

void tst_CBlockManager::init() {
    msg = new ts_msg();
    test = new CBlockManager();
    sequence = 1;
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    QVERIFY(test != NULL);
}

void tst_CBlockManager::cleanup() {
    delete msg;
    delete test;
}

void tst_CBlockManager::testRecord() {
    for (int i = 0; i < 10240; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->record(*msg) > 0);
    }
}

void tst_CBlockManager::testRecord2() {
    sequence = 30000;
    for (int i = 0; i < 10240; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->record(*msg) > 0);
    }

}

void tst_CBlockManager::testMemoryBlock() {
    for (int i = 0; i < 10240; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->record(*msg) > 0);
    }
}
