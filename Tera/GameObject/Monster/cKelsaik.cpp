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

	// 블랜딩 처리 할거니
	//블렌드 처리하니깐 제식해버리더라구. 그래서 해제시켰다.
	m_bIsBlend = false;

	//Monster01은 이런 특성을 가지고 있다.
	m_fAreaRadius = 200.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.5f;
	m_fFightZone = 100.0f;
	m_fHpCur = 50000.0f;

	STATE = IDLE;

	// 패턴의 가짓 수
	m_nNumofPattern = 4;
	m_fPatternCostTime = 0.0f;

	m_pEffectCost = true;
	// 사용하는 파티클 등록
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
	//m_pMonster->Setup("XFile/Monster", "Kelsaik.X"); // Kelsaik2 Kelsaik
	m_pMonster = SKINNEDMESHMANAGER->GetSkinnedMesh("XFile/Monster", "kelsaik3.X");
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
	m_isDoingPattern = false;
	m_partternCost = true;
}

void cKelsaik::Update()
{
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;
	//m_pBIP->TransformationMatrix._42 = m_matWorld._42;

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
	case TURN :
		Turn_Update();
		break;
	case WALK :
		Walk_Update();
		break;
	case DIE :
		Death_Update();
	}


	UpdateWorld();				// 월드 갱신
	ParticleUpdate();			// 파티클 위치 업데이트
	CreatePatternCost();
	
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
	else if(isEndPattern())
	{
		ChangeState(BATTLE);
	}
	else if(m_fTime > 0.8f)
	{
		CAMERAMANAGER->Shaking(0.06f);
	}

	//if (isPlayerInDistance())
	//	ChangeState(WALK);
}

void cKelsaik::Awake_Chase()
{

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

	// 플레이어가 공격범위 밖으로 나가면 추적시작
	if (!isPlayerInDistance(m_fAreaRadius) && !m_isDoingPattern)
	{
		ChangeState(WALK);
		return;
	}
	else if (!m_isDoingPattern)
	{
		// 여기서 자연스럽게 각도를 바꾸면 좋겟다..
		//SetAngleWithPlayer();
		//ChangeAnim(MON_Anim_Wait, true);
		//m_partternCost = false;
	}
	
	// 플레이어가 공격범위 안쪽이면 공격
	
	if (m_partternCost)
	{
		// 일단 패턴을 배치하고
		m_nPatternNum = rand() % NUMOFPATTERN;
		
		SetTargetAngle(); // 타겟의 각도를 잰 뒤,

		// 타겟의 위치에 따라 고개를 돌리는거임
		if (m_fTargetAngle >= D3DX_PI * 0.25 && m_fTargetAngle < D3DX_PI * 0.75)
			m_nPatternNum = RIGHTTURN;
		else if (m_fTargetAngle >= D3DX_PI * 0.75 && m_fTargetAngle > D3DX_PI * 1.25)
			m_nPatternNum = BACKTURN;
		else if (m_fTargetAngle >= D3DX_PI * 1.25 && m_fTargetAngle > D3DX_PI * 1.75)
			m_nPatternNum = LEFTTURN;

		m_partternCost = false;
		m_isDoingPattern = true;
		m_pEffectCost = true;

	}

	if (m_isDoingPattern)
	{
		switch (m_nPatternNum)
		{
		case 0			:	AttackPattern01();	break;
		case 1			:	AttackPattern02();	break;
		case 2			:	AttackPattern03();	break;
		case LEFTTURN	:	TurnLeft();			break;
		case RIGHTTURN	:	TurnRight();		break;
		case BACKTURN	:	TurnBack();			break;

		}
	}
}

void cKelsaik::Turn_Update()
{
	// 회전 무브 == 51 프레임 -> 51 / 30 초 걸림
	if (m_Anim != MON_Anim_roundmove01 && m_Anim != MON_Anim_roundmove02)
	{
		SetTargetAngle();
		
		if (m_vPosition.z < g_vPlayerPos->z)
			ChangeAnim(MON_Anim_roundmove01,true);
		else
			ChangeAnim(MON_Anim_roundmove02,true);


		SetAnimWorld();
	}
	else if(!isEndPattern())
	{
		// 매 시간마다 월드 로테이트를 거꾸로 돌려야 될거같은데..
		if (m_Anim == MON_Anim_roundmove01)
		{
			// 빼야해
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
			// 더해야해
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
	if (isPlayerInDistance(m_fAreaRadius))
	{
		ChangeState(BATTLE);
		return;
	}

	ChangeAnim(MON_Anim_Walk,true);
	
	SetAngleWithPlayer();
	
	D3DXVECTOR3 TargetPos = *g_vPlayerPos - m_vPosition;
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	
	m_vPosition += (m_fRunSpeed * TargetPos);
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
	m_fTime += TIMEMANAGER->GetEllapsedTime();
	// 로컬에서 위치의 변화량이 있는 애니메이션을 위한 처리
	m_vBeforeAnimPos = m_vCurAnimPos;
	m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);


	m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
	m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);

	// 이동값이 있는 애니메이션 적용 시
	// 애니메이션 로컬을 현재 포지션으로 적용시키는 증가량을 계산 
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

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "%d RotY : %.1f target : %.1f", m_Anim, m_fRotY, m_fTargetAngle);
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
		m_Anim == MON_Anim_atk01 ||
		m_Anim == MON_Anim_atk02 
		//m_Anim == MON_Anim_roundmove02 ||
		//m_Anim == MON_Anim_roundmove01
		)
		return true;

	//이게 진짜 중요!!! 애니메이션 자체에 움직임이 심한경우 이처리를 해준다.
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

void cKelsaik::ChangeAnim(MON_Anim anim, bool isBlend)
{
	m_fTime = 0.0f;

	m_bIsBlend = isBlend;

	m_Anim = anim;
	m_fCurAnimTime = m_fAnimTime[anim];

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
	if (!m_partternCost)
	{
		m_fPatternCostTime += TIMEMANAGER->GetEllapsedTime();
		if (m_fPatternCostTime >= 10.0f)
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

void cKelsaik::AttackPattern01()
{
	if (m_Anim != MON_Anim_atk01)
	{
		// 패턴 처음 시작
		ChangeAnim(MON_Anim_atk01,true);
		SetAngleWithPlayer();
		SetAnimWorld();
	}
	else
	{
		// 패턴이 끝났다면
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // 파티클 출력과 함께 데미지를 주자!
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
				CAMERAMANAGER->Shaking(0.1f);
			}
		}
	}
}

void cKelsaik::AttackPattern02()
{
	if (m_Anim != MON_Anim_atk02)
	{
		// 패턴 처음 시작
		ChangeAnim(MON_Anim_atk02, true);
		SetAngleWithPlayer();
		SetAnimWorld();
	}
	else
	{
		// 패턴이 끝났다면
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // 파티클 출력과 함께 데미지를 주자!
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
				CAMERAMANAGER->Shaking(0.1f);
			}
		}
	}
}

void cKelsaik::AttackPattern03()
{
	if (m_Anim != MON_Anim_ReactonAtk)
	{
		// 패턴 처음 시작
		ChangeAnim(MON_Anim_ReactonAtk, true);
		SetAngleWithPlayer();
		SetAnimWorld();
	}
	else
	{
		// 패턴이 끝났다면
		if (isEndPattern())
		{
			ChangeAnim(MON_Anim_Wait, false);
			m_isDoingPattern = false;
		}
		else // 파티클 출력과 함께 데미지를 주자!
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

				mat._41 = m_pHandR->CombinedTransformationMatrix._41;
				mat._42 = m_vPosition.y;
				mat._43 = m_pHandR->CombinedTransformationMatrix._43;
				m_pFireEffect->SetWorld(mat);
				m_pFireEffect->Start();
				CAMERAMANAGER->Shaking(0.1f);
			}
		}
	}
}

void cKelsaik::TurnLeft()
{
}

void cKelsaik::TurnRight()
{
}

void cKelsaik::TurnBack()
{
}

