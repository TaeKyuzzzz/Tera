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
	m_fHpCur = 50000.0f;

	MODE = IDLE;
	eIDLE = ROAMING;
	eAWAKE = CHASE;
	eDEATH = DIE;

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

	m_fMaxHp = 50000.0f;
	m_fCurHp = 50000.0f;
	m_fAttack = 20.0f;
	m_fDefense = 10.0f;

	m_pMonster = new cSkinnedMesh;
	m_pMonster->Setup("XFile/Monster", "Kelsaik.X");
	m_pMonster->SetAnimationIndexBlend(m_currState);

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
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	switch (MODE)
	{
	case IDLE:
		Idle_Update();
		break;
	case AWAKE:
		Awake_Update();
		break;
	case DEATH:
		Death_Update();
		break;
	}

	// �ִϸ��̼� ����
	if (m_currState != m_state)
	{
		if (m_bIsBlend)
		{
			m_pMonster->SetAnimationIndexBlend(m_state);

		}
		else
		{
			m_pMonster->SetAnimationIndex(m_state);

		}

		m_currState = m_state;

		m_pMonster->AnimAdvanceTime();
		//m_fTime += TIMEMANAGER->GetEllapsedTime();
	}

	// �̵����� �ִ� �ִϸ��̼��� ������Ʈ��
	// �ִϸ��̼� ��ŸƮ ������ ���忡�� ���� ������Ʈ
	// �ƴϸ� ���ó�� ����� ���忡�� ������Ʈ
	if (isUseLocalAnim())
	{
		m_pMonster->Update(m_matAnimWorld);

	}
	else
	{
		m_pMonster->Update(m_matWorld);

	}
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);



	m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
	m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);

	// �̵����� �ִ� �ִϸ��̼� ���� ��
	// �ִϸ��̼� ������ ���� ���������� �����Ű�� �������� ��� 
	//D3DXMATRIX matR, matT;

	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x < 30.f)
		m_vPosition += (m_vDirection * (m_vCurAnimPos.x - m_vBeforeAnimPos.x));
	else
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
	}


	D3DXMATRIX mat, matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);


	m_matWorld = matR * matT;
	m_pBoundingBox->SetWorld(m_matWorld);
	m_pSpere->SetWorld(m_matWorld);

	cMonster::Update();

	cGameObject::Update();
}

void cKelsaik::Idle_Update()
{
	switch (eIDLE)
	{
	case ROAMING:
		Idle_Roaming();
		break;
	case COMEBACK:
		Idle_Back_to_SquareOne();
		break;
	}
}

void cKelsaik::Idle_Roaming()
{
	//��ٸ��°���(ù����)
	if (!m_bWalkOnOff && !m_bStart)
	{
		m_bStart = true;
		m_state = MON_STATE_unarmedwait;
		m_fStopTime = (float)GetTickCount();
	}
	//��ٸ��� ����
	else if (!m_bWalkOnOff)
	{
		if (GetTickCount() - m_fStopTime > 4000.0f)
		{
			m_bWalkOnOff = true;
			m_bStart = false;
		}
	}
	//�ȴ°���.ó�������Ҷ�
	else if (m_bWalkOnOff && !m_bStart)
	{
		m_bStart = true;
		//�ð���� ��Ʈ�� ������ �簢������ ó���߾�� �̾��� �Ф�
		int plusminus = rand() % 2;
		int plusminus2 = rand() % 2;

		if (plusminus)
			plusminus = 1;
		else
			plusminus = -1;

		if (plusminus2)
			plusminus2 = 1;
		else
			plusminus2 = -1;

		int AreaX = rand() % (int)(m_fAreaRadius / 5.0f);
		int AreaZ = rand() % (int)(m_fAreaRadius / 5.0f);

		NextSpot = m_vBehaviorSpot + D3DXVECTOR3(plusminus*AreaX, 0, plusminus2*AreaZ);
	}
	//������ �������� �ȴ� ���.
	else if (m_bWalkOnOff)
	{
		m_state = MON_STATE_Walk;
		// u���� -> ���غ���
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v, v2;
		v2 = NextSpot - m_vPosition;
		//�̰ž����ָ� ���̸��νĵǼ� ����ũ�Ѵ�.
		v2.y = 0;
		D3DXVec3Normalize(&v, &v2);

		m_fCosVal = D3DXVec3Dot(&v, &u);
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < NextSpot.z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		m_vPosition += (0.3f*m_fRunSpeed * v);

		//�̰� �������� �˳��ϰ� ��� �Ѵ�. �ȱ׷��� ��Ȯ�ϰ� ���߷��� �θ������� ����. 
		if (D3DXVec3Length(&v2) < 1.0f)
		{
			m_bWalkOnOff = false;
			m_bStart = false;
		}
	}

	float Distance_Player_Monster = D3DXVec3Length(&(*g_vPlayerPos - m_vPosition));
	if (Distance_Player_Monster < m_fAreaRadius)
		MODE = AWAKE;

}

void cKelsaik::Idle_Back_to_SquareOne()
{
	//Ȥ�ø𸣴ϱ� ������Ͽ� ���� �Һ����� ��� �ʱ�ȭ ��������.
	{
		m_bStart = false;
		m_bWalkOnOff = false;
	}
	
	D3DXVECTOR3 tempV = m_vPosition - m_vBehaviorSpot;
	tempV.y = 0;
	if (D3DXVec3Length(&tempV) < 1.0f)
		eIDLE = ROAMING;
	else
	{
		m_state = MON_STATE_run;
		// u���� -> ���غ���
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v;
		D3DXVECTOR3 t;
		t = m_vBehaviorSpot - m_vPosition;
		D3DXVec3Normalize(&v, &t);

		m_fCosVal = D3DXVec3Dot(&v, &u);
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < m_vBehaviorSpot.z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		m_vPosition += (1.5f * m_fRunSpeed * v);
	}
}

void cKelsaik::Awake_Update()
{
	switch (eAWAKE)
	{
	case CHASE:
		Awake_Chase();
		break;
	case BATTLE:
		Awake_Battle();
		break;
	}
}

void cKelsaik::Awake_Chase()
{
	float Distance_Player_Monster = D3DXVec3Length(&(*g_vPlayerPos - m_vPosition));
	
	if (Distance_Player_Monster < m_fFightZone)
		eAWAKE = BATTLE;

	else if (D3DXVec3Length(&(m_vPosition - m_vBehaviorSpot)) > m_fTracableArea)
	{
		MODE = IDLE;
		eIDLE = COMEBACK;
	}

	m_state = MON_STATE_Walk;
	// u���� -> ���غ���
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 v;
	D3DXVec3Normalize(&v, &temp);

	m_fCosVal = D3DXVec3Dot(&v, &u);
	m_fCosVal = acosf(m_fCosVal);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	m_vPosition += (m_fRunSpeed * v);
}

void cKelsaik::Awake_Battle()
{
	//���� �״°�
	if (m_fHpCur <= 0)
		MODE = DEATH;

	//�������� ��Ÿĳ~~~~


}

void cKelsaik::Death_Update()
{
	switch (eDEATH)
	{
	case DIE:
		Death_Die();
		break;
	case REBIRTH:
		Death_Rebirth();
		break;
	}
}

void cKelsaik::Death_Die()
{
	m_fHpCur = 0.0f;

	m_state = MON_STATE_Death;
	m_fCurAnimTime = m_fAnimTime[MON_STATE_Death];
	m_bIsBlend = false;
	//�ִϸ��̼��� ó���ؾ� �ϹǷ� �ð��� �� ������ �ʿ��ϴ�.
	m_fTime += TIMEMANAGER->GetEllapsedTime();

	if (m_fCurAnimTime - 0.05 <= m_fTime)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		m_fTime = 0.0f;
		m_bAnimation = false;
		m_bAngleLock = false;
		m_bAtkTerm = !m_bAtkTerm;
		m_bIsGen = false;
		//������ ����� ���� ���
		m_fTimeofDeath = (float)GetTickCount();
	}
}

void cKelsaik::Death_Rebirth()
{
	m_vPosition = m_vBehaviorSpot;
	m_state = MON_STATE_unarmedwait;
	//m_currState = MON_STATE_unarmedwait;
	m_fRotY = 0.0f;
	m_vDirection = D3DXVECTOR3(1, 0, 0);
	m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
	m_fHpCur = 50000.0f;

	//5�ʵڿ� ��Ȱ.
	if (GetTickCount() - m_fTimeofDeath >= 5000.0f)
	{
		MODE = IDLE;
		eIDLE = ROAMING;
		m_pMonster->AnimAdvanceTime();
	}
}

void cKelsaik::Render()
{
	if (m_bIsGen)
	{
		m_pMonster->Render(NULL);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pMonster->Render(NULL);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

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

bool cKelsaik::isUseLocalAnim()
{

	if (
		m_state == MON_STATE_atk02 ||
		m_state == MON_STATE_atk01
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
