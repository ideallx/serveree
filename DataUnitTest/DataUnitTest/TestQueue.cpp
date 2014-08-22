#include <TSQueue.h>

#include "Assert.h"
#include "common.h"

static TSQueue<ts_msg>* test;
static ts_msg* msg;

static void initial() {
	msg = new ts_msg();
	test = new TSQueue<ts_msg>();
	sequence = 1;
	((TS_MESSAGE_HEAD*) &msg->Body)->size = 300;

}

static void unInitial() {
	delete msg;
	delete test;
}


CTEST(QueueMemory) {
	for (int i = 333; i < 666; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->enQueue(*msg));
	}
	for (int i = 333; i < 666; i++) {		// seq ´Ó1-333
		CAssert1(test->deQueue(*msg));
		CAssert1(getSeq(*msg) == i - 332);
	}

	for (int i = 333; i < 666; i++) {
		generateNormalMsg(*msg);
		CAssert1(test->enQueue(*msg));
	}
	for (int i = 333; i < 666; i++) {		// seq ´Ó334-666
		CAssert1(test->deQueue(*msg));
		CAssert1(getSeq(*msg) == i + 1);
	}
	CTESTEND
}


int TSQueueTest() {
	int calc = 0;
	calc += testQueueMemory();
	return calc;
}