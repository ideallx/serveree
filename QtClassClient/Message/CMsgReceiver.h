#pragma once

#include <QObject>
#include <queue>
#include "../Reliable/DataUnit/CMessage.h"

/****************************��Ϣ�ӿ�*******************************/
class CMsgReceiver
{
protected:
	UINT lastType;

public:
    CMsgReceiver(void) {}
    virtual ~CMsgReceiver(void) {}

public:
	// ����ģ�����յ�������
    virtual void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
        Q_UNUSED(msg); Q_UNUSED(wParam); Q_UNUSED(lParam); Q_UNUSED(isremote);
    }
};
