#pragma once
class cXMesh;

class cBossRoom_Wall
{
public:
	cBossRoom_Wall();
	~cBossRoom_Wall();

	vector<cBossRoom_Wall> m_vecBossRoomWall;
	vector<cXMesh*> m_vecBossRoom;
	D3DXMATRIX matWorld;

	float rotY;

	void Setup();
	void Render();
	void Destroy();
};

