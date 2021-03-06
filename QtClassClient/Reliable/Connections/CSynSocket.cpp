#include <assert.h>
#include "CSynSocket.h"
#include "../DataUnit/CMessage.h"
#include "../Strategy/CSettings.h"

CSynSocket::CSynSocket()
	: ipAddress("127.0.0.1") {
}

bool CSynSocket::bindPort(unsigned short iPort) {
	FILE* fp = fopen("config.txt", "r");
	char ipPrefix[20];
	int nLen = 0;
    if (fp != NULL) {
		nLen = fread(ipPrefix, sizeof(char), 20, fp);
        fclose(fp);
    }

    // TODO client
#ifdef WIN32
	struct hostent *localhost;
    char *ip;
    localhost = gethostbyname("");
	if (localhost == NULL) {
        ip = "192.168.1.123";
	} else {
		int i = 0;
		bool find = false;
		if (nLen < 16 && nLen > 1) {
			while (localhost->h_addr_list[i] != 0) {	// 寻找本机局域网IP
				ip = inet_ntoa(*(struct in_addr *) localhost->h_addr_list[i++]);
				if (memcmp(ip, ipPrefix, nLen) == 0) {
					find = true;
					break;
				}
			}
		}

		if (!find) {
            ip = inet_ntoa(*(struct in_addr *) localhost->h_addr_list[0]);
		}
	}
    cout << "server ip is " << ip << " port is " << iPort << endl;
	ipAddress = ip;
    m_LocalAddr.sin_family = AF_INET;
    m_LocalAddr.sin_addr.s_addr = inet_addr(ip);
    m_LocalAddr.sin_port = htons(iPort);

	if (iPort != 0) {
		int result = bind(m_Socket, (struct sockaddr *) &m_LocalAddr, m_LocalAddrSize);
        if (result == SOCKET_ERROR) {
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
		cout << "socket create error" << endl;
		// perror("error");
		return false;
	} else {
#ifdef _DEBUG_INFO_
		printf("socket created\n");
#endif
		if (iPort != 0)
			settingsServerSocketOpt(m_Socket);
		return bindPort(iPort);
	}
}

// TODO socket destructed
int CSynSocket::sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr) {
	if (ToAddr == NULL)
		return -1;

	int nSend = sendto(m_Socket, buf, len, 0, (sockaddr*) ToAddr, m_LocalAddrSize);
	if (nSend <= 0)	{
		cout << "send failed, error no: " << GetLastError() << endl;
	}
	return nSend;
}

int CSynSocket::recvData(char* buf, ULONG& len, struct sockaddr_in* fromAddr) {
	iop_socklen_t Fromlen = m_LocalAddrSize;
	int recv_len = recvfrom(m_Socket, buf, len, 0, (sockaddr*) fromAddr, &Fromlen);
	if (recv_len <= 0)	{
        cout << "recv failed, error no: " << GetLastError() << endl;
	}
	return recv_len;
}
