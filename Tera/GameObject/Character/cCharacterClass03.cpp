#include "stdafx.h"
#include "cCharacterClass03.h"

#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"
#include "Particle\cParticleSet.h"

cCharacterClass03::cCharacterClass03()
{
	m_state = CH_STATE_Wait;
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	float animTime[60] =
	{
		16,34,10,34,10,29,58,16,31,46,10,29,49,
		31,25,37,30,28,26,61,91,73,65,1,55,42,54,
		55,25,27,55,21,52,33,25,8,106,29,49,22,43,
		52,52,27,15,34,24,63,17,73,47,76,31,61,24,
		21,19,21,26,61
	};

	memcpy(m_fAnimTime, animTime, sizeof(animTime));

	for (int i = 0; i < CH_STATE_COUNT; i++)
		m_fAnimTime[i] -= 1.0f;
	for (int i = 0; i < CH_STATE_COUNT; i++)
		m_fAnimTime[i] /= 30.0f;


	m_bIsBlend = true;
	m_bDoCombo = false;
	m_fCosVal = 0.0f;

	m_pParticleSet = PARTICLEMANAGER->GetParticle("gaiaCrash");
	//m_pParticleAura = PARTICLEMANAGER->GetParticle("aura");
	m_pParticleHeal = PARTICLEMANAGER->GetParticle("Heal");

	PARTICLEMANAGER->AddChild(m_pParticleSet);
	//PARTICLEMANAGER->AddChild(m_pParticleAura);
	PARTICLEMANAGER->AddChild(m_pParticleHeal);

	m_isDoEffect = false;
	m_isDoSkiilSound = false;
}


cCharacterClass03::~cCharacterClass03()
{
}

void cCharacterClass03::Setup()
{
	cCharacter::Setup();


}

void cCharacterClass03::Update()
{

	//Damaged(5.0f, D3DXVECTOR3(0,0,0));
	//BigDamaged();
	//Die();
	// 여기서도 애니메이션의 걸린 시간을 똑같이 진행
	//if(g_pKeyManager->IsOnceKeyDown('2'))
	m_fTime += TIMEMANAGER->GetEllapsedTime();

	// 애니메이션이 끝났는지 알아보고
	// 각 상황마다 다음 애니메이션 처리
	if (!m_bIsDone)
	{
		if (m_fCurAnimTime - 0.1f <= m_fTime)
		{
			m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
			m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);

			m_fCurAnimTime = 0.0f;
			m_fTime = 0.0f;
			m_bIsDone = false;

			CHARA_STATE cs = m_state;
			// 연격 처리 함수
			ProcessCombo();
			// 데미지, 사망 처리
			ProcessDamaged();

			//
			ProcessGaiaCrash();

			//죽으면 뻗어야 되는데, 일어나버리니깐 뒤에 && 추가한거야.
			if (cs == m_state && cs != CH_STATE_Dearhwait)
			{
				m_state = CH_STATE_Wait;
				m_bIsBlend = false;
			}
		}

		SkillProcess(); // 스킬 이펙트, 타격 처리
		AttSound(); // 공격 사운드 처리
	}

	// 버튼 조작
	if (!isOptionMode)
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
		{
			// 일반 연격 시작
			if (m_state == CH_STATE_combo1 ||
				m_state == CH_STATE_combo2 ||
				m_state == CH_STATE_combo3 ||
				m_state == CH_STATE_combo4)
			{
				// 연격을 하기 위한 콤여 여부 불 값 갱신 
				if (!m_bDoCombo)
				{
					if (m_fTime >= m_fCurAnimTime - 0.35f)
					{
						m_bDoCombo = true;
						m_fRotY = m_fCosVal;
					}
				}
			}
			// 첫타
			else if (m_state == CH_STATE_Wait || m_state == CH_STATE_run)
			{
				m_isDoSkiilSound = false;
				// 정면 카메라 방향 위치 이동 애니메이션 시 해야되는 작업
				m_fRotY = m_fCosVal;
				// 위치 이동 애니메이션 시 해야되는 작업
				SetAnimWorld();

				m_state = CH_STATE_combo1;
				m_fCurAnimTime = m_fAnimTime[CH_STATE_combo1];
				m_fTime = 0.0f;
				m_bIsDone = false;
			}
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON) &&
			(m_state == CH_STATE_run || m_state == CH_STATE_Wait ||
				m_state == CH_STATE_combo1R || m_state == CH_STATE_combo2R || m_state == CH_STATE_combo3R))
		{

			GetAngle();

			SetAnimWorld();

			// 구르기
			m_state = CH_STATE_tumbling;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_tumbling];
			m_fTime = 0.0f;
			m_bIsDone = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			SetAnimWorld();

			// 여기는 점프를 만들어야 합니다.
			m_state = CH_STATE_DwonBlow;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_DwonBlow];
			m_fTime = 0.0f;
			m_bIsDone = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown('1') && m_state == CH_STATE_Wait)
		{
			// 가이아 크래시
			SetAnimWorld();

			// 여기는 점프를 만들어야 합니다.
			m_state = CH_STATE_gaiaCrush01;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_gaiaCrush01];
			m_fTime = 0.0f;
			m_bIsDone = false;
			m_isDoEffect = false;
			m_isDoSkiilSound = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown('2') && m_state == CH_STATE_Wait)
		{
			// 커팅슬래시

			SetAnimWorld();

			// 여기는 점프를 만들어야 합니다.
			m_state = CH_STATE_CuttingSlash;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_CuttingSlash];
			m_fTime = 0.0f;
			m_bIsDone = false;
			m_isDoEffect = false;
			m_isDoSkiilSound = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown('3') && m_state == CH_STATE_Wait)
		{
			// 컷헤드

			SetAnimWorld();

			// 여기는 점프를 만들어야 합니다.
			m_state = CH_STATE_CutHead;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_CutHead];
			m_fTime = 0.0f;
			m_bIsDone = false;
			m_isDoEffect = false;
			m_isDoSkiilSound = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown('4') && m_state == CH_STATE_Wait)
		{
			SetAnimWorld();

			// 여기는 점프를 만들어야 합니다.
			m_state = CH_STATE_StingerBlade;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_StingerBlade];
			m_fTime = 0.0f;
			m_bIsDone = false;
			m_isDoEffect = false;
			m_isDoSkiilSound = false;
		}

		// 스킬 셋에 따른 스킬을 나가게 해야해 ( 포션 사용도 )
		else if (m_bIsDone)
		{
			if (m_state == CH_STATE_run)
				m_bIsBlend = true;
			m_state = CH_STATE_Wait;
		}
	}
	else
	{
		if (m_bIsDone)
		{
			if (m_state == CH_STATE_run)
				m_bIsBlend = true;
			m_state = CH_STATE_Wait;
		}
	}




	// 원래는 캐릭터 클래스가 이동을 관장하게 하려고 했는데
	// m_state 값에 따라서 이동의 제약을 줘야해서 포기,
	// 그냥 여기 클래스에서 이동도 처리하기로 했음 
	//cCharacter::Update();

	// 이동

	if ((KEYMANAGER->IsStayKeyDown('W') ||
		KEYMANAGER->IsStayKeyDown('A') ||
		KEYMANAGER->IsStayKeyDown('D') ||
		KEYMANAGER->IsStayKeyDown('S')) &&
		(m_state == CH_STATE_Wait || m_state == CH_STATE_run))
	{
		//if (m_state == CH_STATE_Wait)
		//	m_bIsBlend = true;
		m_state = CH_STATE_run;
	}

	Move();
	/////////////////
	// 파티클 테스트 입니다.
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	if (KEYMANAGER->IsOnceKeyDown('P'))
	{
		m_pParticleHeal->SetWorld(mat);
		m_pParticleHeal->Start();
	}

	//m_pParticleAura->SetWorld(mat);
	//m_pParticleAura->Update();
	//m_pParticleSet->Update();
	//m_pParticleHeal->Update();

	// 스킬 공격 ㅊ ㅓ리

	cCharacter::Update();
	if (m_fHpCur < 0)
	{
		SOUNDMANAGER->Play("PCDie");
		Die();
	}
}

void cCharacterClass03::Render()
{

	//m_pParticleSet->Render();
	//m_pParticleAura->Render();
	//m_pParticleHeal->Render();



	cCharacter::Render();
}

void cCharacterClass03::SetAnimWorld()
{
	// 이동값이 있는 애니메이션의 스타트 월드 매트릭스를 세팅
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;;
}

void cCharacterClass03::ProcessCombo()
{
	// 연격 동작을 연결 시켜주는 함수
	// 애니메이션을 끝났을때 실행되며 , 콤보여부 불값에 따라 다음
	// 애니메이션을 적용
	if (m_bDoCombo)
	{
		//m_fRotY = m_fCosVal;
		SetAnimWorld();
	}

	if (m_state == CH_STATE_combo1)
	{
		if (m_bDoCombo)
		{

			m_bDoCombo = false;
			m_state = CH_STATE_combo2;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo2];
			m_bIsDone = false;
			m_bIsBlend = false;
			m_isDoSkiilSound = false;
		}
		else
		{
			m_state = CH_STATE_combo1R;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo1R];
			m_bIsDone = false;
			m_bIsBlend = false;
		}
	}
	else if (m_state == CH_STATE_combo1R)
	{
		m_state = CH_STATE_Wait;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_combo2)
	{
		if (m_bDoCombo)
		{

			m_bDoCombo = false;
			m_state = CH_STATE_combo3;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo3];
			m_bIsDone = false;
			m_bIsBlend = false;
			m_isDoSkiilSound = false;
		}
		else
		{
			m_state = CH_STATE_combo2R;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo2R];
			m_bIsDone = false;
			m_bIsBlend = false;
		}
	}
	else if (m_state == CH_STATE_combo2R)
	{
		m_state = CH_STATE_Wait;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_combo3)
	{
		if (m_bDoCombo)
		{

			m_bDoCombo = false;
			m_state = CH_STATE_combo4;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo4];
			m_bIsDone = false;
			m_bIsBlend = false;
			m_isDoSkiilSound = false;
		}
		else
		{
			m_state = CH_STATE_combo3R;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo3R];
			m_bIsDone = false;
			m_bIsBlend = false;
		}
	}

}

void cCharacterClass03::ProcessDamaged()
{
	if (m_state == CH_STATE_bReactionStart)
	{
		m_state = CH_STATE_bReactionCom2;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionCom2];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_bReactionStart3)
	{
		SetAnimWorld();
		m_state = CH_STATE_bReactionLand3;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionLand3];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_Death)
	{
		m_state = CH_STATE_Dearhwait;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_Dearhwait];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_bReactionLand3)
	{
		m_state = CH_STATE_bReactionCom3;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionCom3];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_Dearhwait)
	{
		m_state == CH_STATE_Dearhwait;
	}
}

void cCharacterClass03::ProcessGaiaCrash()
{
	if (m_state == CH_STATE_gaiaCrush01)
	{
		SetAnimWorld();
		m_state = CH_STATE_gaiaCrush02;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_gaiaCrush02];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
	else if (m_state == CH_STATE_gaiaCrush02)
	{
		SetAnimWorld();
		m_state = CH_STATE_gaiaCrush03;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_gaiaCrush03];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
}

void cCharacterClass03::ProcessBigDamaged()
{
}

void cCharacterClass03::ProcessDie()
{
}

void cCharacterClass03::Move()
{
	// 이동에 관련된 함수
	D3DXVECTOR3 beforePos = m_vPosition;
	float		beforeRot = m_fRotY;

	if (KEYMANAGER->IsStayKeyDown('A') && m_state == CH_STATE_run)
	{
		m_fRotY = m_fCosVal + D3DX_PI * 1.5f;

		if (!OBJECTMANAGER->IsCollision(this))
			m_vPosition += (m_vDirection * m_fSpeed);
	}
	else if (KEYMANAGER->IsStayKeyDown('D') && m_state == CH_STATE_run)
	{
		m_fRotY = m_fCosVal + D3DX_PI * 0.5;
		if (!OBJECTMANAGER->IsCollision(this))
			m_vPosition += (m_vDirection * m_fSpeed);
	}
	if (KEYMANAGER->IsStayKeyDown('W') && m_state == CH_STATE_run)
	{
		if (KEYMANAGER->IsStayKeyDown('A'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 1.75f;
			//m_vPosition += (m_vDirection * m_fSpeed);
		}
		else if (KEYMANAGER->IsStayKeyDown('D'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 0.25;
			//m_vPosition += (m_vDirection * m_fSpeed);
		}
		else
		{
			m_fRotY = m_fCosVal;
			if (!OBJECTMANAGER->IsCollision(this))
				m_vPosition += (m_vDirection * m_fSpeed);
		}
	}
	if (KEYMANAGER->IsStayKeyDown('S') && m_state == CH_STATE_run)
	{
		if (KEYMANAGER->IsStayKeyDown('A'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 1.25f;
			//m_vPosition += (m_vDirection * m_fSpeed);
		}
		else if (KEYMANAGER->IsStayKeyDown('D'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 0.75;
			//m_vPosition += (m_vDirection * m_fSpeed);
		}
		else
		{
			m_fRotY = m_fCosVal + D3DX_PI;
			if (!OBJECTMANAGER->IsCollision(this))
				m_vPosition += (m_vDirection * m_fSpeed);
		}
	}

	if (m_fRotY < 0.0f)
		m_fRotY += (D3DX_PI * 2);
	else if (m_fRotY > D3DX_PI * 2)
		m_fRotY -= D3DX_PI * 2;


	D3DXMATRIX mat, matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y + 15, m_vPosition.z);
	m_pBoundingBox->SetWorld(matR * mat);

	m_pSpere->SetWorld(mat);

	if (OBJECTMANAGER->IsCollision(this))
	{
		m_fRotY = beforeRot;
		m_vPosition = beforePos;
		D3DXMATRIX mat, matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);

		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y + 15, m_vPosition.z);
		m_pBoundingBox->SetWorld(matR * mat);

		m_pSpere->SetWorld(mat);
	}



	if (m_vCurAnimPos.x - m_vBeforeAnimPos.x < 30.0f)
		m_vPosition += (m_vDirection * (m_vCurAnimPos.x - m_vBeforeAnimPos.x));
	else
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
	}

	//D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
}

void cCharacterClass03::Damaged(float damage, D3DXVECTOR3 dir)
{

	if (m_state == CH_STATE_bReactionStart ||
		m_state == CH_STATE_bReactionStart3 ||
		m_state == CH_STATE_Dearhwait ||
		m_state == CH_STATE_Death ||
		m_state == CH_STATE_groggy1 ||
		(m_isPossibleDamaged == false)) return;

	m_isPossibleDamaged = false;
	m_PossbleDamagedTime = 0.0f;

	D3DXVECTOR3 u = dir - m_vPosition;
	u.y = 0;
	D3DXVec3Normalize(&u, &u);
	m_fCosVal = D3DXVec3Dot(&u, &D3DXVECTOR3(1, 0, 0));

	// nan 값 나오지 않게 예외처리..
	if (m_fCosVal < -1.0f)
		m_fCosVal = -0.99f;
	else if (m_fCosVal > 1.0f)
		m_fCosVal = 0.99;

	m_fRotY = acosf(m_fCosVal);

	cCharacter::Damaged();

	m_fHpCur -= damage;

	if (damage < m_fHpMax / 10.0f)
	{
		m_state = CH_STATE_groggy1;
		m_fCurAnimTime = 0.5f;
		m_bIsBlend = true;
		m_bIsDone = false;

		SOUNDMANAGER->Play("PCDamaged");
	}
	else if (damage < m_fHpMax / 6.0f)
	{
		SetAnimWorld();
		m_state = CH_STATE_bReactionStart;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart];
		m_bIsDone = false;
		m_bIsBlend = false;
		SOUNDMANAGER->Play("PCBigDamaged");
	}
	else
	{
		SetAnimWorld();
		m_state = CH_STATE_bReactionStart3;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart3];
		m_bIsDone = false;
		m_bIsBlend = false;
		SOUNDMANAGER->Play("PCBigDamaged");
	}

	if (m_fHpCur < 0)
	{
		SOUNDMANAGER->Play("PCDie");
		Die();
	}
}

void cCharacterClass03::Damaged(float damage, D3DXVECTOR3 dir, CONDITION con, float per)
{

	if (m_state == CH_STATE_bReactionStart ||
		m_state == CH_STATE_bReactionStart3 ||
		m_state == CH_STATE_Dearhwait ||
		m_state == CH_STATE_Death ||
		m_state == CH_STATE_groggy1 ||
		(m_isPossibleDamaged == false)) return;

	m_isPossibleDamaged = false;
	m_PossbleDamagedTime = 0.0f;

	D3DXVECTOR3 u = dir - m_vPosition;
	u.y = 0;
	D3DXVec3Normalize(&u, &u);
	m_fCosVal = D3DXVec3Dot(&u, &D3DXVECTOR3(1, 0, 0));

	// nan 값 나오지 않게 예외처리..
	if (m_fCosVal < -1.0f)
		m_fCosVal = -0.99f;
	else if (m_fCosVal > 1.0f)
		m_fCosVal = 0.99;

	m_fRotY = acosf(m_fCosVal);

	cCharacter::Damaged();

	m_fHpCur -= damage;

	if (damage < m_fHpMax / 10.0f)
	{
		m_state = CH_STATE_groggy1;
		m_fCurAnimTime = 0.5f;
		m_bIsBlend = true;
		m_bIsDone = false;

		SOUNDMANAGER->Play("PCDamaged");
	}
	else if (damage < m_fHpMax / 6.0f)
	{
		SetAnimWorld();
		m_state = CH_STATE_bReactionStart;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart];
		m_bIsDone = false;
		m_bIsBlend = false;
		SOUNDMANAGER->Play("PCBigDamaged");
	}
	else
	{
		SetAnimWorld();
		m_state = CH_STATE_bReactionStart3;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart3];
		m_bIsDone = false;
		m_bIsBlend = false;
		SOUNDMANAGER->Play("PCBigDamaged");
	}

	if (m_fHpCur < 0)
	{
		SOUNDMANAGER->Play("PCDie");
		Die();
	}

	if (rand() % 100 < per)
	{
		if (con == m_eCondition)
		{
			m_fHpCur = 0;
			Die();
			return;
		}
		else if (con == CDT_BURN && m_eCondition == CDT_ICE)
			m_eCondition = CDT_NORMAL;
		else if (con == CDT_ICE && m_eCondition == CDT_BURN)
			m_eCondition = CDT_NORMAL;
		else
			m_eCondition = con;

		switch (m_eCondition)
		{
		case CDT_NORMAL:
			m_pConditionBurn->End();
			m_pConditionIce->End();
			m_fSpeed = 1.0f;
			break;
		case CDT_BURN:
			m_pConditionBurn->Start();
			break;
		case CDT_ICE:
			m_pConditionIce->Start();
			m_fSpeed = 0.6;
			break;
		case CDT_STURN:
			break;
		default:
			break;
		}
	}
}

void cCharacterClass03::BigDamaged()
{
	if (KEYMANAGER->IsOnceKeyDown('E'))
	{
		SetAnimWorld();

		m_state = CH_STATE_bReactionStart3;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart3];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
}

void cCharacterClass03::Die()
{
	m_fHpCur = 0.0f;

	SetAnimWorld();
	m_state = CH_STATE_Death;
	m_fCurAnimTime = m_fAnimTime[CH_STATE_Death];
	m_bIsDone = false;
	m_bIsBlend = false;
}

void cCharacterClass03::SkillProcess()
{
	D3DXMATRIX matR, matT;

	// 이펙트 있는 스킬의 타격, 파티클, 사운드 처리
	if (!m_isDoEffect)
	{
		D3DXMatrixRotationY(&matR, m_fRotY);
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		if (m_state == CH_STATE_gaiaCrush02)
		{
			if (m_fTime >= m_fAnimTime[CH_STATE_gaiaCrush02] - 0.85f)
			{
				m_isDoEffect = true;
				m_pParticleSet->SetWorld(matR * matT);
				m_pParticleSet->Start();

				// 바운딩 박스 만들어서 몹과 충돌
				cBoundingBox hitBox;
				hitBox.Setup(D3DXVECTOR3(0, 0, -60), D3DXVECTOR3(100, 10, 60));
				hitBox.SetWorld(matR * matT);
				OBJECTMANAGER->GiveDamagedMonster(&hitBox, m_fAttack * 3.0f);
				CAMERAMANAGER->Shaking(0.275f);
				//SOUNDMANAGER->Play("PCSkill01");
			}

		}
		else if (m_state == CH_STATE_CuttingSlash && m_fTime >= m_fAnimTime[CH_STATE_CuttingSlash] - 1.1f)
		{
			m_isDoEffect = true;
			m_pParticleSet->SetWorld(matR * matT);
			m_pParticleSet->Start();

			// 바운딩 박스 만들어서 몹과 충돌
			cBoundingBox hitBox;
			hitBox.Setup(D3DXVECTOR3(0, 0, -60), D3DXVECTOR3(100, 10, 60));
			hitBox.SetWorld(matR * matT);
			OBJECTMANAGER->GiveDamagedMonster(&hitBox, m_fAttack * 3.0f);
			CAMERAMANAGER->Shaking(0.275f);

		}
	}
}

void cCharacterClass03::AttSound()
{
	if (!m_isDoSkiilSound)
	{
		if (m_state == CH_STATE_combo1 && m_fTime >= m_fAnimTime[CH_STATE_combo1] - 0.5f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCAtt01");
		}
		else if (m_state == CH_STATE_combo2 && m_fTime >= m_fAnimTime[CH_STATE_combo2] - 0.5f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCAtt02");
		}
		else if (m_state == CH_STATE_combo3 && m_fTime >= m_fAnimTime[CH_STATE_combo3] - 0.4f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCAtt03");
		}
		else if (m_state == CH_STATE_combo4 && m_fTime >= m_fAnimTime[CH_STATE_combo4] - 1.2f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCAtt04");
		}
		else if (m_state == CH_STATE_gaiaCrush02 && m_fTime >= m_fAnimTime[CH_STATE_gaiaCrush02] - 1.6f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCSkill01");
		}
		else if (m_state == CH_STATE_CuttingSlash && m_fTime >= m_fAnimTime[CH_STATE_CuttingSlash] - 1.5f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCSkill01");
		}
		else if (m_state == CH_STATE_CutHead && m_fTime >= m_fAnimTime[CH_STATE_CutHead] - 1.5f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCSkill01");
		}
		else if (m_state == CH_STATE_StingerBlade && m_fTime >= m_fAnimTime[CH_STATE_StingerBlade] - 1.5f)
		{
			m_isDoSkiilSound = true;
			SOUNDMANAGER->Play("PCSkill01");
		}
	}
}

void cCharacterClass03::GetAngle()
{
	if (KEYMANAGER->IsStayKeyDown('A'))
	{
		m_fRotY = m_fCosVal + D3DX_PI * 1.5f;
	}
	else if (KEYMANAGER->IsStayKeyDown('D'))
	{
		m_fRotY = m_fCosVal + D3DX_PI * 0.5;
	}
	if (KEYMANAGER->IsStayKeyDown('W'))
	{
		if (KEYMANAGER->IsStayKeyDown('A'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 1.75f;
		}
		else if (KEYMANAGER->IsStayKeyDown('D'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 0.25;
		}
		else
		{
			m_fRotY = m_fCosVal;
		}
	}
	if (KEYMANAGER->IsStayKeyDown('S'))
	{
		if (KEYMANAGER->IsStayKeyDown('A'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 1.25f;
		}
		else if (KEYMANAGER->IsStayKeyDown('D'))
		{
			m_fRotY = m_fCosVal + D3DX_PI * 0.75;
		}
		else
		{
			m_fRotY = m_fCosVal + D3DX_PI;
		}
	}

	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
}

