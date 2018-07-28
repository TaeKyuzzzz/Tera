#include "stdafx.h"
#include "cSceneTest.h"
#include "GameObject\Character\Player/cCharaPopori.h"
#include "GameObject\Object\cDummyObj.h"
#include "GameObject/Monster/cMonster01.h"
#include "GameObject/Monster/cMonster02.h"
#include "GameObject/NPC/cPoalong.h"
#include "Sprite\cSprite.h"

#include "GameObject/Town/cTown_House.h"
#include "cTestMap.h"


#include "GameObject/Monster/cKelsaik.h"
 
cSceneTest::cSceneTest()
	: m_pBackGroundBlack(NULL)
	, m_pPopori(NULL)
	, m_pDummy(NULL)
	, m_pMonster01(NULL)
	, m_pMonster02(NULL)
	, m_pKelsaik(NULL)
	, m_pPoalong(NULL)
	, m_nBGBlackAlpha(255)
{
}


cSceneTest::~cSceneTest()
{
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pPopori);
	SAFE_DELETE(m_pDummy);
	SAFE_DELETE(m_pMonster01);
	SAFE_DELETE(m_pMonster02);
	SAFE_DELETE(m_pKelsaik);
	SAFE_DELETE(m_pPoalong);
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
	m_pMonster01->Setup(D3DXVECTOR3(1979,0,3893));
	//m_pMonster01->SetPosition(m_pMonster01->GetSpot());
	OBJECTMANAGER->AddMonsterObject(m_pMonster01);

	m_pMonster02 = new cMonster02;
	m_pMonster02->Setup(D3DXVECTOR3(1247, 0, 3578));
	//m_pMonster01->SetPosition(m_pMonster01->GetSpot());
	OBJECTMANAGER->AddMonsterObject(m_pMonster02);

	m_pPoalong = new cPoalong;
	m_pPoalong->Setup(D3DXVECTOR3(972,0,3813));

	m_pTown_House = new cTown_House;
	m_pTown_House->Setup();

	m_pMap = new cTestMap;
	m_pMap->Setup();

	m_pPopori->SetMap(m_pMap);
	m_pMonster01->SetMap(m_pMap);
	m_pMonster02->SetMap(m_pMap);
	m_pPoalong->SetMap(m_pMap);
	
	OBJECTMANAGER->AddObject(m_pDummy);
	//SOUNDMANAGER->Stop("Loading");
	SOUNDMANAGER->Play("Field");

	m_isGoBoss = false;


	m_pKelsaik = new cKelsaik;
	m_pKelsaik->Setup();
	m_pKelsaik->SetPosition(D3DXVECTOR3(0, -45.2, 0));
	//m_pKelsaik->SetMap(m_pBossRoom_Wall);
	OBJECTMANAGER->AddMonsterObject(m_pKelsaik);
}

void cSceneTest::Release()
{
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pPopori);
	SAFE_DELETE(m_pDummy);
	SAFE_DELETE(m_pMonster01);
	SAFE_DELETE(m_pPoalong);
	SAFE_DELETE(m_pMap);



	m_pTown_House->Destroy();
}

void cSceneTest::Update()
{
	m_pKelsaik->Update();
	//m_pTown_House->Update();

	//m_pDummy->Update();
	if (m_pDummy->IsGoBossRoom())
		m_isGoBoss = true;
	
	m_pPopori->Update();

	//if (KEYMANAGER->IsOnceKeyDown('U'))
	m_pMonster01->Update();

	m_pMonster02->Update();

	m_pPoalong->Update();

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
	m_pKelsaik->Render();
	m_pPoalong->Render();
	m_pMonster01->Render();
	m_pMonster02->Render();

	//포포리가 제일 나중에 렌더되어야 한다.
	PARTICLEMANAGER->Render();
	m_pPopori->Render();
	

	UIMANAGER->Render();
	ITEMMANAGER->Render();
	
	/////////////
	if (m_nBGBlackAlpha>0)
		m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), m_nBGBlackAlpha);
}
