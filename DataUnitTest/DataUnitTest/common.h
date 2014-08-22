#pragma once

#include <CMessage.h>
#include <string>

using namespace std;

int CBlockTest();
int CPackageTest();
int CBlockManagerTest();
int CReliableTest();
int TSQueueTest();

bool checkFileExist(string zipName, int fileName);

int generateNormalMsg(ts_msg& msg);

extern TS_UINT64 sequence;