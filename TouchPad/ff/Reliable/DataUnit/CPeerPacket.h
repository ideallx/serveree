/*
 * CBlock.h
 *
 *  Created on: 2014-6-13
 *      Author: root
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "../Stdafx.h"
#include "CMessage.h"

class CPeerPacket {
protected:
	ts_msg* _msg;
	sockaddr_in peerAddr;

public:
	CPeerPacket(const ts_msg& msg) {
		int size = ((TS_MESSAGE_HEAD*) &msg)->size + sizeof (TS_MESSAGE_HEAD);
		_msg = static_cast<ts_msg*>(malloc(size));
		memcpy(_msg, &msg, size);
		totalSize = size;
	}
	CPeerPacket(TS_PEER_MESSAGE& pmsg) : peerAddr(pmsg.peeraddr) {
		CPeerPacket(pmsg.msg);
	}
	CPeerPacket() {};

	virtual ~CPeerPacket() { free(_msg); }

	inline ts_msg* msg() { return _msg; }
	inline const char* body() { return _msg->Body; } const

	inline int seq() const { return ((TS_MESSAGE_HEAD*) _msg)->sequence; }
	inline TS_UINT64 rserved() const { return ((TS_MESSAGE_HEAD*) _msg)->reserved; }
	inline TS_UINT64 time() const { return ((TS_MESSAGE_HEAD*) _msg)->time; }
	inline TS_UINT64 uid() const { return ((TS_MESSAGE_HEAD*) _msg)->UID; }
	inline sockaddr_in addr() const { return peerAddr; }
	inline unsigned char type() const { return ((TS_MESSAGE_HEAD*) _msg)->type; }
	inline void setAddr(sockaddr_in in) { peerAddr = in; }
	inline int size() const { return totalSize; }

	inline void copy(CPeerPacket* p) { 
		memcpy(&peerAddr, &p->peerAddr, sizeof(sockaddr_in)); 
		memcpy(&_msg, &p->_msg, totalSize);
	}

private:
	int totalSize;
};

#endif /* BLOCK_H_ */
