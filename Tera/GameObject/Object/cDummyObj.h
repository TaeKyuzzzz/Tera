#pragma once
#include "GameObject\cGameObject.h"

class cDummyObj : public cGameObject
{

	SYNTHESIZE(D3DXMATRIX, m_matWorld, World);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);


public:
	cDummyObj();
	~cDummyObj();

	void Setup(D3DXVECTOR3	pos);
	void Update();
	void Render();
};

