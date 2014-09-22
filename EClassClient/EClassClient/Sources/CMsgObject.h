#pragma once

#include "../stdafx.h"

#include "CMsgReceiver.h"
#include "CMsgSender.h"
#include "CModuleAgent.h"

// Controller
// Object������һ����������Ϣ�ַ�����Ϣ�ĸ���
// �κζ��󶼿�������Ϣ�Ľ����ߺͷ�����

class CMsgObject : public CMsgSender, public CMsgReceiver {
protected:
	CModuleAgent* m_agent;

	CMsgObject* p_Parent;
	set<CMsgObject*> p_ChildList;

public:
	CMsgObject(CMsgObject* parent = NULL);

	virtual ~CMsgObject(void);


public:
	void setAgent(CModuleAgent* agent);

	inline CModuleAgent* getAgent() { return m_agent; }

	CMsgObject* getAncestor();

	void changeParent(CMsgObject* newParent);


private:
	void removeChild(CMsgObject* child);

	void addChild(CMsgObject* obj);
};