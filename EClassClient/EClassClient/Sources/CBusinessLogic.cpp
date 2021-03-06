#include "CBusinessLogic.h"
#include "CShape.h"
#include "CShapeContainer.h"

CBusinessLogic::CBusinessLogic(CMsgObject* parent) :
	CMsgObject(parent),
	m_UserLogic(new CUserLogic(this)),
	m_GraphicLogic(new CGraphicLogic(this)) {
}

CBusinessLogic::~CBusinessLogic() {
	delete m_UserLogic;
	delete m_GraphicLogic;
}

void CBusinessLogic::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	if (isremote) {							// 外部过来，那就是从Net层来的
		if (head->type > PACKETCONTROL) {	// Net层传来的控制类下行处理
			m_UserLogic->procMsg(msg, true);
		} else {							// Net层传来的其他指令传给UI层
			// TODO
			sendToUpLayer(msg, wParam, lParam, true);
		}
	} else {								// 内部过来，从UI层来的
		if (head->type > PACKETCONTROL) {	
			m_UserLogic->procMsg(msg, false);
		} else {
			switch (head->type) {
			case GRAPHICS:
				m_GraphicLogic->procMsg(msg, false);
				break;

			default:
				break;
			}
			sendToDownLayer(msg, wParam, lParam, false);
		}
	}
}