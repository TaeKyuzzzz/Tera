#pragma once
#include "../../cGameNode.h"

class cSceneBoss : public cGameNode
{
private:

public:
	cSceneBoss();
	virtual~cSceneBoss();

	void Setup();
	void Release();
	void Update();
	void Render();
};
