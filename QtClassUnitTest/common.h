#pragma once

#include "../QtClassClient/Reliable/DataUnit/CMessage.h"
#include "../QtClassClient/Reliable/Zip/myzip.h"
#include <string>

using namespace std;

bool checkFileExist(string zipName, int fileName);

int generateNormalMsg(ts_msg& msg);

extern TS_UINT64 sequence;
