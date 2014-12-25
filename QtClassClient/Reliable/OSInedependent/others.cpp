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
    tp->tv_sec = static_cast<long> (clock);
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return 0;
}

string leftPadding(int value, int size, char c) {
    string rawString = int2string(value);
    string result;
    int sizeDiff = size - rawString.size();
    if (sizeDiff > 0) {
        result = string(sizeDiff, c) + rawString;
        return result;
    } else {
        return rawString;
    }
}

string getCurTime() {
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    string result = leftPadding(wtm.wYear, 4, '0') + '_' + \
        leftPadding(wtm.wMonth, 2, '0') + \
        leftPadding(wtm.wDay, 2, '0') + '_' + \
        leftPadding(wtm.wHour, 2, '0') + \
        leftPadding(wtm.wMinute, 2, '0') + '_' + \
        leftPadding(wtm.wSecond, 2, '0');

    return result;
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

string int2string(TS_UINT64 number) {
	stringstream ss;
	string s;
	ss << number;
	ss >> s;
	return s;
}
