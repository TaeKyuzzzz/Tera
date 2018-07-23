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

	// ���⼭ ���۷��� ī��Ʈ�� ����
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
	// �����뿡 �ʿ��� ���ҽ��� ��������

	m_pLoading->InitForSound("BossBGM","Sound/BossRoom/Boss_Battle.ogg");
	
	// �ʿ� ���̴� ����ƽ �޽ø� �ҷ��ɽô�
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P1.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P2.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P3.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P4.X");

	m_pLoading->InitForStaticMesh("XFile/Boss_Room/Bottom_ray.X");
	
	
}
