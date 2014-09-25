#ifndef _CONNECTIONS_PEERCONNECTION_H_
#define _CONNECTIONS_PEERCONNECTION_H_

#include "CConnection.h"
#include "CAbsSocket.h"

class  CPeerConnection : public CConnection {
public:
	CPeerConnection(void);
	CPeerConnection(CAbsSocket* ps);
	virtual ~CPeerConnection(void);
};



#endif