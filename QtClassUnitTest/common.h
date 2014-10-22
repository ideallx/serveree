#pragma once

#include "../QtClassClient/Reliable/DataUnit/CMessage.h"
#include "../QtClassClient/Reliable/Zip/myzip.h"
#include <string>

using namespace std;

bool checkFileExist(string zipName, int fileName);

int generateNormalMsg(ts_msg& msg, TS_UINT64 uid = 0x01010101);

extern TS_UINT64 sequence;
