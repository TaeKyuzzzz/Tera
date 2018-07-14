#pragma once
#include "GameObject\cGameObject.h"
class cXMesh;

//== ������ Destroy() ����.
class cTown_House
{
private:
	SYNTHESIZE(D3DXMATRIX, m_matWorld, World);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	vector<cXMesh*> m_vTownHouse;

public:
	cTown_House();
	virtual~cTown_House();

	void Setup();
	void Update();
	void Render();

	void Destroy();
};


