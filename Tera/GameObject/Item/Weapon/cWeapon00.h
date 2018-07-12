#pragma once
#include "GameObject/Item/cItemBase.h"

class cXMesh;
class cBoundingBox;

class cWeapon00 : public cItemBase
{
private :



public:
	cWeapon00();
	virtual~cWeapon00();

	void Setup();
	void Update();
	void Rendeer();

};

