#ifndef _ASSERT_H_
#define _ASSERT_H_

void CAssert1(bool event1);
void CAssert2(void *event2, void* expected);

void testBegin(string caseName);
int testEnd();

void clockBegin();
void clockEnd();

void memoryLeakBegin();
void memoryLeakEnd();


#define CTEST(name)			\
	int test##name()	{	\
		testBegin(#name);	\
		memoryLeakBegin();	\
		initial();			\
		clockBegin();

#define CTESTEND			\
		clockEnd();			\
		unInitial();		\
		memoryLeakEnd();	\
		return testEnd();	\
	}


#endif