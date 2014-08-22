#include <CBlock.h>
#include "Assert.h"
#include "common.h"

#include <iostream>
using namespace std;

static CBlock *test;
static ts_msg* msg;

static void initial() {
	test = new CBlock();
	msg = new ts_msg();
	sequence = 1;
	((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
}

static void unInitial() {
	delete msg;
	delete test;
}

CTEST(AddMsg1) {
	CAssert1(test != NULL);
	test->setZipName("aaaa.zip");
	int total = 100000;
	for (int i = 0; i < total; i++) {
		generateNormalMsg(*msg);
		Sleep(1);
		CAssert1(test->addMsg(*msg) > 0);
	}
	for (int i = 0; i < total / 1024; i++) 
		CAssert1(checkFileExist("aaaa.zip", i));
	CAssert1(!checkFileExist("aaaa.zip", 300));
	CTESTEND
}

CTEST(ReadMsg) {
	CAssert1(test != NULL);
	test->setZipName("bbbb.zip");
	for (int i = 0; i < 30000; i++) {
		generateNormalMsg(*msg);
		Sleep(1);
		CAssert1(test->addMsg(*msg) > 0);
	}

	for (int i = 200; i < 20000; i += 400) {
		CAssert1(test->readMsg(i, *msg) > 0);
		TS_UINT64 seq = getSeq(*msg);
		CAssert1(getSeq(*msg) == i);
	}

	CTESTEND
}

CTEST(ScanMissing) {
	CAssert1(test != NULL);
	test->setZipName("cccc.zip");

	int interval = 36;
	int total = 20000;

	for (int i = 0; i < total; i++) {		// 模拟丢包
		if (i % interval == 0) {			// 随便一个数的倍数全丢了
			sequence++;
			continue;
		}
		generateNormalMsg(*msg);
		CAssert1(test->addMsg(*msg) > 0);
	}

	set<TS_UINT64> missed = test->scanMissingPackets();
	for (int i = 1 + interval; i < total; i += interval)	// 第一号被跳过了。因为第一次就是continue
		CAssert1(missed.count(i) != 0);

	CTESTEND
}

CTEST(BlockMemoryLeak) {
	CAssert1(test != NULL);
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 50000; i++) {
			generateNormalMsg(*msg);
			CAssert1(test->addMsg(*msg) > 0);
		}
		unInitial();
		initial();
	}
	CTESTEND
}

int CBlockTest() {
	int calc = 0;
	//calc += testAddMsg1();
	calc += testReadMsg();
	calc += testScanMissing();
	// calc += testBlockMemoryLeak();
	return calc;
}