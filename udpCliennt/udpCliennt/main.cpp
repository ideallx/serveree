#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "CMessage.h"

using namespace std;

#define PORT 2222
#pragma comment(lib, "ws2_32.lib")

TS_UINT64 sequence = 1;
int generateNormalMsg(ts_msg& msg) {
	// 数据长度在100-400之间
	// int length = rand() % 300 + 100;

	// 数据长度在525-1024之间
	int length = rand() % 500 + 525;

	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	head->size = length;
	head->sequence = sequence;
	head->isEnd = 0;
	head->UID = 0x01010101;
	head->version = 1;

	//char* body = (char *) &msg + sizeof(TS_MESSAGE_HEAD);
	//int begin = sizeof(TS_MESSAGE_HEAD);
	
	//for (int i = begin; i < length; i++) {
	//	msg.Body[i] = rand() % 256;
	//}

	//memset(body, sequence, length - sizeof(TS_MESSAGE_HEAD));
	
	sequence++;
	return length;
}

int sendMsg(ts_msg& msg, TS_UINT64 seq) {
	sequence = seq;
	return generateNormalMsg(msg);
}

int main(int argc, char* argv[]) {
	int sockfd, num;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		return 1;

	SOCKADDR_IN addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.1.202");
	addr.sin_port = htons(PORT);

	int result;
	int addrLen = sizeof(addr);

	ts_msg *msg = new ts_msg();
	int count = 0;

	while (true) {
		generateNormalMsg(*msg);
		result = sendto(sockfd, msg->Body, packetSize(*msg), 0, 
			(struct sockaddr*) &addr, addrLen);
		if (result < 0)
		{
			result = WSAGetLastError();
			cout << "error:" << result << endl;
			continue;
		}
		Sleep(1);
	}

	WSACleanup();
	return 0;
}