#pragma once
#include "GameObject/Item/cItemBase.h"

class cXMesh;
class cBoundingBox;

class cWeapon02 : public cItemBase
{
public:
	cWeapon02();
	virtual~cWeapon02();

	void Setup();
	void Update();
	void Rendeer();
};

