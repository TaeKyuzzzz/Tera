#pragma once
#include "iMap.h"

class cXMesh;

class cBossRoom_Wall : public iMap
{
private :
	D3DXMATRIX				m_matWorld;
	ST_PNT_VERTEX*			m_pVertex;		// ���ؽ� ����
	WORD*					m_pIndex;		// �ε��� ����
	DWORD					numOfVertex;	// ���ؽ� ����
	DWORD					numOfIndex;		// �ε��� ���� 


public:
	cBossRoom_Wall();
	~cBossRoom_Wall();

	cXMesh*					m_pFloor;

	vector<cBossRoom_Wall> m_vecBossRoom_Wall;
	vector<cXMesh*> m_vecWallParts;
	D3DXMATRIX matWorld;

	float rotY;

	void Setup();
	void Render();
	void Destroy();

	virtual bool GetHeight(IN float x, OUT float& y, IN float z);

};

