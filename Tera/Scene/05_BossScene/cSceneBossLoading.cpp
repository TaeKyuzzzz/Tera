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

	m_pLoading->InitForSound("BossBGM", "Sound/BossRoom/Boss_Battle.ogg",true,true);

	// 맵에 쓰이는 스태틱 메시를 불러옵시다
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/Bottom_ray.X");

	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P1.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P2.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P3.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_Enter_SM_P4.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/GilMark.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/GateLock.X");  // 문

	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_SM_P4.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_SM_P1.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_SM_P2.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_SM_P5.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Room_A_SM_P3.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Cor02_A_02_Floor_SM.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_Cor02_A_02_SM.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_TES_RCELV02_SM_1.X");
	m_pLoading->InitForStaticMesh("XFile/Boss_Room/ARG_TES_RCELV02_SM_2.X");

	/////

	m_pLoading->IniteForParticle("explosion", "Texture/Particle/explosion.txt");
	m_pLoading->IniteForParticle("iceExplosion", "Texture/Particle/iceExplosion.txt");
	m_pLoading->IniteForParticle("aura", "Texture/Particle/aura1.txt");
	m_pLoading->IniteForParticle("gaiaCrash", "Texture/Particle/gaiaCrash.txt");
	m_pLoading->IniteForParticle("PortalEffect", "Texture/Particle/PortalEffect.txt");
	m_pLoading->IniteForParticle("Heal", "Texture/Particle/heal.txt");
	m_pLoading->IniteForParticle("Bleeding", "Texture/Particle/Bleeding.txt");

	m_pLoading->IniteForParticle("CDT_Ice", "Texture/Particle/CDT_Ice.txt");
	m_pLoading->IniteForParticle("CDT_Burn", "Texture/Particle/CDT_Burn.txt");

	m_pLoading->IniteForParticle("HpPotion", "Texture/Particle/HpHeal.txt");
	m_pLoading->IniteForParticle("MpPotion", "Texture/Particle/MpHeal.txt");

	// 보스가 사용하는 파티클
	m_pLoading->IniteForParticle("IceHand2", "Texture/Particle/IceHand2.txt");
	m_pLoading->IniteForParticle("FireHand", "Texture/Particle/FireHand.txt");
	m_pLoading->IniteForParticle("FireEffect", "Texture/Particle/Boss_FireEffect.txt");
	m_pLoading->IniteForParticle("IceEffect", "Texture/Particle/Boss_IceEffect.txt");

	// x 파일

	m_pLoading->InitForSkinnedMesh("XFile/Monster", "kelsaik3.X");

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

	m_pLoading->IniteForParticle("HpPotion", "Texture/Particle/HpHeal.txt");
	m_pLoading->IniteForParticle("MpPotion", "Texture/Particle/MpHeal.txt");


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

	//== Giant Griffin
	m_pLoading->InitForSound("MON_Anim_atk01", "Sound/Boss/MON_Anim_atk01(Ori).mp3");
	m_pLoading->InitForSound("MON_Anim_atk02", "Sound/Boss/MON_Anim_atk02(Ori).mp3");
	m_pLoading->InitForSound("MON_Anim_heavyatk01", "Sound/Boss/MON_Anim_heavyatk01.mp3");
	m_pLoading->InitForSound("MON_Anim_modeAlarm", "Sound/Boss/MON_Anim_modeAlarm.mp3");
	m_pLoading->InitForSound("MON_Anim_roundAtk02", "Sound/Boss/MON_Anim_roundAtk02.mp3");
	m_pLoading->InitForSound("MON_Anim_roundAtk01", "Sound/Boss/MON_Anim_roundAtk01(Ori).mp3");
	m_pLoading->InitForSound("MON_Anim_Death", "Sound/Boss/MON_Anim_Death.mp3");

	m_pLoading->InitForSound("MON_Anim_groggy", "Sound/Boss/MON_Anim_groggy.mp3");
	m_pLoading->InitForSound("MON_Anim_flinch", "Sound/Boss/MON_Anim_flinch.mp3");
	m_pLoading->InitForSound("MON_Anim_Walk", "Sound/Boss/MON_Anim_Walk.mp3");
	m_pLoading->InitForSound("GiantGriffin_Groggy", "Sound/Boss/GiantGriffin_Groggy.mp3");
	// 타격 관련 ( 로딩에서도 넣어주고 있음 )

	m_pLoading->InitForSound("WPN_Hit", "Sound/Main/WPN_Hit.mp3");
	m_pLoading->InitForSound("WPN_Sword_Attack", "Sound/Main/WPN_Sword_Attack.mp3");
	m_pLoading->InitForSound("WPN_Sword_Swing", "Sound/Main/WPN_Sword_Swing.mp3");
	m_pLoading->InitForSound("WPN_Sword_Swing2", "Sound/Main/WPN_Sword_Swing2.mp3");
	m_pLoading->InitForSound("Char_Wark_GlassLand", "Sound/Main/Char_Wark_GlassLand.mp3");
	m_pLoading->InitForSound("Char_BodyFall", "Sound/Main/Char_BodyFall.mp3");

	// 사용 이용 ( 마찬가지, 로비 로딩에서 넣어줌)
	m_pLoading->InitForSound("Char_Skill_Explosion", "Sound/Main/Char_Skill_Explosion.mp3");
	m_pLoading->InitForSound("Use_Drink", "Sound/Main/Use_Drink.mp3");
	m_pLoading->InitForSound("Use_PotionDrink", "Sound/Main/Use_PotionDrink.mp3");
	m_pLoading->InitForSound("Use_TeleportWarf", "Sound/Interface/Use_TeleportWarf.mp3");

	//GiantGriffin_Groggy
}
