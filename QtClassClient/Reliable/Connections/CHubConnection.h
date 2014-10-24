#ifndef _CONNECTIONS_HUBCONNECTION_H_
#define _CONNECTIONS_HUBCONNECTION_H_

#include <map>
#include <set>
#include <iop_thread.h>

#include "CAbsConnection.h"
#include "CPeerConnection.h"
#include "../../Stdafx.h"

using namespace std;

class  CHubConnection : public CAbsConnection {
protected:
    iop_lock_t                          mutex_lock;
    map<TS_UINT64, CPeerConnection*>*   peerHub;
    CPeerConnection*                    pPeerConnect;
    set<TS_UINT64>                      allUsers;		// all users who has logged in the class

public:
	CHubConnection(void);
	virtual ~CHubConnection(void);

public:
	map<TS_UINT64, CPeerConnection*>* getPeerHub(void) const { return peerHub; }

public:
	// 旧版，用getAddressKey(sockaddr_in)作为key
	bool addPeer(const struct sockaddr_in& peeraddr);
	bool removePeer(const struct sockaddr_in& peeraddr);
	CPeerConnection* findPeer(const struct sockaddr_in& peeraddr);

	// 新版，用uid作为key
	bool addPeer(const TS_UINT64 uid, const struct sockaddr_in& peeraddr);
	bool removePeer(const TS_UINT64 uid);
	CPeerConnection* findPeer(const TS_UINT64 uid);

	void clearMap(void);
	void display();
	int size(void);

public:
	bool create(unsigned short localport = 0);
	bool clear(void);

	// 发给所有的peer
    virtual int send(const char* buf, ULONG len);

	// 发给所有的peer除了某个UID
    virtual int sendExcept(const char* buf, ULONG len, TS_UINT64 uid);

    virtual int recv(char* buf, ULONG& len);

public:
    virtual bool copy(CAbsConnection* conn);

protected:
	void setPeerConnection(const struct sockaddr_in& peeraddr);
};

#endif
