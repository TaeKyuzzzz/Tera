#include "stdafx.h"
#include "cMonster01.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

cMonster01::cMonster01()
	: m_pMonster(NULL)
	, m_currState(MON_STATE_Wait)
{
	m_state = MON_STATE_Wait;

	//루프애니메이션이 아닐때, 동작이 끝난걸 알려주는 변수.
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	float animTime[27] =
	{
		51, 46, 76, 76, 31,
		76, 76, 131, 1, 40,
		31, 30, 41, 41, 31,
		31, 50, 31, 50, 61,
		29, 35, 35, 66, 49,
		41, 97
	};

	memcpy(m_fAnimTime, animTime, sizeof(animTime));

	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] -= 1.0f;
	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] /= 30.0f;

	// 블랜딩 처리 할거니
	m_bIsBlend = true;

	//Monster01은 이런 특성을 가지고 있다.
	m_fAreaRadius = 150.0f;
	m_fRunSpeed = 0.5f;
}


cMonster01::~cMonster01()
{
	SAFE_DELETE(m_pMonster);
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



	//처음 젠되는 위치 설정

	m_vPosition = m_vBehaviorSpot;
}

void cMonster01::Update()
{
	//몬스터 죽는거
	if (KEYMANAGER->IsOnceKeyDown('5'))
	{
		//사망시점 기록
		m_fTimeofDeath = (float)GetTickCount();
		m_bIsGen = false;
	}

	//젠 되었을때
	if (m_bIsGen)
	{

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


			m_fTime += TIMEMANAGER->GetEllapsedTime();
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

		// 이동값이 있는 애니메이션 적용 시
		// 애니메이션 로컬을 현재 포지션으로 적용시키는 증가량을 계산 
		m_vBeforeAnimPos = m_vCurAnimPos;
		m_vCurAnimPos = D3DXVECTOR3(m_pDummyRoot->TransformationMatrix._41, 0, 0);


		//D3DXMATRIX matR, matT;
		D3DXMATRIX mat, matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);


		m_matWorld = matR * matT;

		//조작

		cMonster::Update();

		cGameObject::Update();
	}

	//죽었을때
	else
	{
		//다시 처음으로 설정

		m_vPosition = m_vBehaviorSpot;
		m_state = MON_STATE_Wait;
		m_currState = MON_STATE_Wait;
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
}

void cMonster01::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	if (m_bIsGen)
		m_pMonster->Render(NULL);

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "length : %f", D3DXVec3Length(&temp));
	RECT rc;
	SetRect(&rc, 20, 0, 200, 100);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 255, 0));

	cGameObject::Render();
}

bool cMonster01::isUseLocalAnim()
{
	if (
		m_state == MON_STATE_atk04
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

void cMonster01::SetAnimWorld()
{
	// 이동값이 있는 애니메이션의 스타트 월드 매트릭스를 세팅
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;

	m_matWorld = matR * matT;;
}

//몬스터는 연격동작이 없으므로 생략한다.
void cMonster01::ProcessCombo()
{
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
	temp = *g_vPlayerPos - m_vPosition;
	if (D3DXVec3Length(&temp) < m_fAreaRadius)
	{
		m_bAwake = true;
	}
	else
	{
		m_bAwake = false;
	}

	if (m_bAwake)
	{
		// u벡터 -> 기준벡터
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v;
		D3DXVec3Normalize(&v, &temp);

		m_fCosVal = D3DXVec3Dot(&v, &u);
		m_fCosVal = acosf(m_fCosVal);

		if (u.z < g_vPlayerPos->z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		D3DXVECTOR3 t, t2;
		m_vPosition += (m_fRunSpeed * v);
		//m_vPosition -= D3DXVECTOR3(1.0f, 0, 1.0f);
	}


	m_fRotY = m_fCosVal;

}
