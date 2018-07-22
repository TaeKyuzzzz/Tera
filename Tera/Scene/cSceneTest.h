#pragma once
#include "../cGameNode.h"

class cCharaPopori;
class cDummyObj;
class cSprite;
class cMonster01;
class cKelsaik;

class cTown_House;
class cTestMap;

class cSceneTest : public cGameNode
{
private :

	cSprite*			m_pBackGroundBlack;
	int					m_nBGBlackAlpha;
	cCharaPopori*		m_pPopori;
	cDummyObj*			m_pDummy;

	cMonster01*			m_pMonster01;
	cKelsaik*			m_pKelsaik;

	cTown_House*		m_pTown_House;
	cTestMap*			m_pMap;

public:
	cSceneTest();
	~cSceneTest();

	void Setup();
	void Release();
	void Update();
	void Render();
};

