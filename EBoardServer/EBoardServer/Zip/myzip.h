#pragma once;

#ifndef _MYZIP_H
#define _MYZIP_H

#include <stdio.h>
#include "zip.h"
#include "zlib.h"
#include "unzip.h"
#include <fstream>

using namespace std;
#pragma comment(lib, "zlib.lib")

class CZip
{
private:

public:
	CZip(){};
	~CZip(){};

public:
	static bool saveToZip(const char* DestPathName,const char* FileName,const void* pBuf,unsigned int nLen, bool isCreate);
	static unsigned int getOriginalSize(const char* SrcPathName,const char* FileName);
	static bool loadFromZip(const char* SrcPathName,const char* FileName,void* pBuf,unsigned int nLen);
};

#endif 