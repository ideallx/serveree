#include "tst_CPackage.h"
#include "../common.h"

tst_CPackage::tst_CPackage()
{
}

void tst_CPackage::initTestCase()
{
}

void tst_CPackage::cleanupTestCase()
{
}

void tst_CPackage::init() {
    test = new CPackage();
    msg = new ts_msg();
    ((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
    sequence = 1;

    QVERIFY(test != NULL);
    QVERIFY(test->isFull() == false);
}

void tst_CPackage::cleanup() {
    delete msg;
    delete test;
}

void tst_CPackage::testInsert1()
{
    for (int i = 0; i < 1024; i++)
        QVERIFY(test->insert(*msg, i) > 0);

    for (int i = 0; i < 200; i++)
        QVERIFY(test->insert(*msg, rand() % 1030) < 0);	// 此时已满，无论大小应该都加不了
}

void tst_CPackage::testInsert2() {
    for (int i = 0; i < 100; i++)
        QVERIFY(test->insert(*msg, i) > 0);

    for (int i = 500; i < 700; i++)
        QVERIFY(test->insert(*msg, i) > 0);

    for (int i = 552; i < 661; i++)
        QVERIFY(test->insert(*msg, i) < 0);

    for (int i = 1024; i < 1100; i++)
        QVERIFY(test->insert(*msg, i) < 0);
}

void tst_CPackage::testInsert3() {
    for (int i = 1023; i != -1; i--)
        QVERIFY(test->insert(*msg, i) > 0);

    QVERIFY(test->isFull());
}

void tst_CPackage::testQuery1() {
    for (int i = 444; i < 456; i++) {
        QVERIFY(test->query(*msg, i) < 0);
    }
    for (int i = 1024; i < 1222; i++) {
        QVERIFY(test->query(*msg, i) < 0);
    }
    for (int i = -500; i < 0; i++) {
        QVERIFY(test->query(*msg, i) < 0);
    }

    for (int i = 0; i < 1024; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->insert(*msg, i) > 0);
    }

    for (int i = 0; i < 1024; i++) {
        QVERIFY(test->query(*msg, i) > 0);
        TS_UINT64 seq = getSeq(*msg);
        QVERIFY(seq == i + 1);
    }
}

void tst_CPackage::testQuery2() {
    sequence = 1025;
    for (int i = 0; i < 555; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->insert(*msg, i) > 0);
    }

    for (int i = 444; i < 555; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->query(*msg, i) > 0);
        TS_UINT64 seq = getSeq(*msg);
        QVERIFY(seq == i + 1025);
    }

    for (int i = 666; i < 777; i++) {
        QVERIFY(test->query(*msg, i) < 0);
    }
}

void tst_CPackage::testSave() {
    for (int i = 0; i < 1024; i++) {
        generateNormalMsg(*msg);
        QVERIFY(test->insert(*msg, i) > 0);
    }

    QVERIFY(test->save("fff.zip", true));
}

void tst_CPackage::testLoad() {
    QVERIFY(test->load("ggg.zip", 0) == false);

    QVERIFY(test->load("fff.zip", 0) == true);
    for (int i = 0; i < 1024; i++) {
        QVERIFY(test->query(*msg, i) > 0);
        int seq = getSeq(*msg);
        QVERIFY(seq == i+1);
    }
}

void tst_CPackage::testIsExist() {
    for (int i = 333; i < 555; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }

    for (int i = 777; i < 999; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }

    for (int i = -200; i < 2000; i++) {
        if (i < 0) {
            QVERIFY(test->isExist(i) == false);
        } else if (i < 333) {
            QVERIFY(test->isExist(i) == false);
        } else if (i < 555) {
            QVERIFY(test->isExist(i) == true);
        } else if (i < 777) {
            QVERIFY(test->isExist(i) == false);
        } else if (i < 999) {
            QVERIFY(test->isExist(i) == true);
        } else if (i < 1024) {
            QVERIFY(test->isExist(i) == false);
        } else {
            QVERIFY(test->isExist(i) == false);
        }
    }
}

void tst_CPackage::testIsFull1() {
    for (int i = 333; i < 555; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }
    QVERIFY(test->isFull() == false);

    for (int i = 0; i < 1023; i++) {
        test->insert(*msg, i);
    QVERIFY(test->isFull() == false);
    }
    test->insert(*msg, 1023);
    QVERIFY(test->isFull() == true);
    QVERIFY(test->save("erer.zip", true));
    delete test;

    sequence = 1;
    test = new CPackage();
    QVERIFY(test->isFull() == false);
    QVERIFY(test->load("erer.zip", 0) == true);
    QVERIFY(test->isFull() == true);
}

void tst_CPackage::testIsFull2() {
    for (int i = 1023; i != -1; i--)
        QVERIFY(test->insert(*msg, i) > 0);
    QVERIFY(test->isFull() == true);
}

void tst_CPackage::testScanAll() {
    for (int i = 333; i < 555; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }
    set<int> out;
    QVERIFY(test->scanMissingPackets(out) == 333);

    test->needAll();
    QVERIFY(test->scanMissingPackets(out) == 1024-222);
}

void tst_CPackage::testScanMissingPackets() {
    for (int i = 333; i < 555; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }
    set<int> out;
    QCOMPARE(test->scanMissingPackets(out), 333);

    set<int> answer;
    for (int i = 0; i < 333; i++) {
        answer.insert(i);
    }
    QCOMPARE(out, answer);

    for (int i = 0; i < 222; i++) {
        QVERIFY(test->insert(*msg, i) > 0);
    }
    out.clear();
    QCOMPARE(test->scanMissingPackets(out), 111);
    answer.clear();
    for (int i = 222; i < 333; i++) {
        answer.insert(i);
    }
    QCOMPARE(out, answer);
}

void tst_CPackage::testScanMissingPackets2() {
    delete test;
    test = new CPackage(200);
    for (int i = 200; i < 1000; i++) {
        test->insert(*msg, i);
    }
    set<int> out;
    QVERIFY(test->scanMissingPackets(out) == 0);
    QVERIFY(!test->isFull());
    test->needAll();

    QCOMPARE(test->scanMissingPackets(out), 24);
}
