#include "stdafx.h"
#include "cCharaPopori.h"
#include "SkinnedMesh\cSkinnedMesh.h"

#include "GameObject\Item\Weapon\cWeapon00.h"
#include "GameObject\Item\Weapon\cWeapon01.h"
#include "GameObject\Item\Weapon\cWeapon02.h"
#include "GameObject\Item\Weapon\cWeapon03.h"

#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "GameObject\Item\cItem.h"

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

	m_pWeapon = new cWeapon00;
	m_pWeapon->Setup();

	m_pHair = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Head", "Hair01.X");
	m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_00.X");
	m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_00.X");
	m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_00.X");

	//////////////////////////////////////////////////////////////
	m_pWeapon = new cWeapon00;
	m_pWeapon->Setup();

	// ���� ������ ������ ��
	m_pWeaponHand = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"R_Sword");

	// ��ġ�� ���� ��Ʈ ��
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"Dummy_root");

	// �󱼰� �Ӹ��� ������ �� ��
	m_pHead = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(),
		"Bip01-Head");

	// �ٿ�� �ڽ� ����
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-10, -15, -10), D3DXVECTOR3(10, 15, 10));

	// �� �浹 ���� ����
	m_pSpere = new cSpere;
	m_pSpere->Setup(D3DXVECTOR3(0, 0, 0), 20);

	g_vPlayerPos = &m_vPosition;
}

void cCharaPopori::Update()
{
	// �ʰ����Ա�
	ChangeEquit();
	
	// �ִϸ��̼��� ���̿� ���̸� ����
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	// ī�޶� ���� ���� ����
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	m_fCosVal = D3DXVec3Dot(&g_vCamera, &u);

	// nan �� ������ �ʰ� ����ó��..
	if (m_fCosVal < -1.0f)
		m_fCosVal = -0.99f;
	else if (m_fCosVal > 1.0f)
		m_fCosVal = 0.99;


	m_fCosVal = acosf(m_fCosVal);

	if (u.z < g_vCamera.z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	if (m_fCosVal < 0.0f)
		m_fCosVal += D3DX_PI * 2;
	else if (m_fCosVal > D3DX_PI * 2)
		m_fCosVal -= D3DX_PI * 2;

	if (KEYMANAGER->IsOnceKeyDown('Y'))
	{
		m_fRotY = 1.0f;
		m_vPosition = D3DXVECTOR3(0, 0, 0);
	}
	// �ִϸ��̼� ����
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

	// �̵����� �ִ� �ִϸ��̼��� ������Ʈ��
	// �ִϸ��̼� ��ŸƮ ������ ���忡�� ���� ������Ʈ
	// �ƴϸ� ���ó�� ����� ���忡�� ������Ʈ
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

	// �̵����� �ִ� �ִϸ��̼� ���� ��
	// �ִϸ��̼� ������ ���� ���������� �����Ű�� �������� ��� 
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);

	// ���Ⱑ �ִٸ� ���⸦ ������Ʈ
	if (m_pWeapon)
		m_pWeapon->Update();

	// ���� ( ������ �ٿ���ڽ��� ���⼭�ۿ� ������.. ���� ������ �����丵�ϸ� ��������
	if (m_state == CH_STATE_combo1 ||
		m_state == CH_STATE_combo2 ||
		m_state == CH_STATE_combo3 ||
		m_state == CH_STATE_combo4)
		Attack(m_fAttack);
	else if (m_state == CH_STATE_CutHead)
		if (Attack(m_fAttack * 2.0f))
			CAMERAMANAGER->Shaking(0.275f);
	else if (m_state == CH_STATE_StingerBlade)
		if(Attack(m_fAttack * 2.0f))
			CAMERAMANAGER->Shaking(0.275f);
	
	// ����
	cCharacterClass03::Update();

	cGameObject::Update();

}

void cCharaPopori::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	m_pBody->Render(NULL);
	m_pHand->Render(NULL);
	m_pLeg->Render(NULL);
	m_pHair->Render(NULL);

	m_pWeapon->Render();

	cGameObject::Render();

	cCharacterClass03::Render();

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "%.1f %.1f %.1f", m_vPosition.x, m_vPosition.y, m_vPosition.z);
	RECT rc;
	SetRect(&rc, 0, 500, 500, 700);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 255, 0));
	sprintf_s(szTemp, 1024, "%.1f %.1f %.1f", m_matWorld._41, m_matWorld._42, m_matWorld._43);

	SetRect(&rc, 0, 700, 500, 900);

	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 255, 0));
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
		
		if (m_pWeapon)
			SAFE_DELETE(m_pWeapon);

		if (m_pEquitWeapon->GetName() == "���")
		{
			m_pWeapon = new cWeapon00;
			m_pWeapon->Setup();
		}
		else if (m_pEquitWeapon->GetName()=="��ī�̼ҵ�")
		{
			m_pWeapon = new cWeapon01;
			m_pWeapon->Setup();
		}
		else if (m_pEquitWeapon->GetName()== "����")
		{
			m_pWeapon = new cWeapon02;
			m_pWeapon->Setup();

		}
		else if (m_pEquitWeapon->GetName()== "���̽��ҵ�")
		{
			m_pWeapon = new cWeapon03;
			m_pWeapon->Setup();
		}
}

void cCharaPopori::ChangeBody()
{
	
		float position = m_pBody->GetAnimPosition();
		//m_pEquitBody->GetName();

		if (m_pEquitBody == NULL)
		{
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_00.X");
			m_pBody->SetAnimationIndex(m_currState);
		}
		else if(m_pEquitBody->GetName() == "�����Ƹ�")
		{
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_01.X");
			m_pBody->SetAnimationIndex(m_currState);
		}
		else if (m_pEquitBody->GetName() == "���������ǿ�")
		{
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_02.X");
			m_pBody->SetAnimationIndex(m_currState);
		}
		else if (m_pEquitBody->GetName() == "��ī�̾Ƹ�")
		{
			m_pBody = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Body", "Body_03.X");
			m_pBody->SetAnimationIndex(m_currState);
		}

		m_pWeaponHand = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(), "R_Sword");
		m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(), "Dummy_root");
		m_pHead = (ST_BONE*)D3DXFrameFind(m_pBody->GetFrame(), "Bip01-Head");

		m_pBody->SetAnimPosition(position);
}

void cCharaPopori::ChangeHand()
{
	
		float position = m_pHand->GetAnimPosition();

		if (m_pEquitHand == NULL)
		{
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_00.X");
			m_pHand->SetAnimationIndex(m_currState);
		}
		else if (m_pEquitHand->GetName() == "�����۷���")
		{
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_01.X");
			m_pHand->SetAnimationIndex(m_currState);
		}
		else if (m_pEquitHand->GetName() == "�����������尩")
		{
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_02.X");
			m_pHand->SetAnimationIndex(m_currState);
		}
		else if (m_pEquitHand->GetName() == "��ī�̱۷���")
		{
			m_pHand = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Hand", "Hand_03.X");
			m_pHand->SetAnimationIndex(m_currState);
		}

		m_pHand->SetAnimPosition(position);
}

void cCharaPopori::ChangeLeg()
{
	float position = m_pLeg->GetAnimPosition();

	if (m_pEquitLeg == NULL)
	{
		m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_00.X");
		m_pLeg->SetAnimationIndex(m_currState);
	}
	else if (m_pEquitLeg->GetName() == "��������")
	{
		m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_01.X");
		m_pLeg->SetAnimationIndex(m_currState);
	}
	else if (m_pEquitLeg->GetName() == "���������ǽŹ�")
	{
		m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_02.X");
		m_pLeg->SetAnimationIndex(m_currState);
	}
	else if (m_pEquitLeg->GetName() == "��ī�̽���")
	{
		m_pLeg = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Character/poporiClass03/Armor/Leg", "Leg_03.X");
		m_pLeg->SetAnimationIndex(m_currState);
	}

	m_pLeg->SetAnimPosition(position);
}

bool cCharaPopori::Attack(float damage)
{
	if (OBJECTMANAGER->GiveDamagedMonster(m_pWeapon->GetBoundingBox(), damage))
		return true;
	return false;
}

int cCharaPopori::ChangeEquit()
{
	int n = 0;
	n = cCharacter::ChangeEquit();

	if (n)
	{
		switch (n)
		{
		case 1 :
			ChangeWeapon();
			break;
		case 2 :
			ChangeBody();
			break;
		case 3:
			ChangeHand();
			break;
		case 4 :
			ChangeLeg();
			break;
		}
	}


	return 0;
}

