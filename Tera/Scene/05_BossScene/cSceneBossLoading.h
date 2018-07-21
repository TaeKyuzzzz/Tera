#pragma once
#include "cGameNode.h"

class cXMesh;
class cBossRoom_Wall;

class cSceneBossLoading : public cGameNode
{
private:
	vector<cXMesh*> m_vGroundMap;
	cBossRoom_Wall* m_pBossRoomWall;

public:
	cSceneBossLoading();
	virtual ~cSceneBossLoading();

	void Setup();
	void Update();
	void Render();

	void Render_Wall();
	void Roader_WallGate();

	void Destroy();
};

