#include "CMsgObject.h"

CMsgObject::CMsgObject(CMsgObject* parent) :
	m_agent(NULL),
	p_Parent(parent) {
	//if (p_Parent != NULL) {
	//	p_Parent->addChild(this);
	//	m_agent = p_Parent->getAgent();
	//}
}

CMsgObject::~CMsgObject() {
	//for (auto iter = p_ChildList.begin(); iter != p_ChildList.end(); iter++) {
	//	delete *iter;
	//}
	p_ChildList.clear();
}

void CMsgObject::setAgent(CModuleAgent* agent) {
	m_agent = CModuleAgent::getUniqueAgent();
	//m_agent = agent;
	//for (auto iter = p_ChildList.begin(); iter != p_ChildList.end(); iter++) {
	//	(*iter)->setAgent(agent);
	//}
}

CMsgObject* CMsgObject::getAncestor() {
	CMsgObject* ancestor = this;
	while (ancestor->p_Parent != NULL) {
		ancestor = p_Parent;
	}
	return ancestor;
}

void CMsgObject::addChild(CMsgObject* obj) { 
	if (NULL != obj)
		p_ChildList.insert(obj); 
}

void CMsgObject::removeChild(CMsgObject* child) {
	p_ChildList.erase(child);
}

void CMsgObject::changeParent(CMsgObject* newParent) {
	p_Parent->removeChild(this);
	p_Parent = newParent;
	setAgent(newParent->m_agent);
}