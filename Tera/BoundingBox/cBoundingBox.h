#pragma once
#include "Cube\cCube.h"

class cBoundingBox : public cCube
{
private :

	
	SYNTHESIZE_REF(D3DXMATRIX,m_matWorld, World);
	SYNTHESIZE_REF(cCube*, m_pBoundBox, BoundingBox);

	D3DXVECTOR3					m_vMinPos;
	D3DXVECTOR3					m_vMaxPos;


public:
	cBoundingBox();
	~cBoundingBox();

	void Setup(D3DXVECTOR3 min, D3DXVECTOR3 max);
	void Update();
	void Render();

	ST_OBB GetOBB();

};

