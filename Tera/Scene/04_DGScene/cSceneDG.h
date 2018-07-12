#pragma once
#include "../../cGameNode.h"

class cSceneDG : public cGameNode
{
private:

public:
	cSceneDG();
	virtual~cSceneDG();

	void Setup();
	void Update();
	void Render();
};
