/*
 * CWSServer.h
 *
 *  Created on: Jun 21, 2014
 *      Author: root
 */

#ifndef _SERVER_CWSSERVER_H_
#define _SERVER_CWSSERVER_H_

#include <set>
#include <map>

#include <semaphore.h>

#include "CServer.h"
#include "../Connections/CHubConnection.h"
#include "../DataUnit/CBlockManager.h"


class CWSServer : public CServer {
private:
	TS_UINT64 _classid;
	TS_UINT64 _reserved;

public:
	CWSServer(TS_UINT64 classid, TS_UINT64 reserved);
	virtual ~CWSServer();

public:
	void sendProc();
	void recvProc();
	void msgProc();

	void displayPeer();
	bool addPeer(sockaddr_in addr, TS_UINT64 uid);
	bool removePeer(TS_UINT64 uid);

	void addUser(TS_UINT64 UID);
	void removeUser(TS_UINT64 uid);
	bool isEmpty();

	inline TS_UINT64 getClassid() const { return _classid; }
	inline void setClassid(TS_UINT64 uid) { _classid = uid; }

	inline TS_UINT64 getReserved() const { return _reserved; }
	inline void setReserved(TS_UINT64 res) { _reserved = res; }

};

#endif /* CWSSERVER_H_ */
