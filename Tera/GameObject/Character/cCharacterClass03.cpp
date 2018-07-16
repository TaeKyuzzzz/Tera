#include "stdafx.h"
#include "cCharacterClass03.h"

#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

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

	Damaged(5.0f);
	BigDamaged();
	Die();
	// ���⼭�� �ִϸ��̼��� �ɸ� �ð��� �Ȱ��� ����
	//if(g_pKeyManager->IsOnceKeyDown('2'))
	m_fTime += TIMEMANAGER->GetEllapsedTime();

	// �ִϸ��̼��� �������� �˾ƺ���
	// �� ��Ȳ���� ���� �ִϸ��̼� ó��
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
			// ���� ó�� �Լ�
			ProcessCombo();
			// ������, ��� ó��
			ProcessDamaged();

			//
			ProcessGaiaCrash();

			//������ ����� �Ǵµ�, �Ͼ�����ϱ� �ڿ� && �߰��Ѱž�.
			if (cs == m_state && cs != CH_STATE_Dearhwait)
			{
				m_state = CH_STATE_Wait;
				m_bIsBlend = false;
			}
		}
	}
	
	// ��ư ����
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		// �Ϲ� ���� ����
		if (m_state == CH_STATE_combo1 || 
			m_state == CH_STATE_combo2 || 
			m_state == CH_STATE_combo3 ||
			m_state == CH_STATE_combo4)
		{
			// ������ �ϱ� ���� �޿� ���� �� �� ���� 
			m_bDoCombo = true;
		}
		// ùŸ
		else if (m_state == CH_STATE_Wait || CH_STATE_run)
		{
			// ���� ī�޶� ���� ��ġ �̵� �ִϸ��̼� �� �ؾߵǴ� �۾�
			m_fRotY = m_fCosVal;
			// ��ġ �̵� �ִϸ��̼� �� �ؾߵǴ� �۾�
			SetAnimWorld();

			m_state = CH_STATE_combo1;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_combo1];
			m_fTime = 0.0f;
			m_bIsDone = false;
		}
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON) && m_state != CH_STATE_tumbling)
	{
		SetAnimWorld();

		// ������
		m_state = CH_STATE_tumbling;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_tumbling];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		SetAnimWorld();

		// ����� ������ ������ �մϴ�.
		m_state = CH_STATE_DwonBlow;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_DwonBlow];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		// ���̾� ũ����

		SetAnimWorld();

		// ����� ������ ������ �մϴ�.
		m_state = CH_STATE_gaiaCrush01;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_gaiaCrush01];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown('2'))
	{
		// Ŀ�ý�����

		SetAnimWorld();

		// ����� ������ ������ �մϴ�.
		m_state = CH_STATE_CuttingSlash;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_CuttingSlash];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		// �����

		SetAnimWorld();

		// ����� ������ ������ �մϴ�.
		m_state = CH_STATE_CutHead;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_CutHead];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		SetAnimWorld();

		// ����� ������ ������ �մϴ�.
		m_state = CH_STATE_StingerBlade;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_StingerBlade];
		m_fTime = 0.0f;
		m_bIsDone = false;
	}

	// ��ų �¿� ���� ��ų�� ������ �ؾ��� ( ���� ��뵵 )
	else if(m_bIsDone)
	{
		m_state = CH_STATE_Wait;
	}

	// �̵�
	if ((KEYMANAGER->IsStayKeyDown('W') ||
		KEYMANAGER->IsStayKeyDown('A') ||
		KEYMANAGER->IsStayKeyDown('D') ||
		KEYMANAGER->IsStayKeyDown('S')) &&
		(m_state == CH_STATE_Wait || m_state == CH_STATE_run))
		m_state = CH_STATE_run;

	// ������ ĳ���� Ŭ������ �̵��� �����ϰ� �Ϸ��� �ߴµ�
	// m_state ���� ���� �̵��� ������ ����ؼ� ����,
	// �׳� ���� Ŭ�������� �̵��� ó���ϱ�� ���� 
	//cCharacter::Update();
	Move();

	cCharacter::Update();
}

void cCharacterClass03::Render()
{
	cCharacter::Render();
}

void cCharacterClass03::SetAnimWorld()
{
	// �̵����� �ִ� �ִϸ��̼��� ��ŸƮ ���� ��Ʈ������ ����
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;;
}

void cCharacterClass03::ProcessCombo()
{
	// ���� ������ ���� �����ִ� �Լ�
	// �ִϸ��̼��� �������� ����Ǹ� , �޺����� �Ұ��� ���� ����
	// �ִϸ��̼��� ����
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
	// �̵��� ���õ� �Լ�
	D3DXVECTOR3 beforePos = m_vPosition;
	float		beforeRot = m_fRotY;

	if (KEYMANAGER->IsStayKeyDown('A') && m_state == CH_STATE_run)
	{
		m_fRotY = m_fCosVal + D3DX_PI * 1.5f;
		
		if(!OBJECTMANAGER->IsCollision(this))
			m_vPosition += (m_vDirection * m_fSpeed);
		//m_fRotY -= 0.1f;
	}
	else if (KEYMANAGER->IsStayKeyDown('D') && m_state == CH_STATE_run)
	{
		//m_fRotY += 0.1f;
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

	if (m_fRotY <= 0.0f)
		m_fRotY += D3DX_PI * 2;
	else if (m_fRotY >= D3DX_PI * 2)
		m_fRotY -= D3DX_PI * 2;

	D3DXMATRIX mat , matR, matT;
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

void cCharacterClass03::Damaged(float damage)
{

	if (KEYMANAGER->IsOnceKeyDown('Q'))
	{
		m_fHpCur -= damage;

		if (damage < m_fHpMax / 10.0f)
		{

		}
		else if (damage < m_fHpMax / 6.0f)
		{
			SetAnimWorld();
			m_state = CH_STATE_bReactionStart;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart];
			m_bIsDone = false;
			m_bIsBlend = false;
		}
		else
		{
			SetAnimWorld();
			m_state = CH_STATE_bReactionStart3;
			m_fCurAnimTime = m_fAnimTime[CH_STATE_bReactionStart3];
			m_bIsDone = false;
			m_bIsBlend = false;
		}

		if (m_fHpCur < 0)
		{
			Die();
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
	if (KEYMANAGER->IsOnceKeyDown('R'))
	{
		m_fHpCur = 0.0f;

		SetAnimWorld();
		m_state = CH_STATE_Death;
		m_fCurAnimTime = m_fAnimTime[CH_STATE_Death];
		m_bIsDone = false;
		m_bIsBlend = false;
	}
}
