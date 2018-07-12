#pragma once
#include "../../cGameNode.h"

class cSceneTown : public cGameNode
{
private:

public:
	cSceneTown();
	virtual~cSceneTown();

	void Setup();
	void Update();
	void Render();
};
