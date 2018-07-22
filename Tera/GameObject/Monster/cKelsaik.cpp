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



	//루프애니메이션이 아닐때, 동작이 끝난걸 알려주는 변수.
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

	// 블랜딩 처리 할거니
	//블렌드 처리하니깐 제식해버리더라구. 그래서 해제시켰다.
	m_bIsBlend = false;

	//Monster01은 이런 특성을 가지고 있다.
	m_fAreaRadius = 300.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.0f;
	m_fFightZone = 100.0f;
	m_fHpCur = 50000.0f;

	MODE = IDLE;
	eIDLE = ROAMING;
	eAWAKE = CHASE;
	eDEATH = DIE;

	// 패턴의 가짓 수
	m_nNumofPattern = 4;
	//처음에 얘로 셋팅해놓는다.
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

	// 위치를 가진 루트 본
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Dummy_root");

	m_pBIP = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01");

	// 싸대기 때릴 양손 본
	m_pHandR = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-R-Hand");

	m_pHandL = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-L-Hand");

	////양발 판정 구체
	m_pSphereR = new cSpere;
	m_pSphereR->Setup(D3DXVECTOR3(0, 0, 0), 50);

	m_pSphereL = new cSpere;
	m_pSphereL->Setup(D3DXVECTOR3(0, 0, 0), 50);



	//처음 젠되는 위치 설정

	m_vPosition = m_vBehaviorSpot;

	// 바운딩 박스 생성
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// 구 충돌 영역 생성(싸움존 거리)
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

	// 애니메이션 진행
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

	// 이동값이 있는 애니메이션의 업데이트면
	// 애니메이션 스타트 지점의 월드에서 부터 업데이트
	// 아니면 평소처럼 적용된 월드에서 업데이트
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

	// 이동값이 있는 애니메이션 적용 시
	// 애니메이션 로컬을 현재 포지션으로 적용시키는 증가량을 계산 
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
	//기다리는과정(첫세팅)
	if (!m_bWalkOnOff && !m_bStart)
	{
		m_bStart = true;
		m_state = MON_STATE_unarmedwait;
		m_fStopTime = (float)GetTickCount();
	}
	//기다리는 과정
	else if (!m_bWalkOnOff)
	{
		if (GetTickCount() - m_fStopTime > 4000.0f)
		{
			m_bWalkOnOff = true;
			m_bStart = false;
		}
	}
	//걷는과정.처음셋팅할때
	else if (m_bWalkOnOff && !m_bStart)
	{
		m_bStart = true;
		//시간없어서 패트롤 영역을 사각형으로 처리했어요 미안해 ㅠㅠ
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
	//임의의 지점까지 걷는 모션.
	else if (m_bWalkOnOff)
	{
		m_state = MON_STATE_Walk;
		// u벡터 -> 기준벡터
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v, v2;
		v2 = NextSpot - m_vPosition;
		//이거안해주면 높이맵인식되서 문워크한다.
		v2.y = 0;
		D3DXVec3Normalize(&v, &v2);

		m_fCosVal = D3DXVec3Dot(&v, &u);
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < NextSpot.z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		m_vPosition += (0.3f*m_fRunSpeed * v);

		//이거 오차범위 넉넉하게 줘야 한다. 안그러면 정확하게 맞추려고 부르르르르 떤다. 
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
	//혹시모르니깐 어슬렁패턴에 쓰인 불변수는 모두 초기화 시켜주자.
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
		// u벡터 -> 기준벡터
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
	// u벡터 -> 기준벡터
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
	//몬스터 죽는거
	if (m_fHpCur <= 0)
		MODE = DEATH;

	//나머지를 부타캐~~~~


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
	//애니메이션을 처리해야 하므로 시간을 잴 변수가 필요하다.
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
		//완전히 사라진 시점 기록
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

	//5초뒤에 부활.
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


// 이동값이 있는 애니메이션의 스타트 월드 매트릭스를 세팅
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

	//이게 진짜 중요!!! 애니메이션 자체에 움직임이 심한경우 이처리를 해준다.
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 10.0f)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}


	return false;
}
