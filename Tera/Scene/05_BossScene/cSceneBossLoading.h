#pragma once
#include "cGameNode.h"

class cLoading;

class cSceneBossLoading : public cGameNode
{
private:
	cLoading *				m_pLoading;
public:
	cSceneBossLoading();
	virtual ~cSceneBossLoading();

	void Setup();
	void Release();
	void Update();
	void Render();

	void TotalLoading();
};

