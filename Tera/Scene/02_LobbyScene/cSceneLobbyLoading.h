#pragma once
#include "cGameNode.h"

class cLoading;

class cSceneLobbyLoading : public cGameNode
{
private :
	cLoading *				m_pLoading;
public:
	cSceneLobbyLoading();
	virtual~cSceneLobbyLoading();

	void Setup();
	void Update();
	void Render();

	void TotalLoading();
};

