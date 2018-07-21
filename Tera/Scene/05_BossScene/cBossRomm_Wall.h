#pragma once
class cXMesh;

class cBossRomm_Wall
{
public:
	cBossRomm_Wall();
	~cBossRomm_Wall();

	vector<cBossRomm_Wall> m_vecBossRoomWall;
	vector<cXMesh*> m_vecBossRoom;
	D3DXMATRIX matWorld;

	float rotY;

	void Setup();
	void Render();
	void Destroy();
};

