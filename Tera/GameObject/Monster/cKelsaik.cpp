#include "stdafx.h"
#include "cKelsaik.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "Particle\cParticleSet.h"
#include "cShader.h"


cKelsaik::cKelsaik()
	: m_pMonster(NULL)
	, m_currState(MON_STATE_unarmedwait)
{
	m_state = MON_STATE_unarmedwait;



	//�����ִϸ��̼��� �ƴҶ�, ������ ������ �˷��ִ� ����.
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	float animTime[MON_STATE_COUNT] =
	{
		61, 61, 1, 401, 31,
		51, 51, 116, 116, 31,
		85, 51, 175, 85, 181,
		131, 111, 111, 171, 256,
		196, 61, 1, 191, 71,
		141, 131, 61
	};

	memcpy(m_fAnimTime, animTime, sizeof(animTime));

	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] -= 1.0f;
	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] /= 30.0f;

	// ���� ó�� �ҰŴ�
	//���� ó���ϴϱ� �����ع�������. �׷��� �������״�.
	m_bIsBlend = false;

	//Monster01�� �̷� Ư���� ������ �ִ�.
	m_fAreaRadius = 300.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.0f;
	m_fFightZone = 100.0f;
	m_fHpCur = 500.0f;

	MODE = IDLE;

	// ������ ���� ��
	m_nNumofPattern = 4;
	//ó���� ��� �����س��´�.
	m_vBehaviorSpot = D3DXVECTOR3(1247, 0, 1000);

	m_pParticleBleeding = PARTICLEMANAGER->GetParticle("Bleeding");
	PARTICLEMANAGER->AddChild(m_pParticleBleeding);
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

	m_fMaxHp = 500.0f;
	m_fCurHp = 500.0f;
	m_fAttack = 20.0f;
	m_fDefense = 10.0f;

	m_pMonster = new cSkinnedMesh;
	m_pMonster->Setup("XFile/Monster", "Kelsaik.X");
	m_pMonster->SetAnimationIndexBlend(m_currState);

	// ��ġ�� ���� ��Ʈ ��
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Dummy_root");

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

	m_vPosition = m_vBehaviorSpot;

	// �ٿ�� �ڽ� ����
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// �� �浹 ���� ����(�ο��� �Ÿ�)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);

	MODE = IDLE;
}

void cKelsaik::Update()
{
	switch (MODE)
	{
	case IDLE:
		break;
	case AWAKE:
		break;
	case DEATH:
		break;
	}
}

void cKelsaik::Idle_Update()
{
}

void cKelsaik::Idle_Roaming()
{
}

void cKelsaik::Idle_Back_to_SquareOne()
{
}

void cKelsaik::Awake_Update()
{
}

void cKelsaik::Awake_Chase()
{
}

void cKelsaik::Awake_Battle()
{
}

void cKelsaik::Death_Update()
{
}

void cKelsaik::Render()
{
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

bool cKelsaik::isUseLocalAnim()
{

	if (
		m_state == MON_STATE_atk02 ||
		m_state == MON_STATE_atk01
		)
		return true;

	//�̰� ��¥ �߿�!!!
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 10.0f)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}


	return false;
}
