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

	//�����ִϸ��̼��� �ƴҶ�, ������ ������ �˷��ִ� ����.
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

	// ���� ó�� �ҰŴ�
	//���� ó���ϴϱ� �����ع�������. �׷��� �������״�.
	m_bIsBlend = false;

	//Monster01�� �̷� Ư���� ������ �ִ�.
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

	// ��ġ�� ���� ��Ʈ ��
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Dummy_root");

	// �δ�� ���� ��� ��
	m_pHandR = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-R-Hand");

	m_pHandL = (ST_BONE*)D3DXFrameFind(m_pMonster->GetFrame(),
		"Bip01-L-Hand");

	////�δ�� ���� ��ü
	m_pSphereR = new cSpere;
	m_pSphereR->Setup(D3DXVECTOR3(0, 0, 0), 20);

	m_pSphereL = new cSpere;
	m_pSphereL->Setup(D3DXVECTOR3(0, 0, 0), 20);



	//ó�� ���Ǵ� ��ġ ����

	m_vPosition = m_vBehaviorSpot;

	// �ٿ�� �ڽ� ����
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-30, -55, -30), D3DXVECTOR3(30, 55, 30));

	// �� �浹 ���� ����(�ο��� �Ÿ�)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);
}

void cMonster01::Update()
{

	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	//���� �״°�
	if (m_fHpCur <= 0)
	{
		//������� ���
		m_fTimeofDeath = (float)GetTickCount();
		m_bIsGen = false;
	}

	//�� �Ǿ�����
	if (m_bIsGen)
	{
		temp = *g_vPlayerPos - m_vPosition;

		MonoBehavior();


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



		// �̵�ó��!!
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


		
		//����

		Move();

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

	//�׾�����
	else
	{
		//�ٽ� ó������ ����

		m_vPosition = m_vBehaviorSpot;
		m_state = MON_STATE_unarmedwait;
		m_currState = MON_STATE_unarmedwait;
		m_fRotY = 0.0f;
		m_vDirection = D3DXVECTOR3(1, 0, 0);
		m_vPosition = m_vBehaviorSpot;
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);

		//5�ʵڿ� ��Ȱ.
		if (GetTickCount() - m_fTimeofDeath >= 5000.0f)
		{
			m_bIsGen = true;
		}
	}


	// ����
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

	//�̰� ��¥ �߿�!!!
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
	// �̵����� �ִ� �ִϸ��̼��� ��ŸƮ ���� ��Ʈ������ ����
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;
}

//���Ͱ� �������� �Ծ����� �����ִ� �ൿ����
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
	//ĳ���� �νĻ����϶�
	if (m_bAwake)
	{
		//���� ĳ���͸� �ν��̵Ǹ� �⺻���´� ����.
		m_bIdle = false;

		//���ݸ��
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
				//������ �����ִϸ��̼� ������ �̷���������Ƿ� �̷��� ������.
				m_bAnimation = true;
				//�����߿��� ������ �ٲ��� �����Ƿ� �ޱ۶��� �½����ݴϴ�.
				m_bAngleLock = true;
				//��������� atk01Ÿ���̴�.
				m_state = MON_STATE_atk02;
				//���� �ִϸ��̼� �������̸� �Է����ݴϴ�.
				m_fCurAnimTime = m_fAnimTime[MON_STATE_atk02];
			}
			else if(m_bAtkTerm && !m_bAnimation)
			{
				//������ �����ִϸ��̼� ������ �̷���������Ƿ� �̷��� ������.
				m_bAnimation = true;
				m_state = MON_STATE_Wait;
				m_fCurAnimTime = m_fAnimTime[MON_STATE_Wait];
			}


		}
		//�ִϸ��̼��� �Ϸ�� ���¿��� �߰��� ĵ������ ������ �� if���� �߰��ߴ�.
		else
		{
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

			//�ֱ׷��� �𸣰ڴµ� �� ���� �۾������� Idle�� �ٲ�� �ð��� �������.
			if (D3DXVec2Length(&tt) < 50.0f)
				m_bIdle = true;
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

				m_vPosition += (3.0f * m_fRunSpeed * v);
			}
		}
	}

	//�����ִϸ��̼� ó���κ�.
	if (m_bAnimation)
	{
		//�ִϸ��̼��� ó���ؾ� �ϹǷ� �ð��� �� ������ �ʿ��ϴ�.
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

//�� ������ ���̴� �ܼ��ൿ����
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
				m_bAtkTerm = true;			//���������ʱ�ȭ.
			}
		}
	}
	
	//�� Ż��������
	else if(D3DXVec3Length(&temp) > m_fAreaRadius && !m_bEscapeToggle)
	{
		m_bEscapeToggle = true;
		m_fEscapeTime = GetTickCount();
	}

	if (m_bEscapeToggle && m_bAwake)
	{
		//Ż��������κ��� 5�ʰ� ������ �ٽ� �������� ���ư���.
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