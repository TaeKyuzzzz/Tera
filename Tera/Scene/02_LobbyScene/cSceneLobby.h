#pragma once
#include "../../cGameNode.h"

class cSceneLobby : public cGameNode
{
private:

public:
	cSceneLobby();
	virtual~cSceneLobby();

	void Setup();
	void Update();
	void Render();
};
