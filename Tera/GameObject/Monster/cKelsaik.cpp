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

	//루프애니메이션이 아닐때, 동작이 끝난걸 알려주는 변수.
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

	// 블랜딩 처리 할거니
	//블렌드 처리하니깐 제식해버리더라구. 그래서 해제시켰다.
	m_bIsBlend = false;

	//Monster01은 이런 특성을 가지고 있다.
	m_fAreaRadius = 300.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.0f;
	m_fFightZone = 100.0f;
	m_fHpCur = 50000.0f;

	STATE = IDLE;

	// 패턴의 가짓 수
	m_nNumofPattern = 4;
	
	
	// 사용하는 파티클 등록
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
	
	m_fRotY = 4.7f;

	// 바운딩 박스 생성
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// 구 충돌 영역 생성(싸움존 거리)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);

	STATE = IDLE;
}

void cKelsaik::Update()
{
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	AnimUpdate();				// 애니메이션 진행
	
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


	UpdateWorld();				// 월드 갱신
	ParticleUpdate();			// 파티클 업데이트

	
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
	// u벡터 -> 기준벡터
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
	//몬스터 죽는거
	if (m_fHpCur <= 0)
		STATE = DIE;

	//나머지를 부타캐~~~~


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
	// 애니메이션 진행

	// 만약 현재 진행중인 애니와 진행해야될 애니가 다르다면 교체해야함
	if (m_currAnim != m_Anim)
	{
		if (m_bIsBlend) // 블렌드 처리를 해야 한다면
			m_pMonster->SetAnimationIndexBlend(m_Anim);
		else
			m_pMonster->SetAnimationIndex(m_Anim);

		m_currAnim = m_Anim;						// 현재 애니를 바뀔 애니로

		m_pMonster->AnimAdvanceTime();				// 한번 애니메이션을 진행시켜야함;
		m_fTime += TIMEMANAGER->GetEllapsedTime();	// 진행했으니 시간도 올려야지
	}

	// 이동값이 있는 애니메이션의 업데이트면
	// 애니메이션 스타트 지점의 월드에서 부터 업데이트
	// 아니면 평소처럼 적용된 월드에서 업데이트
	if (isUseLocalAnim())
		m_pMonster->Update(m_matAnimWorld);
	else
		m_pMonster->Update(m_matWorld);

	// 로컬에서 위치의 변화량이 있는 애니메이션을 위한 처리
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);


	m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
	m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);

	// 이동값이 있는 애니메이션 적용 시
	// 애니메이션 로컬을 현재 포지션으로 적용시키는 증가량을 계산 

	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x < 30.f)
		m_vPosition += (m_vDirection * (m_vCurAnimPos.x - m_vBeforeAnimPos.x));
	else
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
	}
}

// 현재 위치, 각도 정보를 통해 월드를 갱신하는 함수
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

// 렌더
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

// 로컬에서 위치 변화가 있는 애니메이션은 변화량을 따로 빼놔야함
bool cKelsaik::isUseLocalAnim()
{

	if (
		m_Anim == MON_Anim_atk02 ||
		m_Anim == MON_Anim_atk01
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
