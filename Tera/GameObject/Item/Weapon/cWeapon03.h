#pragma once
#include "GameObject/Item/cItemBase.h"

class cXMesh;
class cBoundingBox;

class cWeapon03 : public cItemBase
{
public:
	cWeapon03();
	virtual~cWeapon03();

	void Setup();
	void Update();
	void Rendeer();
};

