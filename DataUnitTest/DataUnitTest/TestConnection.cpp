#include "CReliableConnection.h"

#include "Assert.h"
#include "common.h"

static CReliableConnection *test;
static ts_msg* msg;

static void initial() {
	msg = new ts_msg();
	test = new CReliableConnection();
	sequence = 1;
	((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;
	test->create(1000);
}

static void unInitial() {
	delete msg;
	delete test;
}

CTEST(Recv) {
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10240; i++) {
			generateNormalMsg(*msg);
			test->msgQueue->enQueue(*msg);	
			sem_post((sem_t*) &test->semMsg);
		}
		unInitial();
		initial();
	}
	CTESTEND
}


int CReliableTest() {
	int calc = 0;
	calc += testRecv();
	return calc;
}