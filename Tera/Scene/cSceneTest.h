#pragma once
#include "../cGameNode.h"

class cCharaPopori;
class cDummyObj;
class cSprite;
class cMonster01;
class cKelsaik;
class cPoalong;

class cTown_House;
class cTestMap;
class cKelsaik;
class cSceneTest : public cGameNode
{
private :

	cSprite*			m_pBackGroundBlack;
	int					m_nBGBlackAlpha;
	cCharaPopori*		m_pPopori;
	
	cDummyObj*			m_pDummy;

	cMonster01*			m_pMonster01;
	cKelsaik*			m_pKelsaik;
	cPoalong*			m_pPoalong;

	cTown_House*		m_pTown_House;
	cTestMap*			m_pMap;

	bool				m_isGoBoss;

	cKelsaik*			m_pKelsaik;

public:
	cSceneTest();
	~cSceneTest();

	void Setup();
	void Release();
	void Update();
	void Render();
};

