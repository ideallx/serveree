#include <iostream>

using namespace std;
#include <direct.h>
#include "common.h"


int main(int argc, char* argv[]) {
	int calc = 0;
	calc += CPackageTest();
	calc += CBlockTest();
	calc += CBlockManagerTest();
	//calc += CReliableTest();
	calc += TSQueueTest();
	cout << "TOTAL ERROR: " << calc << endl;
	int i;
	cin >> i; 
}