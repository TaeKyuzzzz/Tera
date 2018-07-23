#include "stdafx.h"
#include "cSceneBoss.h"

#include "Scene\05_BossScene\cBossRoom_Wall.h"
#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"

#include "GameObject\Character\Player\cCharaPopori.h"
#include "Sprite\cSprite.h"
#include "GameObject/Monster/cKelsaik.h"

cSceneBoss::cSceneBoss()
{
}


cSceneBoss::~cSceneBoss()
{
	SAFE_DELETE(m_pBossRoom_Wall);
	//this->Destroy();
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pPopori);
	SAFE_DELETE(m_pKelsaik);

}

void cSceneBoss::Setup()
{
	Roader_WallGate();

	m_pBossRoom_Wall = new cBossRoom_Wall;
	m_pBossRoom_Wall->Setup();

	m_pPopori = new cCharaPopori;
	m_pPopori->Setup();
	m_pPopori->SetPosition(D3DXVECTOR3(0, 0, 1162));
//	m_pPopori->SetMap(m_pBossRoom_Wall);
	OBJECTMANAGER->AddCharaObject(m_pPopori);

	m_pKelsaik = new cKelsaik;
	m_pKelsaik->Setup();
	m_pKelsaik->SetPosition(D3DXVECTOR3(0, 0, 0));
	//m_pKelsaik->SetMap(m_pBossRoom_Wall);
	OBJECTMANAGER->AddMonsterObject(m_pKelsaik);

	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");

	isOptionMode = false;

	//SOUNDMANAGER->Play("BossBGM");
}

void cSceneBoss::Release()
{
}

void cSceneBoss::Update()
{
	m_pKelsaik->Update();

	m_pPopori->Update();
	
	PARTICLEMANAGER->Update();

	//////////
	if (m_nBGBlackAlpha > 0)
		m_nBGBlackAlpha -= 5;

	UIMANAGER->Update();
	ITEMMANAGER->Update();
}

void cSceneBoss::Render()
{
	Render_Wall();
	

	m_pKelsaik->Render();

	m_pPopori->Render();


	/////////////
	UIMANAGER->Render();
	ITEMMANAGER->Render();

	PARTICLEMANAGER->Render();

	if (m_nBGBlackAlpha>0)
		m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), m_nBGBlackAlpha);
}

void cSceneBoss::Render_Wall()
{
	if (!m_vBossRoom_SingObj.empty())
	{
		for (auto p : m_vBossRoom_SingObj)
		{
			p->Render();
		}
	}

	for (auto p : m_pBossRoom_Wall->m_vecBossRoom_Wall)
	{
		p.Render();
	}
}

void cSceneBoss::Roader_WallGate()
{
	const int size = 4;

	char fileName[size][256] = {
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P1.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P2.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P3.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P4.X"
		//"XFile\Boss_Room\ARG_Room_A_Enter_SM_P5.X",
	};

	for (int i = 0; i < size; i++)
	{
		//cXLoader  ground_meshX;
		//m_vBossRoom_SingObj.push_back(ground_meshX.xFimeLoad(fileName[i]));
		m_vBossRoom_SingObj.push_back(STATICMESHMANAGER->GetStaticMesh(fileName[i]));
	}
}

void cSceneBoss::Destroy()
{
	if (!m_vBossRoom_SingObj.empty())
	{
		for (auto p : m_vBossRoom_SingObj)
		{
			SAFE_DELETE(p);
		}
		delete this;
	}

	//if (!(m_pBossRoom_Wall->m_vecBossRoom_Wall.empty()))
	//{
	//	for (auto p : m_pBossRoom_Wall->m_vecBossRoom_Wall)
	//	{
	//		p.Destroy();
	//	}
	//	delete this;
	//}
}
