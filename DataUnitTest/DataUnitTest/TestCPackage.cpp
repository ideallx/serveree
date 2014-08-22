#include <CPackage.h>

#include "Assert.h"
#include "common.h"

static CPackage *test;
static ts_msg* msg;

static void initial() {
	msg = new ts_msg();
	test = new CPackage();
	sequence = 1;
	((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;

}

static void unInitial() {
	delete msg;
	delete test;
}

CTEST(Insert1) {	// 全部添加 
	CAssert1(test != NULL);

	for (int i = 0; i < 1024; i++)
		CAssert1(test->insert(*msg, i) > 0);

	for (int i = 0; i < 200; i++)
		CAssert1(test->insert(*msg, rand() % 1030) < 0);	// 此时已满，无论大小应该都加不了
	CTESTEND
}

CTEST(Insert2) {	// 部分添加
	CAssert1(test != NULL);
	for (int i = 0; i < 100; i++)
		CAssert1(test->insert(*msg, i) > 0);

	for (int i = 500; i < 700; i++)
		CAssert1(test->insert(*msg, i) > 0);

	for (int i = 552; i < 661; i++)
		CAssert1(test->insert(*msg, i) < 0);

	for (int i = 1024; i < 1100; i++)
		CAssert1(test->insert(*msg, i) < 0);
	CTESTEND
}

CTEST(Insert3) {	// 乱序添加
	CAssert1(test != NULL);
	for (int i = 1023; i != -1; i--)
		CAssert1(test->insert(*msg, i) > 0);

	CAssert1(test->isFull());
	CTESTEND
}


CTEST(Query1) {		// 全部插入读取
	CAssert1(test != NULL);
	for (int i = 444; i < 456; i++) {
		CAssert1(test->query(*msg, i) < 0);
	}
	for (int i = 1024; i < 1222; i++) {
		CAssert1(test->query(*msg, i) < 0);
	}
	for (int i = -500; i < 0; i++) {
		CAssert1(test->query(*msg, i) < 0);
	}

	for (int i = 0; i < 1024; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->insert(*msg, i) > 0);
	}

	for (int i = 0; i < 1024; i++) {
		CAssert1(test->query(*msg, i) > 0);
		TS_UINT64 seq = getSeq(*msg);
		CAssert1(seq == i + 1);
	}
	CTESTEND
}

CTEST(Query2) {		// 部分插入读取
	sequence = 1025;
	for (int i = 0; i < 555; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->insert(*msg, i) > 0);
	}

	for (int i = 444; i < 555; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->query(*msg, i) > 0);
		TS_UINT64 seq = getSeq(*msg);
		CAssert1(seq == i + 1025);
	}

	for (int i = 666; i < 777; i++) {
		CAssert1(test->query(*msg, i) < 0);
	}
	CTESTEND
}

CTEST(Save) {
	for (int i = 0; i < 1024; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->insert(*msg, i) > 0);
	}

	CAssert1(test->save("fff.zip", 2, true));
	CTESTEND
}

CTEST(Load) {
	// 异常测试
	CAssert1(test->load("ggg.zip", 2) == false);
	
	CAssert1(test->load("fff.zip", 2) == true);
	for (int i = 0; i < 1024; i++) {
		CAssert1(test->query(*msg, i) > 0);
		int seq = getSeq(*msg);
		CAssert1(seq == i+1);
	}
	CTESTEND
}

CTEST(IsExist) {
	for (int i = 333; i < 555; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}

	for (int i = 777; i < 999; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}

	for (int i = -200; i < 2000; i++) {
		if (i < 0) {
			CAssert1(test->isExist(i) == false);
		} else if (i < 333) {
			CAssert1(test->isExist(i) == false);
		} else if (i < 555) {
			CAssert1(test->isExist(i) == true);
		} else if (i < 777) {
			CAssert1(test->isExist(i) == false);
		} else if (i < 999) {
			CAssert1(test->isExist(i) == true);
		} else if (i < 1024) {
			CAssert1(test->isExist(i) == false);
		} else {
			CAssert1(test->isExist(i) == false);
		}
	}
	CTESTEND
}

CTEST(IsFull1) {
	CAssert1(test->isFull() == false);
	for (int i = 333; i < 555; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}
	CAssert1(test->isFull() == false);

	for (int i = 0; i < 1023; i++) {
		test->insert(*msg, i);
	CAssert1(test->isFull() == false);
	}
	test->insert(*msg, 1023);
	CAssert1(test->isFull() == true);
	CAssert1(test->save("erer.zip", 2, true));
	delete test;
	
	sequence = 1;
	test = new CPackage();
	CAssert1(test->isFull() == false);
	CAssert1(test->load("erer.zip", 2) == true);
	CAssert1(test->isFull() == true);
	
	CTESTEND
}

CTEST(IsFull2) {
	CAssert1(test->isFull() == false);
	for (int i = 1023; i != -1; i--)
		CAssert1(test->insert(*msg, i) > 0);
	CAssert1(test->isFull() == true);
	
	CTESTEND
}

CTEST(ScanAll) {
	for (int i = 333; i < 555; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}
	set<int> out;
	CAssert1(test->scanMissingPackets(out) == 333);

	test->scanAll();
	CAssert1(test->scanMissingPackets(out) == 1024-222);
	
	CTESTEND
}

CTEST(ScanMissingPackets) {
	for (int i = 333; i < 555; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}
	set<int> out;
	CAssert1(test->scanMissingPackets(out) == 333);

	set<int> answer;
	for (int i = 0; i < 333; i++) {
		answer.insert(i);
	}
	CAssert1(out == answer);
	
	for (int i = 0; i < 222; i++) {
		CAssert1(test->insert(*msg, i) > 0);
	}
	out.clear();
	CAssert1(test->scanMissingPackets(out) == 111);
	answer.clear();
	for (int i = 222; i < 333; i++) {
		answer.insert(i);
	}
	CAssert1(out == answer);
	CTESTEND
}

CTEST(ScanMissingPackets2) {
	delete test;
	test = new CPackage(200);
	for (int i = 200; i < 1000; i++) {
		test->insert(*msg, i);
	}
	set<int> out;
	CAssert1(test->scanMissingPackets(out) == 0);
	CAssert1(!test->isFull());
	test->scanAll();

	CAssert1(test->scanMissingPackets(out) == 24);


	CTESTEND
}

CTEST(MemoryLeak) {
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < 1024; i++) {
			generateNormalMsg(*msg);
			CAssert1(test->insert(*msg, i) > 0);
		}
		unInitial();
		initial();
	}

	CTESTEND
}

int CPackageTest() {
	int calc = 0;
	calc += testInsert1();
	calc += testInsert2();
	calc += testInsert3();
	calc += testQuery1();
	calc += testQuery2();
	calc += testSave();
	calc += testLoad();
	calc += testIsExist();
	calc += testIsFull1();
	calc += testIsFull2();
	calc += testScanAll();
	calc += testScanMissingPackets();
	calc += testScanMissingPackets2();
	//calc += testMemoryLeak();
	return calc;
}