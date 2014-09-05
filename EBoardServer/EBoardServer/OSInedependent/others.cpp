#include "others.h"

int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year     = wtm.wYear - 1900;
    tm.tm_mon      = wtm.wMonth - 1;
    tm.tm_mday     = wtm.wDay;
    tm.tm_hour     = wtm.wHour;
    tm.tm_min      = wtm.wMinute;
    tm.tm_sec      = wtm.wSecond;
    tm.tm_isdst    = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return 0;
}

int getIp(char* ip) {
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0) {
		return 1;
	}

	char host[256];
	ret = gethostname(host, sizeof(host));
	if (ret == SOCKET_ERROR) {
		return 2;
	}

	HOSTENT* hosts = gethostbyname(host);
	if (host == NULL) {
		return 3;
	}

	strcpy(ip, inet_ntoa(*(in_addr*) *hosts->h_addr_list));
	return 0;
}

TS_UINT64 getServerTime() {
	return GetTickCount();
}

TS_UINT64 getClientTime(DWORD bouns) {
	return GetTickCount() + bouns;
}

string int2string(TS_UINT64 number) {
	stringstream ss;
	string s;
	ss << number;
	ss >> s;
	return s;
}