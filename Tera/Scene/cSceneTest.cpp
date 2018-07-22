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
	OBJECTMANAGER->SetPlayer(m_pPopori);
	
	m_pDummy = new cDummyObj;
	m_pDummy->Setup(D3DXVECTOR3(969, -406, 4157));
	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");
	
	m_pMonster01 = new cMonster01;
	m_pMonster01->Setup();
	m_pMonster01->SetPosition(m_pMonster01->GetSpot());
	OBJECTMANAGER->AddMonsterObject(m_pMonster01);

	m_pTown_House = new cTown_House;
	m_pTown_House->Setup();

	m_pMap = new cTestMap;
	m_pMap->Setup();

	m_pPopori->SetMap(m_pMap);
	m_pMonster01->SetMap(m_pMap);
	
	OBJECTMANAGER->AddObject(m_pDummy);
	//SOUNDMANAGER->Stop("Loading");
	SOUNDMANAGER->Play("Field");

	m_isGoBoss = false;
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

	//m_pDummy->Update();
	if (m_pDummy->IsGoBossRoom())
		m_isGoBoss = true;
	
	m_pPopori->Update();

	//if (KEYMANAGER->IsOnceKeyDown('U'))
	m_pMonster01->Update();

	PARTICLEMANAGER->Update();

	UIMANAGER->Update();
	ITEMMANAGER->Update();
	
	if (m_nBGBlackAlpha > 0 && !m_isGoBoss)
		m_nBGBlackAlpha -= 5;
	else if (m_nBGBlackAlpha < 255 && m_isGoBoss)
		m_nBGBlackAlpha += 5;


	if (m_isGoBoss && m_nBGBlackAlpha > 250)
	{
		OBJECTMANAGER->VecClear();
		SOUNDMANAGER->Stop("Field");
		SCENEMANAGER->ChangeScene("BossLoading");
	}
}
void cSceneTest::Render()
{

	
	m_pDummy->Render();
	//m_pMap->Render(); //Ground Map Rendering은 GameObject/Town에서 한다.
	m_pTown_House->Render();

	
	m_pMonster01->Render();
	m_pPopori->Render();
	
	PARTICLEMANAGER->Render();
	/////////////
	if (m_nBGBlackAlpha>0)
		m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), m_nBGBlackAlpha);

	UIMANAGER->Render();
	ITEMMANAGER->Render();
}
