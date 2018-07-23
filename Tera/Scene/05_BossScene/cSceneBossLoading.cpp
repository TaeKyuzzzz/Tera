#include "stdafx.h"
#include "cSceneBossLoading.h"
#include "Loading\cLoading.h"

cSceneBossLoading::cSceneBossLoading()
	: m_pLoading(NULL)
{
}


cSceneBossLoading::~cSceneBossLoading()
{
	SAFE_DELETE(m_pLoading);
}

void cSceneBossLoading::Setup()
{
	m_pLoading = new cLoading;

	// 여기서 레퍼런스 카운트가 증가
	m_pLoading->Setup("Texture/SceneTexture/LoadingTexture/LoadingImage_Awaken_02.png");
	this->TotalLoading();

	isOptionMode = false;

	SOUNDMANAGER->AddSound("Loading", "Sound/Loading/LoadingSound.mp3", true, true);
	//SOUNDMANAGER->Play("Loading");
}

void cSceneBossLoading::Release()
{
	SAFE_DELETE(m_pLoading);
}

void cSceneBossLoading::Update()
{
	m_pLoading->Update();

	if (m_pLoading->LoadingDone())
	{
		//SOUNDMANAGER->Stop("Loading");
		//TEXTUREMANAGER->Destroy();
		CAMERAMANAGER->SetType(CAMERA_FREE);
		SCENEMANAGER->ChangeScene("Boss");
	}
}

void cSceneBossLoading::Render()
{
	m_pLoading->Render();
}

void cSceneBossLoading::TotalLoading()
{
	// 보스룸에 필요한 리소스들 가져오기

	m_pLoading->InitForSound("BossBGM","Sound/BossRoom/Boss_Battle.ogg");
	
	// 맵에 쓰이는 스태틱 메시를 불러옵시다
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P1.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P2.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P3.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P4.X");

	m_pLoading->InitForStaticMesh("XFile/Boss_Room/Bottom_ray.X");
	
	
}
