#pragma once
#include "iMap.h"
class cXMesh;

class cTestMap : public iMap
{
private :

	D3DXMATRIX					m_matWorld;
	cXMesh*						m_pGround;
	
	ST_PNT_VERTEX*				m_pVertex;
	WORD*						m_pIndex;

	DWORD						numOfVertex;
	DWORD						numOfIndex;
public:
	cTestMap();
	~cTestMap();

	void Setup();
	void Update();
	void Render();

	virtual bool GetHeight(IN float x, OUT float& y, IN float z);
};

