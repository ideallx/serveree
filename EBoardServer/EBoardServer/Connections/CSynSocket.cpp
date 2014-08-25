#include <assert.h>
#include "CSynSocket.h"
#include "../DataUnit/CMessage.h"

CSynSocket::CSynSocket() {

}

CSynSocket::~CSynSocket(void) {

}

bool CSynSocket::init(void) {
	return true;
}

void CSynSocket::unInit(void) {
	return;
}

bool CSynSocket::bindPort(unsigned short iPort) {
#ifdef WIN32
	struct hostent *localhost;
    char *ip;
    localhost = gethostbyname("");

	int i = 0;
	bool find = false;
	while (localhost->h_addr_list[i] != 0) {	// 寻找本机局域网IP
		ip = inet_ntoa(*(struct in_addr *) localhost->h_addr_list[i++]);
		if (memcmp(ip, "192.168.1", 9) == 0) {
			find = true;
			break;
		}
	}
	if (!find)
		return false;

    m_LocalAddr.sin_family = AF_INET;
    m_LocalAddr.sin_addr.s_addr = inet_addr(ip);
    m_LocalAddr.sin_port = htons(iPort);

	if (iPort != 0) {
		rc = bind(m_Socket, (struct sockaddr *) &m_LocalAddr, m_LocalAddrSize);
		if (rc == SOCKET_ERROR) {
			err = WSAGetLastError();
			return false;
		}
	}
	return true;
#else
	struct ifreq ifr;
	strcpy(ifr.ifr_name, "eth0");
	if(ioctl(sock, SIOCGIFADDR, &ifr) < 0){
		cout << "eth0" << endl;
	    return false;
	}
	m_LocalAddr.sin_addr.s_addr = ((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr.s_addr;
	m_LocalAddr.sin_family = AF_INET;
	m_LocalAddr.sin_port = htons( iPort );
	rc = bind(m_Socket, (struct sockaddr *) &m_LocalAddr, m_LocalAddrSize);

	if (rc <  0 ){
		cout << "Bind Failed " << endl;
	    return FALSE;
	}
	cout << "Bind Success" << endl;
	return TRUE;
#endif
}

// 创建socket并绑定端口
bool CSynSocket::createSocket(unsigned short iPort) {
	if ((m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("error");
		return false;
	} else {
		printf("socket created\n");
		return bindPort(iPort);
	}
}

bool CSynSocket::closeSocket(void) {
	if (0 == iop_close_handle(m_Socket))
		return true;
	else
		return false;
}

int CSynSocket::sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr) {
	int nSend = sendto(m_Socket, buf, len, 0, (sockaddr*) ToAddr, sizeof(*ToAddr));
	return nSend;
}

int CSynSocket::recvData(char* buf, ULONG& len, struct sockaddr_in* fromAddr )
{
	socklen_t Fromlen = sizeof(*fromAddr);
	int recv_len = recvfrom(m_Socket, buf, len, 0, (sockaddr*) fromAddr, &Fromlen);
	return recv_len;
}