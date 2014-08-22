#include <CBlockManager.h>

#include "Assert.h"
#include "common.h"

static CBlockManager *test;
static ts_msg* msg;

static void initial() {
	msg = new ts_msg();
	test = new CBlockManager();
	sequence = 1;
	((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;

}

static void unInitial() {
	delete msg;
	delete test;
}

CTEST(Record) {
	for (int i = 0; i < 10240; i++) {
		generateNormalMsg(*msg);
		Sleep(1);
		CAssert1(test->record(*msg, packetSize(*msg)) > 0);
	}
	
	CTESTEND
}

CTEST(Record2) {
	sequence = 30000;
	for (int i = 0; i < 10240; i++) {
		generateNormalMsg(*msg);
		Sleep(1);
		CAssert1(test->record(*msg, packetSize(*msg)) > 0);
	}
	
	CTESTEND
}

CTEST(MemoryBlock) {
	CAssert1(test != NULL);
	for (int i = 0; i < 10240; i++) {
		generateNormalMsg(*msg);
		Sleep(1);
		CAssert1(test->record(*msg, packetSize(*msg)) > 0);
	}
	Sleep(1000);
	CTESTEND
}

int CBlockManagerTest() {
	int calc = 0;
	calc += testRecord();
	calc += testRecord2();
	calc += testMemoryBlock();
	return calc;
}