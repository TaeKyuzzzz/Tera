#pragma once
class cXMesh;

class cBossRoom_Road
{
public:
	cBossRoom_Road();
	~cBossRoom_Road();

	vector<cBossRoom_Road> m_vecBossRoomRoad;
	vector<cXMesh*> m_vecBossRoomParts;
	D3DXMATRIX matWorld;

	D3DXVECTOR3 pos;

	void Setup();
	void Render();
	void Destroy();
};
