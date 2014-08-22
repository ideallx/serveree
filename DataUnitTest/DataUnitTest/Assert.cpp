#include <iostream>
#include <string>
#include <time.h>

#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

using namespace std;

static int testNum = 0;
int errNum = 0;

void CAssert1(bool event1) {
	if (!event1) {
		cout << "ASSERT_1 ERROR, TEST NUM:" << testNum << endl;
		errNum++;
	}

	testNum++;
}

//template <class T>;
//void CAssert2(T express, T actural) {
//	if (express != actural) {
//		cout << "ASSERT_2 ERROR, TEST NUM:" << testNum << endl;
//		errNum++;
//	}
//	testNum++;
//}

void testBegin(string caseName) {
	cout << "CASE: " << caseName << " BEGIN TEST" << endl;
}

int testEnd() {
	int totalError = errNum;
	if (totalError == 0) {
		cout << "CASE SUCCESSFUL";
	} else {	
		cout << "CASE FAILED, ERROR NUM: " << errNum;
	}
	cout << endl << endl;
	testNum = errNum = 0;
	return totalError;
}

clock_t start_time;

void clockBegin() {
	start_time = clock();
}

void clockEnd() {
	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double> (
		end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

SIZE_T memoryUsed;
SIZE_T pageFile;

void memoryLeakBegin() {
	HANDLE handle=GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	memoryUsed = pmc.WorkingSetSize;
	pageFile = pmc.PagefileUsage;
}

void memoryLeakEnd() {
	HANDLE handle=GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	
	if (memoryUsed != pmc.WorkingSetSize) {
		cout << memoryUsed << "  " << pmc.WorkingSetSize << endl;
	}
	if (pageFile != pmc.PagefileUsage) {
		cout << pageFile << "  " << pmc.PagefileUsage << endl;
	}
}

