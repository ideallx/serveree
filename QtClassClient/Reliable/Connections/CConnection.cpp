#include "CConnection.h"
#include "CSynSocket.h"

#include <iostream>

CConnection::~CConnection(void) {
    if (isCloned)
        return;

    clear();
}

bool CConnection::create(unsigned short localport) {
	if (pSocket == NULL) {
		pSocket = new CSynSocket();
	}

	if (!pSocket->createSocket(localport)) {
		return false;
	} else
		return true;
}

bool CConnection::clear(void) {
	if (isCloned)
		return true;

	if (pSocket == NULL)
		return true;

	bool brc = true;

	memset(&m_ToAddr, 0, CAbsSocket::m_LocalAddrSize);
	memset(&m_FromAddr, 0, CAbsSocket::m_LocalAddrSize);
    DESTROY(pSocket);

	return brc;
}

int CConnection::send(const char* buf, ULONG len) {
	if (!pSocket)
		return -1;

#ifdef _DEBUG_INFO_
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) buf;
    cout << "single send" << " "
         << head->UID << "  "
         << head->sequence << "  "
         << head->subSeq << endl;
	cout << "0";
#endif

	return pSocket->sendData(buf, len, &m_ToAddr);
}

int CConnection::recv(char* buf, ULONG& len) {
	if (!pSocket)
		return -1;
	
	//cout << "1";
	return pSocket->recvData(buf, len, &m_FromAddr);
}