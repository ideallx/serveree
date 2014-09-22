#pragma once

#include "../stdafx.h"

#include <map>

class CMsgObject;

using namespace std;

class CModuleAgent {
private:
	map<string, CMsgObject*> m_ModuleManager;

	CModuleAgent();

	static CModuleAgent *p_uniqueAgent;

public:
	~CModuleAgent();

	static CModuleAgent* getUniqueAgent();

public:
	void registerModule(string modulename, CMsgObject* object);
	void* getModule(string modulename);
};