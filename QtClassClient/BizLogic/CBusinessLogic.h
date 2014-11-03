#pragma once

#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"
#include "CUserLogic.h"
#include "CGraphicLogic.h"
#include "cfilelogic.h"

class CBusinessLogic : public CMsgObject {
private:
    CUserLogic*			m_UserLogic;
    CGraphicLogic*      m_GraphicLogic;
    CFileLogic*         m_FileLogic;

public:
	CBusinessLogic(CMsgObject* parent = NULL);
	virtual ~CBusinessLogic();

	// �����ⲿģ����ź�
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);


private:

};
