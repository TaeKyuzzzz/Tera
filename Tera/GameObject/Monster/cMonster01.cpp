#include "stdafx.h"
#include "cMonster01.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

cMonster01::cMonster01()
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
		97, 41, 49, 66, 35,
		35, 29, 61, 50, 31, 
		50, 31, 31, 41, 41, 
		30, 31, 40, 1, 131, 
		76, 76, 31, 76, 76, 
		46, 51
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
	m_fRunSpeed = 1.0f;
	m_fFightZone = 100.0f;
	m_fHpCur = 100.0f;
}


cMonster01::~cMonster01()
{
	SAFE_DELETE(m_pMonster);
	SAFE_DELETE(m_pSphereR);
	SAFE_DELETE(m_pSphereL);
}

void cMonster01::Setup()
{
	cMonster::Setup();

	m_pMonster = new cSkinnedMesh;
	m_pMonster->Setup("XFile/Monster", "Moster01.X");
	m_pMonster->SetAnimationIndexBlend(m_currState);

	// 위치를 가진 루트 본
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Dummy_root");

	// 싸대기 때릴 양손 본
	m_pHandR = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-R-Hand");

	m_pHandL = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-L-Hand");

	////싸대기 판정 구체
	m_pSphereR = new cSpere;
	m_pSphereR->Setup(D3DXVECTOR3(0, 0, 0), 20);

	m_pSphereL = new cSpere;
	m_pSphereL->Setup(D3DXVECTOR3(0, 0, 0), 20);



	//처음 젠되는 위치 설정

	m_vPosition = m_vBehaviorSpot;

	// 바운딩 박스 생성
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// 구 충돌 영역 생성(싸움존 거리)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);
}

void cMonster01::Update()
{

	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	//몬스터 죽는거
	if (m_fHpCur <= 0)
	{
		//사망시점 기록
		m_fTimeofDeath = (float)GetTickCount();
		m_bIsGen = false;
	}

	//젠 되었을때
	if (m_bIsGen)
	{
		temp = *g_vPlayerPos - m_vPosition;

		MonoBehavior();


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



		// 이동처리!!
		//D3DXVECTOR3 beforePos = m_vPosition;
		//float		beforeRot = m_fRotY;
		//
		//if (m_fRotY <= 0.0f)
		//	m_fRotY += D3DX_PI * 2;
		//else if (m_fRotY >= D3DX_PI * 2)
		//	m_fRotY -= D3DX_PI * 2;
		//
		//D3DXMATRIX mat, matR, matT;
		//D3DXMatrixRotationY(&matR, m_fRotY);
		//
		//D3DXMatrixIdentity(&mat);
		//D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y + 55, m_vPosition.z);
		//m_pBoundingBox->SetWorld(matR * mat);
		//
		//m_pSpere->SetWorld(mat);

		/*	if (OBJECTMANAGER->IsCollision(this))
		{
		m_fRotY = beforeRot;
		m_vPosition = beforePos;
		D3DXMATRIX mat, matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);

		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y + 55, m_vPosition.z);
		m_pBoundingBox->SetWorld(matR * mat);

		m_pSpere->SetWorld(mat);
		}*/

		m_pSphereR->SetWorld(m_pHandR->CombinedTransformationMatrix);
		m_pSphereL->SetWorld(m_pHandL->CombinedTransformationMatrix);


		
		//조작

		Move();

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

	//죽었을때
	else
	{
		//다시 처음으로 설정

		m_vPosition = m_vBehaviorSpot;
		m_state = MON_STATE_unarmedwait;
		m_currState = MON_STATE_unarmedwait;
		m_fRotY = 0.0f;
		m_vDirection = D3DXVECTOR3(1, 0, 0);
		m_vPosition = m_vBehaviorSpot;
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);

		//5초뒤에 부활.
		if (GetTickCount() - m_fTimeofDeath >= 5000.0f)
		{
			m_bIsGen = true;
		}
	}


	// 공격
	if(m_state == MON_STATE_atk01)
	Attack(45.0f);
}

void cMonster01::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	if (m_bIsGen)
		m_pMonster->Render(NULL);

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "State : %d", m_state);
	RECT rc;
	SetRect(&rc, 0, 100, 200, 200);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 255, 0));

	cGameObject::Render();

	if (SightSpere && m_pSphereR)
		m_pSphereR->Render();
	if (SightSpere && m_pSphereL)
		m_pSphereL->Render();

	
	sprintf_s(szTemp, 1024, "%.1f %.1f %.1f", m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	SetRect(&rc, 0, 400, 200, 500);

	 pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 255, 0));
}

bool cMonster01::isUseLocalAnim()
{
	if (
		m_state == MON_STATE_atk02
		)
		return true;

	//이게 진짜 중요!!!
	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x > 10.0f)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		return true;
	}

	return false;
}

void cMonster01::SetAnimWorld()
{
	// 이동값이 있는 애니메이션의 스타트 월드 매트릭스를 세팅
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;
}

//몬스터가 데미지를 입었을때 보여주는 행동패턴
void cMonster01::ProcessDamaged()
{
}

void cMonster01::ProcessBigDamaged()
{
}

void cMonster01::ProcessDie()
{
}

void cMonster01::Move()
{
	//캐릭터 인식상태일때
	if (m_bAwake)
	{
		//적이 캐릭터를 인식이되면 기본상태는 해제.
		m_bIdle = false;

		//공격모드
		if (m_bFight)
		{

			if (!m_bAngleLock)
			{

				D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
				D3DXVECTOR3 v;
				D3DXVec3Normalize(&v, &temp);

				m_fCosVal = D3DXVec3Dot(&v, &u);
				m_fCosVal = acosf(m_fCosVal);

				if (m_vPosition.z < g_vPlayerPos->z)
					m_fCosVal = D3DX_PI * 2 - m_fCosVal;
			}

			if (!m_bAtkTerm && !m_bAnimation)
			{
				SetAnimWorld();
				//전투는 구간애니메이션 합으로 이루어져있으므로 이렇게 설정함.
				m_bAnimation = true;
				//공격중에는 방향을 바꾸지 않으므로 앵글락을 온시켜줍니다.
				m_bAngleLock = true;
				//전투모션은 atk01타입이다.
				m_state = MON_STATE_atk02;
				//현재 애니메이션 구간길이를 입력해줍니다.
				m_fCurAnimTime = m_fAnimTime[MON_STATE_atk02];
			}
			else if(m_bAtkTerm && !m_bAnimation)
			{
				//전투는 구간애니메이션 합으로 이루어져있으므로 이렇게 설정함.
				m_bAnimation = true;
				m_state = MON_STATE_Wait;
				m_fCurAnimTime = m_fAnimTime[MON_STATE_Wait];
			}


		}
		//애니메이션이 완료된 상태여야 중간에 캔슬되지 않으니 이 if문을 추가했다.
		else
		{
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
	}
	else
	{
		if (m_bIdle)
			m_state = MON_STATE_unarmedwait;

		else
		{
			D3DXVECTOR2 tt;
			tt.x = m_vPosition.x - m_vBehaviorSpot.x;
			tt.y = m_vPosition.z - m_vBehaviorSpot.z;

			//왜그런지 모르겠는데 이 값이 작아질수록 Idle로 바뀌는 시간이 길어진다.
			if (D3DXVec2Length(&tt) < 50.0f)
				m_bIdle = true;
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

				m_vPosition += (3.0f * m_fRunSpeed * v);
			}
		}
	}

	//구간애니메이션 처리부분.
	if (m_bAnimation)
	{
		//애니메이션을 처리해야 하므로 시간을 잴 변수가 필요하다.
		m_fTime += TIMEMANAGER->GetEllapsedTime();

		if (m_fCurAnimTime - 0.05<= m_fTime)
		{
			m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
			m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
			m_fTime = 0.0f;
			m_bAnimation = false;
			m_bAngleLock = false;
			m_bAtkTerm = !m_bAtkTerm;
		}
	}

	m_fRotY = m_fCosVal;
	
}

void cMonster01::Damaged()
{
}

void cMonster01::BigDamaged()
{
}

void cMonster01::Die()
{
}

//맵 위에서 보이는 단순행동패턴
void cMonster01::MonoBehavior(void)
{
	if (D3DXVec3Length(&temp) <= m_fAreaRadius)
	{
		m_bEscapeToggle = false;
		m_bAwake = true;
		if (D3DXVec3Length(&temp) < m_fFightZone)
		{
			m_bFight = true;
			m_bEscapeToggle2 = true;
			m_fEscapeTime2 = GetTickCount();
		}
		
		if(m_bEscapeToggle2)
		{
			if (GetTickCount() - m_fEscapeTime2 > 2000.0f && !m_bAnimation)
			{
				m_bFight = false;
				m_bAtkTerm = true;			//전투상태초기화.
			}
		}
	}
	
	//갓 탈출했으면
	else if(D3DXVec3Length(&temp) > m_fAreaRadius && !m_bEscapeToggle)
	{
		m_bEscapeToggle = true;
		m_fEscapeTime = GetTickCount();
	}

	if (m_bEscapeToggle && m_bAwake)
	{
		//탈출시점으로부터 5초가 지나면 다시 서식지로 돌아간다.
		if (GetTickCount() - m_fEscapeTime > 3000.0f)
			m_bAwake = false;
	}

}

bool cMonster01::Attack(float damage)
{
	if (!OBJECTMANAGER->GiveDamagedChara(m_pSphereR, damage))
	{
		if (OBJECTMANAGER->GiveDamagedChara(m_pSphereL, damage))
			return true;
	}
	else
		return true;

	return false;
}