#include "stdafx.h"
#include "cCharaPopori.h"
#include "SkinnedMesh\cSkinnedMesh.h"

#include "GameObject\Item\Weapon\cWeapon00.h"
#include "GameObject\Item\Weapon\cWeapon01.h"
#include "GameObject\Item\Weapon\cWeapon02.h"
#include "GameObject\Item\Weapon\cWeapon03.h"

#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

cCharaPopori::cCharaPopori()
	: m_pBody(NULL)
	, m_currState(CH_STATE_AdvLeap)
	, m_pWeaponHand(NULL)
{

}


cCharaPopori::~cCharaPopori()
{	
	SAFE_DELETE(m_pWeapon);
}

void cCharaPopori::Setup()
{
	cCharacterClass03::Setup();

	cSkinnedMesh * pSkinnedMesh;

	
	m_pHair = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Head", "Hair01.X");
	m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_00.X");
	m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_00.X");
	m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_00.X");

	//////////////////////////////////////////////////////////////
	m_pWeapon = new cWeapon00;
	m_pWeapon->Setup();

	// 무기 장착할 스워드 본
	m_pWeaponHand = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"R_Sword");

	// 위치를 가진 루트 본
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"Dummy_root");
	
	// 얼굴과 머리를 장착할 목 본
	m_pHead = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"Bip01-Head");
	
	// 바운딩 박스 생성
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-10,-15,-10),D3DXVECTOR3(10,15,10));
	
	// 구 충돌 영역 생성
	m_pSpere = new cSpere;
	m_pSpere->Setup(D3DXVECTOR3(0,0,0),20);

	g_vPlayerPos = &m_vPosition;
}

void cCharaPopori::Update()
{
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	if (KEYMANAGER->IsOnceKeyDown('5'))
	{
		int a = 1;
	}
	
	ChangeWeapon();
	ChangeBody();
	ChangeHand();
	ChangeLeg();

	// 카메라 보는 각도 설정
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	m_fCosVal = D3DXVec3Dot(&g_vCamera, &u);
	m_fCosVal = acosf(m_fCosVal);

	if (u.z < g_vCamera.z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	if (m_fCosVal <= 0.0f)
		m_fCosVal = D3DX_PI * 2 - 0.01;
	else if (m_fCosVal >= D3DX_PI * 2)
		m_fCosVal = 0.01f;

	if (KEYMANAGER->IsOnceKeyDown('Y'))
	{
		m_fRotY = 1.0f;
		m_vPosition = D3DXVECTOR3(0, 0, 0);
	}
	// 애니메이션 진행
	if (m_currState != m_state)
	{
		if (m_bIsBlend)
		{
			m_pBody->SetAnimationIndexBlend(m_state);
			m_pHand->SetAnimationIndexBlend(m_state);
			m_pLeg->SetAnimationIndexBlend(m_state);
			m_pHair->SetAnimationIndexBlend(m_state);	
		}
		else
		{
			m_pBody->SetAnimationIndex(m_state);
			m_pHand->SetAnimationIndex(m_state);
			m_pLeg->SetAnimationIndex(m_state);
			m_pHair->SetAnimationIndex(m_state);
		}
		
		m_currState = m_state;

		m_pBody->AnimAdvanceTime();
		m_pHand->AnimAdvanceTime();
		m_pLeg->AnimAdvanceTime();
		m_pHair->AnimAdvanceTime();
		
		m_fTime += TIMEMANAGER->GetEllapsedTime();
	}

	// 이동값이 있는 애니메이션의 업데이트면
	// 애니메이션 스타트 지점의 월드에서 부터 업데이트
	// 아니면 평소처럼 적용된 월드에서 업데이트
	if (isUseLocalAnim())
	{
		m_matAnimWorld._42 = m_matWorld._42;

		m_pBody->Update(m_matAnimWorld);
		m_pHand->Update(m_matAnimWorld);
		m_pLeg->Update(m_matAnimWorld);
		m_pWeapon->SetWorld(m_pWeaponHand->CombinedTransformationMatrix);
		m_pHair->Update(m_pHead->CombinedTransformationMatrix);
	}
	else
	{
		m_pBody->Update(m_matWorld);
		m_pHand->Update(m_matWorld);
		m_pLeg->Update(m_matWorld);
		m_pWeapon->SetWorld(m_pWeaponHand->CombinedTransformationMatrix);
		m_pHair->Update(m_pHead->CombinedTransformationMatrix);
	}
	
	// 이동값이 있는 애니메이션 적용 시
	// 애니메이션 로컬을 현재 포지션으로 적용시키는 증가량을 계산 
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);

	// 무기가 있다면 무기를 업데이트
	if (m_pWeapon)
		m_pWeapon->Update();

	// 조작
	cCharacterClass03::Update();

	cGameObject::Update();
}

void cCharaPopori::Render()
{
	m_pBody->Render(NULL);
	m_pHand->Render(NULL);
	m_pLeg->Render(NULL);
	m_pHair->Render(NULL);
	
	m_pWeapon->Render();

	cGameObject::Render();

	cCharacterClass03::Render();

}

bool cCharaPopori::isUseLocalAnim()
{
	if (
		m_state == CH_STATE_combo1 ||
		m_state == CH_STATE_combo2 ||
		m_state == CH_STATE_combo3 ||
		m_state == CH_STATE_combo4 ||
		m_state == CH_STATE_tumbling ||
		m_state == CH_STATE_DwonBlow ||
		m_state == CH_STATE_bReactionStart ||
		m_state == CH_STATE_bReactionStart3 ||
		m_state == CH_STATE_Death ||
		m_state == CH_STATE_bReactionLand3 ||
		m_state == CH_STATE_gaiaCrush01 ||
		m_state == CH_STATE_gaiaCrush02 ||
		m_state == CH_STATE_gaiaCrush03 ||
		m_state == CH_STATE_CuttingSlash ||
		m_state == CH_STATE_CutHead ||
		m_state == CH_STATE_StingerBlade
		)
		return true;

	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 30.0f)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}

	return false;
}

void cCharaPopori::ChangeWeapon()
{
	if (KEYMANAGER->IsOnceKeyDown('Z'))
	{
		m_nWeaponNum = (m_nWeaponNum + 1) % 4;

		if (m_pWeapon)
			SAFE_DELETE(m_pWeapon);

		switch (m_nWeaponNum)
		{
		case 0:
			m_pWeapon = new cWeapon00;
			m_pWeapon->Setup();
			break;
		case 1:
			m_pWeapon = new cWeapon01;
			m_pWeapon->Setup();
			break;
		case 2:
			m_pWeapon = new cWeapon02;
			m_pWeapon->Setup();
			break;
		case 3:
			m_pWeapon = new cWeapon03;
			m_pWeapon->Setup();
			break;
		default:
			break;
		}
	}
}

void cCharaPopori::ChangeBody()
{
	if (KEYMANAGER->IsOnceKeyDown('X'))
	{
		m_nBodyNum = (m_nBodyNum + 1) % 4;

		float position = m_pBody->GetAnimPosition();

		switch (m_nBodyNum)
		{
		case 0:
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_00.X");
			m_pBody->SetAnimationIndex(m_currState);
			break;
		case 1:
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_01.X");
			m_pBody->SetAnimationIndex(m_currState);
			break;
		case 2:
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_02.X");
			m_pBody->SetAnimationIndex(m_currState);
			break;
		case 3:
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_03.X");
			m_pBody->SetAnimationIndex(m_currState);
			break;
		default:
			break;
		}

		m_pWeaponHand = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),"R_Sword");
		m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),"Dummy_root");
		m_pHead = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),"Bip01-Head");

		m_pBody->SetAnimPosition(position);
	}
}

void cCharaPopori::ChangeHand()
{
	if (KEYMANAGER->IsOnceKeyDown('C'))
	{
		m_nHandNum = (m_nHandNum + 1) % 4;
		
		float position = m_pHand->GetAnimPosition();
		
		switch (m_nHandNum)
		{
		case 0:
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_00.X");
			m_pHand->SetAnimationIndex(m_currState);
			break;
		case 1:
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_01.X");
			m_pHand->SetAnimationIndex(m_currState);
			break;
		case 2:
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_02.X");
			m_pHand->SetAnimationIndex(m_currState);
			break;
		case 3:
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_03.X");
			m_pHand->SetAnimationIndex(m_currState);
			break;
		default:
			break;
		}
		m_pHand->SetAnimPosition(position);
	}
}

void cCharaPopori::ChangeLeg()
{
	if (KEYMANAGER->IsOnceKeyDown('V'))
	{
		m_nLegNum = (m_nLegNum + 1) % 4;
		float position = m_pLeg->GetAnimPosition();
		
		switch (m_nLegNum)
		{
		case 0:
			m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_00.X");
			m_pLeg->SetAnimationIndex(m_currState);
			break;
		case 1:
			m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_01.X");
			m_pLeg->SetAnimationIndex(m_currState);
			break;
		case 2:
			m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_02.X");
			m_pLeg->SetAnimationIndex(m_currState);
			break;
		case 3:
			m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_03.X");
			m_pLeg->SetAnimationIndex(m_currState);
			break;
		default:
			break;
		}
		m_pLeg->SetAnimPosition(position);
	}
}

