#include "stdafx.h"
#include "cKelsaik.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"
#include "Sprite\cSprite.h"
#include "ProgressBar/cProgressBar.h"
#include "Particle\cParticleSet.h"
#include "cShader.h"
#include "GameObject\Character\cCharacter.h"

cKelsaik::cKelsaik()
	: m_pMonster(NULL)
	, m_currAnim(MON_Anim_Walk)
	, m_fHitCircleRadian(0.0f)
	, m_vHitCirclePos{ { 0,0,0 },{ 0, 0, 0 } }
	, m_fDamagedStack(0.0f)
	, m_isPossibleGroggy(true)
	, m_isPossibleDown(true)
	, m_isPossibleBerserk(true)
{
	D3DXMatrixIdentity(&m_matWorld);

	m_Anim = MON_Anim_Wait;

	//�����ִϸ��̼��� �ƴҶ�, ������ ������ �˷��ִ� ����.
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	float animTime[MON_Anim_COUNT] =
	{
		61, 131, 141, 71, 191, 1, 61,
		196, 256, 171, 111, 111,
		131, 181, 85, 175, 51, 85, 31, 116,
		116, 51, 51, 31, 401, 1, 61, 61
	};

	memcpy(m_fAnimTime, animTime, sizeof(animTime));

	for (int i = 0; i < MON_Anim_COUNT; i++)
		m_fAnimTime[i] -= 1.0f;
	for (int i = 0; i < MON_Anim_COUNT; i++)
		m_fAnimTime[i] /= 30.0f;

	// ���� ó�� �ҰŴ�
	//���� ó���ϴϱ� �����ع�������. �׷��� �������״�.
	m_bIsBlend = false;

	//Monster01�� �̷� Ư���� ������ �ִ�.
	m_fAreaRadius = 200.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.5f;
	m_fFightZone = 100.0f;
	m_fHpCur = 0.0f;

	STATE = IDLE;

	// ������ ���� ��
	m_nNumofPattern = 4;
	m_fPatternCostTime = 0.0f;

	m_pEffectCost = true;
	// ����ϴ� ��ƼŬ ���
	m_pParticleBleeding = PARTICLEMANAGER->GetParticle("Bleeding");
	PARTICLEMANAGER->AddChild(m_pParticleBleeding);
	m_pIceHand = PARTICLEMANAGER->GetParticle("IceHand2");
	PARTICLEMANAGER->AddChild(m_pIceHand);
	m_pFireHand = PARTICLEMANAGER->GetParticle("FireHand");
	PARTICLEMANAGER->AddChild(m_pFireHand);
	m_pIceEffect = PARTICLEMANAGER->GetParticle("IceEffect");
	PARTICLEMANAGER->AddChild(m_pIceEffect);
	m_pFireEffect = PARTICLEMANAGER->GetParticle("FireEffect");
	PARTICLEMANAGER->AddChild(m_pFireEffect);

	m_pParticleBleeding = PARTICLEMANAGER->GetParticle("Bleeding");
	PARTICLEMANAGER->AddChild(m_pParticleBleeding);

	m_pIceHand->Start();
	m_pFireHand->Start();
}


cKelsaik::~cKelsaik()
{
	SAFE_DELETE(m_pMonster);
	SAFE_DELETE(m_pSphereR);
	SAFE_DELETE(m_pSphereL);
}

void cKelsaik::Setup()
{
	cMonster::Setup();
	
	SetLight();

	m_fMaxHp = 4000.0f;
	m_fCurHp = 0.0f;
	m_fAttack = 30.0f;
	m_fDefense = 10.0f;

	m_pMonster = new cSkinnedMesh;
	//m_pMonster->Setup("XFile/Monster", "Kelsaik.X"); // Kelsaik2 Kelsaik
	m_pMonster = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Monster", "kelsaik3.X");
	m_pMonster->SetAnimationIndexBlend(m_currAnim);


	// ��ġ�� ���� ��Ʈ ��
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Dummy_root");

	m_pBIP = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01");

	// �δ�� ���� ��� ��
	m_pHandR = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-R-Hand");

	m_pHandL = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-L-Hand");

	////��� ���� ��ü
	m_pSphereR = new cSpere;
	m_pSphereR->Setup(D3DXVECTOR3(0, 0, 0), 50);

	m_pSphereL = new cSpere;
	m_pSphereL->Setup(D3DXVECTOR3(0, 0, 0), 50);



	//ó�� ���Ǵ� ��ġ ����

	m_fRotY = 4.7f;

	// �ٿ�� �ڽ� ����
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-80, -47, -50), D3DXVECTOR3(100, 100, 50));

	// �� �浹 ���� ����(�ο��� �Ÿ�)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);

	STATE = IDLE;
	m_isDoingPattern = false;
	m_partternCost = true;

	SetUpStateBar();
}


void cKelsaik::Update()
{
	//if (KEYMANAGER->IsOnceKeyDown('N'))
	//	m_Anim = (MON_Anim)((int)m_Anim + 1);
	SetTargetAngle();
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;
	//m_pBIP->TransformationMatrix._42 = m_matWorld._42;

	AnimUpdate();				// �ִϸ��̼� ����

	switch (STATE)
	{
	case IDLE:
		Idle_Update();
		break;
	case AWAKE:
		Awake_Update();
		break;
	case BATTLE:
		Battle_Update();
		break;
	case TURN:
		Turn_Update();
		break;
	case WALK:
		Walk_Update();
		break;
	case DIE:
		Death_Update();
	}

	CountPossibleDamaged(1.0f);		// �����ð�
	UpdateWorld();				// ���� ����
	ParticleUpdate();			// ��ƼŬ ��ġ ������Ʈ
	CreatePatternCost();
	UpdateUpStateBar();

	cMonster::Update();

	cGameObject::Update();
}

void cKelsaik::Idle_Update()
{
	if (isPlayerInDistance(650.f))
	{
		ChangeState(AWAKE);
	}
}

void cKelsaik::Awake_Update()
{
	if (m_Anim != MON_Anim_modeAlarm)
	{
		ChangeAnim(MON_Anim_modeAlarm, true);
	}
	else if (isEndPattern())
	{
		ChangeState(BATTLE);
	}
	else if (m_fTime > 0.8f)
	{
		if (m_fCurHp < m_fMaxHp)
			m_fCurHp += m_fMaxHp / 144;
		else
			m_fCurHp = m_fMaxHp;
		CAMERAMANAGER->Shaking(0.06f);

	}

	//if (isPlayerInDistance())
	//	ChangeState(WALK);
}

void cKelsaik::Awake_Chase()
{

//	m_Anim = MON_Anim_Walk;
//	// u���� -> ���غ���
//	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
//	D3DXVECTOR3 v;
//	D3DXVec3Normalize(&v, &temp);
//
//	m_fCosVal = D3DXVec3Dot(&v, &u);
//	m_fCosVal = acosf(m_fCosVal);
//
//	if (m_vPosition.z < g_vPlayerPos->z)
//		m_fCosVal = D3DX_PI * 2 - m_fCosVal;
//
//	m_vPosition += (m_fRunSpeed * v);
//
//	m_fRotY = m_fCosVal;
}

void cKelsaik::Awake_Battle()
{
	//���� �״°�
	if (m_fHpCur <= 0)
		STATE = DIE;

	//�������� ��Ÿĳ~~~~


}

void cKelsaik::Battle_Update()
{

	// �÷��̾ ���ݹ��� ������ ������ ��������
	if (!isPlayerInDistance(m_fAreaRadius) && !m_isDoingPattern)
	{
		ChangeState(WALK);
		return;
	}
	else if (!m_isDoingPattern)
	{
		// ���⼭ �ڿ������� ������ �ٲٸ� ���ٴ�..
		//SetAngleWithPlayer();
		ChangeAnim(MON_Anim_Wait, true);
		//m_partternCost = false;
	}

	// �÷��̾ ���ݹ��� �����̸� ����

	if (m_partternCost)
	{
		// �ϴ� ������ ��ġ�ϰ�
		m_nPatternNum = rand() % NUMOFPATTERN;

		SetTargetAngle(); // Ÿ���� ������ �� ��,


		float rot = m_fTargetAngle - m_fRotY;
		if (rot < 0) rot += D3DX_PI * 2;

		// Ÿ���� ��ġ�� ���� ���� �����°���
		if (rot >= D3DX_PI * 0.25 && rot < D3DX_PI * 0.75)
			m_nPatternNum = RIGHTTURN;
		else if (rot >= D3DX_PI * 0.75 && rot < D3DX_PI * 1.25)
			m_nPatternNum = BACKTURN;
		else if (rot >= D3DX_PI * 1.25 && rot < D3DX_PI * 1.75)
			m_nPatternNum = LEFTTURN;

		m_partternCost = false;
		m_isDoingPattern = true;
		m_pEffectCost = true;

	}


	if (m_isDoingPattern) // ���� ���϶�
	{
		switch (m_nPatternNum) // ������ ������ ó��
		{
		case 0:				AttackPattern01();	break;
		case 1:				AttackPattern02();	break;
		case 2:				AttackPattern03();	break;
		case LEFTTURN:		TurnLeft();			break;
		case RIGHTTURN:		TurnRight();		break;
		case BACKTURN:		TurnBack();			break;
		case REACTION:		DamageReaction();	break;
		case REACTIONGRGY:	ReactionGroggy();	break;
		case REACTIONDOWN:	ReactionDown();		break;
		case BERSERK:		Berserk();			break;
		}
	}

	if (KEYMANAGER->IsOnceKeyDown('N'))
	{
		m_fCurHp = 0;
		ChangeState(DIE);
	}
}

void cKelsaik::Turn_Update()
{
	// ȸ�� ���� == 51 ������ -> 51 / 30 �� �ɸ�
	if (m_Anim != MON_Anim_roundmove01 && m_Anim != MON_Anim_roundmove02)
	{
		SetTargetAngle();

		if (m_vPosition.z < g_vPlayerPos->z)
			ChangeAnim(MON_Anim_roundmove01, true);
		else
			ChangeAnim(MON_Anim_roundmove02, true);


		SetAnimWorld();
	}
	else if (!isEndPattern())
	{
		// �� �ð����� ���� ������Ʈ�� �Ųٷ� ������ �ɰŰ�����..
		if (m_Anim == MON_Anim_roundmove01)
		{
			// ������
			m_fRotY -= abs(m_fRotY - m_fTargetAngle) * (TIMEMANAGER->GetEllapsedTime() / m_fCurAnimTime);
			if (m_fRotY < 0)
				m_fRotY += 2 * D3DX_PI;
			if (m_fRotY <= m_fTargetAngle)
			{
				m_fRotY = m_fTargetAngle;
				ChangeState(BATTLE);
				ChangeAnim(MON_Anim_Wait, true);
			}
		}
		else
		{
			// ���ؾ���
			m_fRotY += abs(m_fRotY - m_fTargetAngle) *  (TIMEMANAGER->GetEllapsedTime() / m_fCurAnimTime);
			if (m_fRotY > 2 * D3DX_PI)
				m_fRotY -= 2 * D3DX_PI;
			if (m_fRotY >= m_fTargetAngle)
			{
				m_fRotY = m_fTargetAngle;
				ChangeState(BATTLE);
				ChangeAnim(MON_Anim_Wait, true);
			}
		}
	}
	//else
	//{
	//	m_fRotY = m_fTargetAngle;
	//	ChangeState(BATTLE);
	//	ChangeAnim(MON_Anim_Wait, false);
	//}

}

void cKelsaik::Walk_Update()
{
	if (KEYMANAGER->IsOnceKeyDown('V'))
		int a = 10;

	if (isPlayerInDistance(m_fAreaRadius))
	{
		ChangeState(BATTLE);
		return;
	}

	ChangeAnim(MON_Anim_Walk, true);

	SetAngleWithPlayer();

	D3DXVECTOR3 TargetPos = *g_vPlayerPos - m_vPosition;
	D3DXVec3Normalize(&TargetPos, &TargetPos);

	m_vPosition += (m_fRunSpeed * TargetPos);
}

void cKelsaik::Death_Update()
{
	if (m_Anim != MON_Anim_Death && m_Anim != MON_Anim_deathwait)
	{
		ChangeAnim(MON_Anim_Death,true);
		SetAnimWorld();
	}
	else
	{
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_deathwait,false);
		}
	}
}

void cKelsaik::Death_Die()
{
	m_fHpCur = 0.0f;

	m_Anim = MON_Anim_Death;
	m_fCurAnimTime = m_fAnimTime[MON_Anim_Death];
	m_bIsBlend = false;

}


void cKelsaik::AnimUpdate()
{
	// �ִϸ��̼� ����

	// ���� ���� �������� �ִϿ� �����ؾߵ� �ִϰ� �ٸ��ٸ� ��ü�ؾ���
	if (m_currAnim != m_Anim)
	{
		if (m_bIsBlend) // ���� ó���� �ؾ� �Ѵٸ�
			m_pMonster->SetAnimationIndexBlend(m_Anim);
		else
			m_pMonster->SetAnimationIndex(m_Anim);

		m_currAnim = m_Anim;						// ���� �ִϸ� �ٲ� �ִϷ�

		m_pMonster->AnimAdvanceTime();				// �ѹ� �ִϸ��̼��� ������Ѿ���;
		m_fTime += TIMEMANAGER->GetEllapsedTime();	// ���������� �ð��� �÷�����
	}

	// �̵����� �ִ� �ִϸ��̼��� ������Ʈ��
	// �ִϸ��̼� ��ŸƮ ������ ���忡�� ���� ������Ʈ
	// �ƴϸ� ���ó�� ����� ���忡�� ������Ʈ
	if (isUseLocalAnim())
		m_pMonster->Update(m_matAnimWorld);
	else
		m_pMonster->Update(m_matWorld);
	m_fTime += TIMEMANAGER->GetEllapsedTime();
	// ���ÿ��� ��ġ�� ��ȭ���� �ִ� �ִϸ��̼��� ���� ó��
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);


	m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
	m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);

	// �̵����� �ִ� �ִϸ��̼� ���� ��
	// �ִϸ��̼� ������ ���� ���������� �����Ű�� �������� ��� 
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x != 0.0f)
		int a = 10;
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x < 30.f)
		m_vPosition += (m_vDirection * (m_vCurAnimPos.x - m_vBeforeAnimPos.x));
	else
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
	}
}

// ���� ��ġ, ���� ������ ���� ���带 �����ϴ� �Լ�
void cKelsaik::UpdateWorld()
{
	D3DXMATRIX mat, matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
	m_pBoundingBox->SetWorld(m_matWorld);
	m_pSpere->SetWorld(m_matWorld);
}

void cKelsaik::ParticleUpdate()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat._41 = m_pHandL->CombinedTransformationMatrix._41;
	mat._42 = m_pHandL->CombinedTransformationMatrix._42;
	mat._43 = m_pHandL->CombinedTransformationMatrix._43;
	m_pIceHand->SetWorld(mat);
	mat._41 = m_pHandR->CombinedTransformationMatrix._41;
	mat._42 = m_pHandR->CombinedTransformationMatrix._42;
	mat._43 = m_pHandR->CombinedTransformationMatrix._43;
	m_pFireHand->SetWorld(mat);
}

// ����
void cKelsaik::Render()
{
	RenderUpStateBar();

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	
	// ��Ʈ �ڽ� ����
	HitCircleRender();

	m_pMonster->Render(NULL);


	cGameObject::Render();

	if (SightSpere && m_pSphereR)
		m_pSphereR->Render();
	if (SightSpere && m_pSphereL)
		m_pSphereL->Render();

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "HP : %.0f", m_fCurHp);
	RECT rc;
	SetRect(&rc, WINSIZEX - 400, 200, WINSIZEX, 300);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 0, 0));
}

void cKelsaik::HitCircleRender()
{
	DrawPickCircle(m_vHitCirclePos[0], m_fHitCircleRadian);
	DrawPickCircle(m_vHitCirclePos[1], m_fHitCircleRadian);
}

// �̵����� �ִ� �ִϸ��̼��� ��ŸƮ ���� ��Ʈ������ ����
void cKelsaik::SetAnimWorld()
{
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;
}

// ���ÿ��� ��ġ ��ȭ�� �ִ� �ִϸ��̼��� ��ȭ���� ���� ��������
bool cKelsaik::isUseLocalAnim()
{

	if (
		m_Anim == MON_Anim_atk01		||
		m_Anim == MON_Anim_atk02		||
		m_Anim == MON_Anim_roundmove02	||
		m_Anim == MON_Anim_roundmove01	||
		m_Anim == MON_Anim_ReactonAtk	||
		m_Anim == MON_Anim_Death		||
		m_Anim == MON_Anim_groggy
		)
		return true;

	//�̰� ��¥ �߿�!!! �ִϸ��̼� ��ü�� �������� ���Ѱ�� ��ó���� ���ش�.
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 30.0f)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}


	return false;
}

void cKelsaik::ChangeState(MON_STATE state)
{
	STATE = state;
}

void cKelsaik::ChangeAnim(MON_Anim anim, bool isBlend, float Time)
{
	m_fTime = 0.0f;

	m_bIsBlend = isBlend;

	m_Anim = anim;
	m_fCurAnimTime = m_fAnimTime[anim] * Time;

}

bool cKelsaik::isPlayerInDistance(float distance)
{
	if (KEYMANAGER->IsOnceKeyDown('B'))
		int a = 10;
	float Distance_Player_Monster = D3DXVec3Length(&(*g_vPlayerPos - m_vPosition));
	if (Distance_Player_Monster < distance)
		return true;
	return false;
}

bool cKelsaik::isEndPattern()
{
	if ((m_fCurAnimTime - 0.05 <= m_fTime))
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}
	return false;
}

void cKelsaik::CreatePatternCost()
{
	if (!m_partternCost && !m_isDoingPattern)
	{
		m_fPatternCostTime += TIMEMANAGER->GetEllapsedTime();
		if (m_fPatternCostTime >= 4.0f)
		{
			m_partternCost = true;
			m_fPatternCostTime = 0.0f;
		}
	}
}

void cKelsaik::SetAngleWithPlayer()
{

	D3DXVECTOR3 TargetPos = *g_vPlayerPos - m_vPosition;
	TargetPos.y = 0;
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	m_fCosVal = D3DXVec3Dot(&TargetPos, &D3DXVECTOR3(1, 0, 0));
	m_fCosVal = acosf(m_fCosVal);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	m_fRotY = m_fCosVal;
}

void cKelsaik::SetTargetAngle()
{
	D3DXVECTOR3 TargetPos = *g_vPlayerPos - m_vPosition;
	TargetPos.y = 0;

	D3DXVec3Normalize(&TargetPos, &TargetPos);
	m_fTargetAngle = D3DXVec3Dot(&TargetPos, &D3DXVECTOR3(1, 0, 0));
	m_fTargetAngle = acosf(m_fTargetAngle);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fTargetAngle = D3DX_PI * 2 - m_fTargetAngle;
}

// �� �Ӽ�
void cKelsaik::AttackPattern01()
{
	if (m_Anim != MON_Anim_atk01)
	{
		// ���� ó�� ����
		ChangeAnim(MON_Anim_atk01, true);
		SetAngleWithPlayer();
		SetAnimWorld();
		m_fHitCircleRadian = 0.0f;
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // ��ƼŬ ��°� �Բ� �������� ����!
		{
			if (m_fTime >= 2.28f && m_pEffectCost)
			{
				m_pEffectCost = false;
				D3DXMATRIX mat;
				D3DXMatrixIdentity(&mat);
				mat._41 = m_pHandR->CombinedTransformationMatrix._41;
				mat._42 = m_vPosition.y;
				mat._43 = m_pHandR->CombinedTransformationMatrix._43;
				m_pFireEffect->SetWorld(mat);
				m_pFireEffect->Start();
				CAMERAMANAGER->Shaking(0.3f);
				m_vHitCirclePos[0] = D3DXVECTOR3(mat._41, -45, mat._43);
			}
			else if (m_fTime <= 2.8 && !m_pEffectCost)
			{
				m_fHitCircleRadian += 4.5f;
				cSpere hitCircle;
				hitCircle.Setup(m_vHitCirclePos[0], m_fHitCircleRadian);
				OBJECTMANAGER->GiveDamagedChara(&hitCircle, m_fAttack, m_vPosition, CDT_BURN, 100.0f, PC_DMG_TYPE_1);
			}
		}
	}
}

// ���� �Ӽ�
void cKelsaik::AttackPattern02()
{
	if (m_Anim != MON_Anim_atk02)
	{
		// ���� ó�� ����
		ChangeAnim(MON_Anim_atk02, true);
		SetAngleWithPlayer();
		SetAnimWorld();
		m_fHitCircleRadian = 0.0f;
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // ��ƼŬ ��°� �Բ� �������� ����!
		{
			if (m_fTime >= 2.3f && m_pEffectCost)
			{
				m_pEffectCost = false;
				D3DXMATRIX mat;
				D3DXMatrixIdentity(&mat);
				mat._41 = m_pHandL->CombinedTransformationMatrix._41;
				mat._42 = m_vPosition.y;
				mat._43 = m_pHandL->CombinedTransformationMatrix._43;
				m_pIceEffect->SetWorld(mat);
				m_pIceEffect->Start();
				CAMERAMANAGER->Shaking(0.3f);
				m_vHitCirclePos[0] = D3DXVECTOR3(mat._41, -45, mat._43);
			}
			else if (m_fTime <= 2.8 && !m_pEffectCost)
			{
				m_fHitCircleRadian += 4.5f;
				cSpere hitCircle;
				hitCircle.Setup(m_vHitCirclePos[0], m_fHitCircleRadian);
				OBJECTMANAGER->GiveDamagedChara(&hitCircle, m_fAttack, m_vPosition, CDT_ICE, 100.0f, PC_DMG_TYPE_1);

			}
		}
	}
}

void cKelsaik::AttackPattern03()
{
	if (m_Anim != MON_Anim_ReactonAtk)
	{
		// ���� ó�� ����
		ChangeAnim(MON_Anim_ReactonAtk, true);
		SetAngleWithPlayer();
		SetAnimWorld();
		m_fHitCircleRadian = 0.0f;
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // ��ƼŬ ��°� �Բ� �������� ����!
		{
			if (m_fTime >= 1.95f && m_pEffectCost)
			{
				m_pEffectCost = false;
				D3DXMATRIX mat;
				D3DXMatrixIdentity(&mat);
				mat._41 = m_pHandL->CombinedTransformationMatrix._41;
				mat._42 = m_vPosition.y;
				mat._43 = m_pHandL->CombinedTransformationMatrix._43;
				m_pIceEffect->SetWorld(mat);
				m_pIceEffect->Start();
				m_vHitCirclePos[0] = D3DXVECTOR3(mat._41, -45, mat._43);

				mat._41 = m_pHandR->CombinedTransformationMatrix._41;
				mat._42 = m_vPosition.y;
				mat._43 = m_pHandR->CombinedTransformationMatrix._43;
				m_pFireEffect->SetWorld(mat);
				m_pFireEffect->Start();
				m_vHitCirclePos[1] = D3DXVECTOR3(mat._41, -45, mat._43);
				CAMERAMANAGER->Shaking(0.3f);
			}
			else if (m_fTime <= 2.45 && !m_pEffectCost)
			{
				m_fHitCircleRadian += 4.5f;
				cSpere hitCircle;
				hitCircle.Setup(m_vHitCirclePos[0], m_fHitCircleRadian);
				OBJECTMANAGER->GiveDamagedChara(&hitCircle, m_fAttack, m_vPosition, CDT_ICE, 100.0f, PC_DMG_TYPE_1);
				hitCircle.Setup(m_vHitCirclePos[1], m_fHitCircleRadian);
				OBJECTMANAGER->GiveDamagedChara(&hitCircle, m_fAttack, m_vPosition, CDT_BURN, 100.0f, PC_DMG_TYPE_1);

			}
		}
	}
}

void cKelsaik::TurnLeft()
{
	if (m_Anim != MON_Anim_roundmove01)
	{
		// ���� ó�� ����
		ChangeAnim(MON_Anim_roundmove01, true);
		SetAnimWorld();
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			SetAngleWithPlayer();
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
	}
}

void cKelsaik::TurnRight()
{
	if (m_Anim != MON_Anim_roundmove02)
	{
		// ���� ó�� ����
		ChangeAnim(MON_Anim_roundmove02, true);
		SetAnimWorld();
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			SetAngleWithPlayer();
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
	}
}

void cKelsaik::TurnBack()
{
	if (m_Anim != MON_Anim_roundAtk01 && m_Anim != MON_Anim_roundAtk02)
	{
		// ���� ó�� ����
		if (rand() % 2)
		{
			//m_Anim = MON_Anim_roundAtk01;
			ChangeAnim(MON_Anim_roundAtk01, true);
		}
		else
		{
			//	m_Anim = MON_Anim_roundAtk02;
			ChangeAnim(MON_Anim_roundAtk02, true);
		}
		SetAnimWorld();
	}
	else
	{
		// ������ �����ٸ�
		if (isEndPattern())
		{
			SetAngleWithPlayer();
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // ��ƼŬ ��°� �Բ� �������� ����!
		{
			if (m_Anim == MON_Anim_roundAtk01)
				OBJECTMANAGER->GiveDamagedChara(m_pSphereR, m_fAttack, m_vPosition,CDT_BURN,100, PC_DMG_TYPE_2);
			else if (m_Anim == MON_Anim_roundAtk02)
				OBJECTMANAGER->GiveDamagedChara(m_pSphereL, m_fAttack, m_vPosition,CDT_ICE,100, PC_DMG_TYPE_2);
		}
	}
}

void cKelsaik::Berserk()
{
	if (m_Anim != MON_Anim_heavyatk01)
	{
		ChangeAnim(MON_Anim_heavyatk01, true);
	}
	else if (isEndPattern())
	{
		m_fAttack *= 2.0f;
		m_isDoingPattern = false;
		ChangeAnim(MON_Anim_Wait,false);
	}
	else if (m_fTime > 0.8f)
	{
		CAMERAMANAGER->Shaking(0.06f);
	}
}

void cKelsaik::SetReactionPattern(int patternNum)
{
	m_fDamagedStack = 0;

	m_partternCost = false;
	m_isDoingPattern = true;
	m_pEffectCost = true;

	m_nPatternNum = patternNum;
}

void cKelsaik::DamageReaction()
{
	if (m_Anim != MON_Anim_flinch)
	{
		ChangeAnim(MON_Anim_flinch,true);
	}
	else
	{
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, true);
			m_isDoingPattern = false;
		}
	}
}

void cKelsaik::ReactionGroggy()
{
	if (m_Anim != MON_Anim_groggy)
	{
		ChangeAnim(MON_Anim_groggy, true);
		SetAnimWorld();
	}
	else
	{
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, true);
			m_isDoingPattern = false;
		}
	}
}

void cKelsaik::ReactionDown()
{
	if (m_Anim != MON_Anim_ReactionStart &&
		m_Anim != MON_Anim_ReactionLoop &&
		m_Anim != MON_Anim_ReactionEnd)
	{
		ChangeAnim(MON_Anim_ReactionStart, true);
		SetAnimWorld();
	}
	else
	{
		if (isEndPattern())
		{
			if(m_Anim == MON_Anim_ReactionStart)
				ChangeAnim(MON_Anim_ReactionLoop,false,2.0f);
			else if(m_Anim == MON_Anim_ReactionLoop)
				ChangeAnim(MON_Anim_ReactionEnd, false);
			else
			{
				ChangeAnim(MON_Anim_Wait, true);
				m_isDoingPattern = false;
			}
		}
	}
}

void cKelsaik::Damaged(float Damaged, D3DXVECTOR3 pos)
{
	if (m_isPossibleDamaged == false || STATE == DIE)
		return;

	CAMERAMANAGER->Shaking(0.1f);

	m_isPossibleDamaged = false;
	m_PossbleDamagedTime = 0.0f;

	Damaged = Damaged - m_fDefense;
	if (Damaged < 0) Damaged = 0;

	m_fCurHp -= Damaged;

	// ���� ��Ʈ�� ��ǥ�� ���� �����ϰ� ����
	D3DXMATRIX matTS, matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	float x = 100 + m_vPosition.x;
	float y = rand() % 10 + 10 + m_vPosition.y;
	float z = rand() % 60 - 30 + m_vPosition.z;
	D3DXMatrixTranslation(&matT, x, y, z);
	m_pParticleBleeding->SetWorld(matR * matT);
	m_pParticleBleeding->Start();

	// �ǰݽ� ���� ��½���� ���� ������µ� �� ����� �ƴѵ�..
	//g_pD3DDevice->LightEnable(50, true);

	if (m_fCurHp < m_fMaxHp * 0.1f && m_isPossibleBerserk)
	{
		m_isPossibleBerserk = false;
		SetReactionPattern(BERSERK);
	}
	else if (m_fCurHp < m_fMaxHp * 0.3f && m_isPossibleDown)
	{
		m_isPossibleDown = false;
		SetReactionPattern(REACTIONDOWN);
	}
	else if (m_fCurHp < m_fMaxHp * 0.5f && m_isPossibleGroggy)
	{
		m_isPossibleGroggy = false;
		SetReactionPattern(REACTIONGRGY);
	}
	// ���������� ���, 500�� �Ѿ��� �� ���� ����� ���
	else if (m_fDamagedStack > 500 && (m_nPatternNum != REACTIONGRGY) && (m_nPatternNum != REACTIONDOWN))
	{
		SetReactionPattern(REACTION);
	}
	else // 500 �ƴϸ� ����
		m_fDamagedStack += Damaged;


	if (m_fCurHp < 0)
	{
		m_fCurHp = 0;
		ChangeState(DIE);
	}
}

void cKelsaik::SetUpStateBar()
{
	m_BackBar = TEXTUREMANAGER->GetSprite("Texture/MonsterInfo/BossHpBack.png");

	m_pHpBar = new cProgressBar;
	m_pHpBar->Setup("Texture/MonsterInfo/BossHp.png",
		"Texture/MonsterInfo/BossEmpty.png",
		562, 135, 460, 16);

}

void cKelsaik::UpdateUpStateBar()
{
	m_pHpBar->SetGauge(m_fCurHp, m_fMaxHp);
}

void cKelsaik::RenderUpStateBar()
{
	if (STATE == IDLE)
		return;

	m_BackBar->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(WINSIZEX/2 - m_BackBar->textureInfo.Width / 2.0f, 120, 0));
	m_pHpBar->Render();

	char szTemp[1024];
	RECT rc;

	sprintf_s(szTemp, 1024, "%.0f%%", ((float)m_fCurHp /(float)m_fMaxHp)*100.0f);
	SetRect(&rc,
		WINSIZEX / 2 - 20,137, WINSIZEX / 2 +20,152);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::TF_UI_NUMBER2);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc,
		DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
}

void cKelsaik::SetLight()
{
	D3DXVECTOR3 position = m_vPosition;

	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_POINT;
	light.Ambient.r = light.Diffuse.r = 1.0f;
	light.Ambient.g = light.Diffuse.g = 1.0f;
	light.Ambient.b = light.Diffuse.b = 1.0f;

	light.Attenuation0 = 0.2;
	light.Attenuation1 = 0.1;
	light.Attenuation2 = 0.1;

	light.Position = position;

	vecDir = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 2000.0f;
	g_pD3DDevice->SetLight(50, &light);
}

