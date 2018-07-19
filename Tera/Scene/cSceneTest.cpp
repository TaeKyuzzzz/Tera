#include "stdafx.h"
#include "cSceneTest.h"
#include "GameObject\Character\Player/cCharaPopori.h"
#include "GameObject\Object\cDummyObj.h"
#include "GameObject/Monster/cMonster01.h"
#include "Sprite\cSprite.h"

#include "GameObject/Town/cTown_House.h"
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

	m_pTown_House->Destroy();
}

void cSceneTest::Setup()
{
	CAMERAMANAGER->SetType(CAMERA_FREE);

	m_pPopori = new cCharaPopori;
	m_pPopori->Setup();
	m_pPopori->SetPosition(D3DXVECTOR3(1206, 427, 2952));
	OBJECTMANAGER->AddCharaObject(m_pPopori);
	
	m_pDummy = new cDummyObj;
	m_pDummy->Setup(D3DXVECTOR3(120, 0, 0));
	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");
	
	m_pMonster01 = new cMonster01;
	m_pMonster01->Setup();
	m_pMonster01->SetPosition(D3DXVECTOR3(1247, 0, 3578));
	OBJECTMANAGER->AddMonsterObject(m_pMonster01);

	m_pTown_House = new cTown_House;
	m_pTown_House->Setup();

	m_pMap = new cTestMap;
	m_pMap->Setup();

	m_pPopori->SetMap(m_pMap);
	m_pMonster01->SetMap(m_pMap);
	
	OBJECTMANAGER->AddObject(m_pDummy);
}

void cSceneTest::Release()
{
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pPopori);
	SAFE_DELETE(m_pDummy);
	SAFE_DELETE(m_pMonster01);
	SAFE_DELETE(m_pMap);

	m_pTown_House->Destroy();
}

void cSceneTest::Update()
{
	//m_pTown_House->Update();

	m_pDummy->Update();
	m_pPopori->Update();

	//if (KEYMANAGER->IsOnceKeyDown('U'))
	m_pMonster01->Update();

	PARTICLEMANAGER->Update();

	if (m_nBGBlackAlpha > 0)
		m_nBGBlackAlpha -= 5;
}
void cSceneTest::Render()
{

	m_pMonster01->Render();
	
	m_pDummy->Render();
	//m_pMap->Render(); //Ground Map Rendering은 GameObject/Town에서 한다.
	m_pTown_House->Render();

	m_pPopori->Render();
	
	PARTICLEMANAGER->Render();
	/////////////
	if (m_nBGBlackAlpha>0)
		m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), m_nBGBlackAlpha);
}
