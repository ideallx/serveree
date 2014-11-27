#pragma once

#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"
#include "CUserLogic.h"
#include "CGraphicLogic.h"
#include "cfilelogic.h"
#include "cauthlogic.h"
#include "cplayerlogic.h"
#include "../BeforeClass/loading.h"

class CBusinessLogic : public CMsgObject {
private:
    CUserLogic*			m_UserLogic;
    CGraphicLogic*      m_GraphicLogic;
    CFileLogic*         m_FileLogic;
    CAuthLogic*         m_AuthLogic;
    CPlayerLogic*       m_PlayerLogic;

public:
	CBusinessLogic(CMsgObject* parent = NULL);
	virtual ~CBusinessLogic();

	// 接收外部模块的信号
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);

private:
    bool isUIBuilt;
};
