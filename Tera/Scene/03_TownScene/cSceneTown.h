#pragma once
#include "../../cGameNode.h"

class cSceneTown : public cGameNode
{
private:

public:
	cSceneTown();
	virtual~cSceneTown();

	void Setup();
	void Release();
	void Update();
	void Render();
};
