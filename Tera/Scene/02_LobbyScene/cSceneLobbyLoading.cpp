#include "stdafx.h"
#include "cSceneLobbyLoading.h"
#include "Loading\cLoading.h"


cSceneLobbyLoading::cSceneLobbyLoading()
	: m_pLoading(NULL)
{
}


cSceneLobbyLoading::~cSceneLobbyLoading()
{
	SAFE_DELETE(m_pLoading);
}

void cSceneLobbyLoading::Setup()
{
	m_pLoading = new cLoading;

	// 여기서 레퍼런스 카운트가 증가
	m_pLoading->Setup("Texture/SceneTexture/LoadingTexture/LoadingImage_TIA_1.png");
	this->TotalLoading();
}

void cSceneLobbyLoading::Update()
{
	m_pLoading->Update();

	if (m_pLoading->LoadingDone())
	{
		//TEXTUREMANAGER->Destroy();
		SCENEMANAGER->ChangeScene("Test");
	}
}

void cSceneLobbyLoading::Render()
{
	m_pLoading->Render();
}

void cSceneLobbyLoading::TotalLoading()
{

	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Head", "Hair01.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_00.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_00.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_00.X");
	
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_01.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_01.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_01.X");

	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_02.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_02.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_02.X");

	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_03.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_03.X");
	m_pLoading->InitForSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_03.X");


	m_pLoading->InitForStaticMesh("XFile/Item/Weapon/TwoHandSword_00.X");
	m_pLoading->InitForStaticMesh("XFile/Item/Weapon/TwoHandSword_02.X");
	m_pLoading->InitForStaticMesh("XFile/Item/Weapon/TwoHandSword_03.X");
	m_pLoading->InitForStaticMesh("XFile/Item/Weapon/TwoHandSword_04.X");

	

}
