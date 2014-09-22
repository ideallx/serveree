#include "CModuleAgent.h"
#include "CMsgObject.h"

CModuleAgent* CModuleAgent::p_uniqueAgent = NULL;

CModuleAgent::CModuleAgent() {

}

CModuleAgent::~CModuleAgent() {

}

void CModuleAgent::registerModule(string modulename, CMsgObject* object) {
	m_ModuleManager.insert(make_pair(modulename, object));
	object->setAgent(this);
}

void* CModuleAgent::getModule(string modulename) {
	return m_ModuleManager.find(modulename)->second;
}

CModuleAgent* CModuleAgent::getUniqueAgent() {
	if (NULL == p_uniqueAgent) {
		p_uniqueAgent = new CModuleAgent();
	}
	return p_uniqueAgent;
}