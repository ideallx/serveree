#include <QtTest>
#include "tst_cblock.h"
#include "../common.h"

tst_CBlock::tst_CBlock() {

}

void tst_CBlock::initTestCase() {

}

void tst_CBlock::cleanupTestCase() {

}

void tst_CBlock::init() {
    test = new CBlock(121212);
    msg = new ts_msg();
    sequence = 1;
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    QVERIFY(test != NULL);
}

void tst_CBlock::cleanup() {
    delete test;
    delete msg;
}

void tst_CBlock::testAddMsg1() {
    test->setFilePrefix("aaaa");
    int total = 5000;
    for (int i = 0; i < total; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->addMsg(*msg) > 0);
    }
}

void tst_CBlock::testReadMsg() {
    for (int i = 0; i < 3000; i++) {
        generateNormalMsg(*msg);
        Sleep(1);
        QVERIFY(test->addMsg(*msg) > 0);
    }

    for (int i = 200; i < 2000; i += 400) {
        QVERIFY(test->readMsg(i, *msg) > 0);
        QVERIFY(getSeq(*msg) == i);
    }
}

void tst_CBlock::testScanMissing() {
    int interval = 36;
    int total = 2000;

    for (int i = 0; i < total; i++) {		// 模拟丢包
        if (i % interval == 0) {			// 随便一个数的倍数全丢了
            sequence++;
            continue;
        }
        generateNormalMsg(*msg);
        QVERIFY(test->addMsg(*msg) > 0);
    }

    set<TS_UINT64> missed = test->scanMissingPackets();
    for (int i = 1 + interval; i < total; i += interval)	// 第一号被跳过了。因为第一次就是continue
        QVERIFY(missed.count(i) != 0);
}
