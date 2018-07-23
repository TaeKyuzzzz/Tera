#include "stdafx.h"
#include "cKelsaik.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "Particle\cParticleSet.h"
#include "cShader.h"


cKelsaik::cKelsaik()
	: m_pMonster(NULL)
	, m_currAnim(MON_Anim_Walk)
{
	D3DXMatrixIdentity(&m_matWorld);
	
	m_Anim = MON_Anim_Wait;

	//�����ִϸ��̼��� �ƴҶ�, ������ ������ �˷��ִ� ����.
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	float animTime[MON_Anim_COUNT] =
	{
		61, 61, 1, 401, 31,
		51, 51, 116, 116, 31,
		85, 51, 175, 85, 181,
		131, 111, 111, 171, 256,
		196, 61, 1, 191, 71,
		141, 131, 61
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
	m_fAreaRadius = 300.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.0f;
	m_fFightZone = 100.0f;
	m_fHpCur = 50000.0f;

	STATE = IDLE;

	// ������ ���� ��
	m_nNumofPattern = 4;
	
	
	// ����ϴ� ��ƼŬ ���
	m_pParticleBleeding = PARTICLEMANAGER->GetParticle("Bleeding");
	PARTICLEMANAGER->AddChild(m_pParticleBleeding);
	m_pIceHand = PARTICLEMANAGER->GetParticle("IceHand2");
	PARTICLEMANAGER->AddChild(m_pIceHand);
	m_pFireHand = PARTICLEMANAGER->GetParticle("FireHand");
	PARTICLEMANAGER->AddChild(m_pFireHand);

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

	m_fMaxHp = 50000.0f;
	m_fCurHp = 50000.0f;
	m_fAttack = 20.0f;
	m_fDefense = 10.0f;

	m_pMonster = new cSkinnedMesh;
	m_pMonster->Setup("XFile/Monster", "Kelsaik.X");
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
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// �� �浹 ���� ����(�ο��� �Ÿ�)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);

	STATE = IDLE;
}

void cKelsaik::Update()
{
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

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
	case DIE :
		Death_Update();
	}


	UpdateWorld();				// ���� ����
	ParticleUpdate();			// ��ƼŬ ������Ʈ

	
	cMonster::Update();
	cGameObject::Update();
}

void cKelsaik::Idle_Update()
{
	//switch (eIDLE)
	//{
	//case ROAMING:
	//	Idle_Roaming();
	//	break;
	//case COMEBACK:
	//	//Idle_Back_to_SquareOne();
	//	break;
	//}
	float Distance_Player_Monster = D3DXVec3Length(&(*g_vPlayerPos - m_vPosition));
	if (Distance_Player_Monster < m_fAreaRadius)
		STATE = AWAKE;
}

void cKelsaik::Awake_Update()
{
	
}

void cKelsaik::Awake_Chase()
{
	float Distance_Player_Monster = D3DXVec3Length(&(*g_vPlayerPos - m_vPosition));
	
	//if (Distance_Player_Monster < m_fFightZone)
	//	eAWAKE = BATTLE;
	//
	//else if (D3DXVec3Length(&(m_vPosition - m_vBehaviorSpot)) > m_fTracableArea)
	//{
	//	MODE = IDLE;
	//	eIDLE = COMEBACK;
	//}

	m_Anim = MON_Anim_Walk;
	// u���� -> ���غ���
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 v;
	D3DXVec3Normalize(&v, &temp);

	m_fCosVal = D3DXVec3Dot(&v, &u);
	m_fCosVal = acosf(m_fCosVal);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	m_vPosition += (m_fRunSpeed * v);

	m_fRotY = m_fCosVal;
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
}

void cKelsaik::Death_Update()
{

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

	// ���ÿ��� ��ġ�� ��ȭ���� �ִ� �ִϸ��̼��� ���� ó��
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);


	m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
	m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);

	// �̵����� �ִ� �ִϸ��̼� ���� ��
	// �ִϸ��̼� ������ ���� ���������� �����Ű�� �������� ��� 

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
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	m_pMonster->Render(NULL);
	
	cGameObject::Render();

	if (SightSpere && m_pSphereR)
		m_pSphereR->Render();
	if (SightSpere && m_pSphereL)
		m_pSphereL->Render();
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
		m_Anim == MON_Anim_atk02 ||
		m_Anim == MON_Anim_atk01
		)
		return true;

	//�̰� ��¥ �߿�!!! �ִϸ��̼� ��ü�� �������� ���Ѱ�� ��ó���� ���ش�.
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 10.0f)
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

void cKelsaik::ChangeAnim(MON_Anim anim, bool isBlend)
{
	m_fTime = 0.0f;

	m_bIsBlend = isBlend;

	m_Anim = anim;
	m_fCurAnimTime = m_fAnimTime[anim];

}
