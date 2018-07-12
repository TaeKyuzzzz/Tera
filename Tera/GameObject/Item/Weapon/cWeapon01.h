#pragma once
#include "GameObject/Item/cItemBase.h"

class cXMesh;
class cBoundingBox;


class cWeapon01 : public cItemBase
{
public:
	cWeapon01();
	virtual~cWeapon01();

	void Setup();
	void Update();
	void Rendeer();
};

