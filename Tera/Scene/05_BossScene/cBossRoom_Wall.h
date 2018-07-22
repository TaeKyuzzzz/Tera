#pragma once
class cXMesh;

class cBossRoom_Wall
{
public:
	cBossRoom_Wall();
	~cBossRoom_Wall();

	vector<cBossRoom_Wall> m_vecBossRoom_Wall;
	vector<cXMesh*> m_vecWallParts;
	D3DXMATRIX matWorld;

	float rotY;

	void Setup();
	void Render();
	void Destroy();
};

