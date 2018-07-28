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

	isOptionMode = false;

	SOUNDMANAGER->AddSound("Loading", "Sound/Loading/LoadingSound.mp3", true, true);
	//SOUNDMANAGER->Play("Loading");
}

void cSceneLobbyLoading::Release()
{
	SAFE_DELETE(m_pLoading);
}

void cSceneLobbyLoading::Update()
{
	m_pLoading->Update();

	if (m_pLoading->LoadingDone())
	{
		//SOUNDMANAGER->Stop("Loading");
		//TEXTUREMANAGER->Destroy();
		CAMERAMANAGER->SetType(CAMERA_FREE);
		SCENEMANAGER->ChangeScene("Test");
	}
}

void cSceneLobbyLoading::Render()
{
	m_pLoading->Render();
}

void cSceneLobbyLoading::TotalLoading()
{
	m_pLoading->IniteForParticle("explosion", "Texture/Particle/explosion.txt");
	m_pLoading->IniteForParticle("iceExplosion", "Texture/Particle/iceExplosion.txt");
	m_pLoading->IniteForParticle("aura", "Texture/Particle/aura1.txt");
	m_pLoading->IniteForParticle("gaiaCrash", "Texture/Particle/gaiaCrash.txt");
	m_pLoading->IniteForParticle("PortalEffect", "Texture/Particle/PortalEffect.txt");
	m_pLoading->IniteForParticle("Heal", "Texture/Particle/heal.txt");
	m_pLoading->IniteForParticle("Bleeding", "Texture/Particle/Bleeding.txt");

	m_pLoading->IniteForParticle("CDT_Ice", "Texture/Particle/CDT_Ice.txt");
	m_pLoading->IniteForParticle("CDT_Burn", "Texture/Particle/CDT_Burn.txt");

	// x 파일
	m_pLoading->InitForStaticMesh("XFile/Map/Field/ANC_B_4858_SL.X"); //무거운 파일을 먼저 로딩한다. 늦게하면 메모리에 안올라간다.

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

	m_pLoading->InitForSound("Field", "Sound/Field/Ambience_Field26.ogg", true, true);

	m_pLoading->InitForSound("PCAtt01", "Sound/Chara/PCAtt01.ogg");
	m_pLoading->InitForSound("PCAtt02", "Sound/Chara/PCAtt02.ogg");
	m_pLoading->InitForSound("PCAtt03", "Sound/Chara/PCAtt03.ogg");
	m_pLoading->InitForSound("PCAtt04", "Sound/Chara/PCAtt04.ogg");
	m_pLoading->InitForSound("PCSkill01", "Sound/Chara/PCSkill01.ogg");

	m_pLoading->InitForSound("EquitArmor", "Sound/Chara/EquitArmor.ogg");
	m_pLoading->InitForSound("EquitWeapon", "Sound/Chara/EquitWeapon.ogg");
	m_pLoading->InitForSound("PCDamaged", "Sound/Chara/PCDamaged.ogg");
	m_pLoading->InitForSound("PCBigDamaged", "Sound/Chara/PCBigDamaged.ogg");
	m_pLoading->InitForSound("PCDie", "Sound/Chara/PCDie.ogg");

	////


}
