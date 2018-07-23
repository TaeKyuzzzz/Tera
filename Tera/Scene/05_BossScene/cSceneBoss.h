#pragma once
#include "cGameNode.h"

class cMesh;
class cBossRoom_Wall;
class cCharaPopori;
class cSprite;
class cKelsaik;

class cSceneBoss : public cGameNode
{
private:
	vector<cXMesh*> m_vBossRoom_SingObj;
	cBossRoom_Wall* m_pBossRoom_Wall;

	cSprite*			m_pBackGroundBlack;
	int					m_nBGBlackAlpha;
	cCharaPopori*		m_pPopori;
	cKelsaik*			m_pKelsaik;


public:
	cSceneBoss();
	virtual~cSceneBoss();

	void Setup();
	void Release();
	void Update();
	void Render();

	void Render_Wall();
	void Roader_WallGate();

	void Destroy();
};
