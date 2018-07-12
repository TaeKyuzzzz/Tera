#include "stdafx.h"
#include "cSceneTest.h"
#include "GameObject\Character\Player/cCharaPopori.h"
#include "GameObject\Object\cDummyObj.h"
#include "GameObject/Monster/cMonster01.h"
#include "Sprite\cSprite.h"
#include "cTestMap.h"

cSceneTest::cSceneTest()
	: m_pBackGroundBlack(NULL)
	, m_pPopori(NULL)
	, m_pDummy(NULL)
	, m_nBGBlackAlpha(255)
{
}


cSceneTest::~cSceneTest()
{
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pPopori);
	SAFE_DELETE(m_pDummy);
	SAFE_DELETE(m_pMonster01);
	SAFE_DELETE(m_pMap);
}

void cSceneTest::Setup()
{
	m_pPopori = new cCharaPopori;
	m_pPopori->Setup();

	m_pDummy = new cDummyObj;
	m_pDummy->Setup(D3DXVECTOR3(120,0,0));
	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");

	m_pMonster01 = new cMonster01;
	m_pMonster01->Setup();

	m_pMap = new cTestMap;
	m_pMap->Setup();
	
	m_pPopori->SetMap(m_pMap);
	
	OBJECTMANAGER->AddObject(m_pDummy);
}

void cSceneTest::Update()
{
	m_pDummy->Update();
	m_pPopori->Update();
	m_pMonster01->Update();

	if (m_nBGBlackAlpha > 0)
		m_nBGBlackAlpha -= 5;
}
void cSceneTest::Render()
{
	m_pMonster01->Render();

	m_pPopori->Render();
	
	m_pDummy->Render();

	m_pMap->Render();

	///////////////
	if(m_nBGBlackAlpha>0)
		m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3( 0, 0, 0), m_nBGBlackAlpha);
}
