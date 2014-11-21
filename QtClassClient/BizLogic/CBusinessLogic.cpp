#include "CBusinessLogic.h"

CBusinessLogic::CBusinessLogic(CMsgObject* parent) :
	CMsgObject(parent),
    m_UserLogic(new CUserLogic(this)),
    m_GraphicLogic(new CGraphicLogic(this)),
    m_FileLogic(new CFileLogic(this)),
    m_AuthLogic(new CAuthLogic(this)),
    m_PlayerLogic(new CPlayerLogic(this)) {
}

CBusinessLogic::~CBusinessLogic() {
    delete m_UserLogic;
}

void CBusinessLogic::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
    Q_UNUSED(wParam);
    Q_UNUSED(lParam);
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    if (head->type > PACKETCONTROL) {	// Net层传来的控制类下行处理
        m_UserLogic->procMsg(msg, isremote);
    } else {							// Net层传来的其他指令传给UI层
        if (isremote)
            qDebug() << head->UID << head->type
                     << head->sequence << head->subSeq;

        if (!m_UserLogic->isServerAvailable() && !isremote)
            return;

        switch (head->type) {
        case GRAPHICS:
            m_GraphicLogic->procMsg(msg, isremote);
            break;
        case COURSEWARE:
            m_FileLogic->procMsg(msg, isremote);
            break;
        case SETWRITEAUTH:
            m_AuthLogic->procMsg(msg, isremote);
            break;
        case PLAYERCONTROL:
            m_PlayerLogic->procMsg(msg, isremote);
            break;
        default:
            break;
        }
    }
}
