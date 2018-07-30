#include "stdafx.h"
#include "cMonster02.h"

#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "Particle\cParticleSet.h"
#include "Shader/cShader.h"


cMonster02::cMonster02()
	: m_pMonster(NULL)
	, m_currState(MON_STATE_unarmedwait)
{
	m_state = MON_STATE_unarmedwait;



	//�����ִϸ��̼��� �ƴҶ�, ������ ������ �˷��ִ� ����.
	m_bIsDone = true;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;
	m_nTime = 0;
	float animTime[MON_STATE_COUNT] =
	{
		40,		60,		50,		23,		41,
		31,		71,		31,		141,	30,
		31,		22,		1,		131,	101,
		106,	51,		56
	};

	memcpy(m_fAnimTime, animTime, sizeof(animTime));

	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] -= 1.0f;
	for (int i = 0; i < MON_STATE_COUNT; i++)
		m_fAnimTime[i] /= 30.0f;

	// ���� ó�� �ҰŴ�
	//���� ó���ϴϱ� �����ع�������. �׷��� �������״�.
	m_bIsBlend = false;

	//Monster02�� �̷� Ư���� ������ �ִ�.
	m_fAreaRadius = 100.0f;
	m_fTracableArea = 1000.0f;
	m_fRunSpeed = 1.2f;
	m_fFightZone = 50.0f;
	m_fHpCur = 200.0f;

	MODE = IDLE;

	// ������ ���� ��
	m_nNumofPattern = 2;

	m_pParticleBleeding = PARTICLEMANAGER->GetParticle("Bleeding");
	PARTICLEMANAGER->AddChild(m_pParticleBleeding);

}


cMonster02::~cMonster02()
{
	SAFE_DELETE(m_pMonster);
	SAFE_DELETE(m_pSphereR);
	SAFE_DELETE(m_pSphereL);

	//���̴� ����
	SAFE_RELEASE(DeathShader);
	SAFE_RELEASE(SKIN);
}

void cMonster02::Setup(D3DXVECTOR3 v)
{
	cMonster::Setup();

	m_sName = "�߻���";

	//ó���� ��� �����س��´�.
	//ó�� ���Ǵ� ��ġ ����
	m_vBehaviorSpot = v;//D3DXVECTOR3(1247, 0, 3578);
	m_vPosition = v;
	
	m_fHpMax = 200.0f;
	m_fHpCur = 200.0f;
	m_fAttack = 10.0f;
	m_fDefense = 5.0f;

	m_pMonster = new cSkinnedMesh;
	m_pMonster->Setup("XFile/Monster", "Bear.X");
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
	m_pSphereR->Setup(D3DXVECTOR3(0, 0, 0), 5);

	m_pSphereL = new cSpere;
	m_pSphereL->Setup(D3DXVECTOR3(0, 0, 0), 5);




	// �ٿ�� �ڽ� ����
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-15, 0, -15), D3DXVECTOR3(15, 20, 15));

	// �� �浹 ���� ����(�ο��� �Ÿ�)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vPosition, m_fFightZone);


	//���̴�����
	DeathShader = cShader::LoadShader("XFile/Monster", "DeathShader.fx");
	SKIN = TEXTUREMANAGER->GetTexture("XFile/Monster/EnragedBear_diff.tga");

	m_pRimLight = cShader::LoadShader("Shader/Effect/", "RimFlash.fx");
	m_pRimLight->SetFloat("Offset", 0.2f);
	
	MODE = IDLE;
}

void cMonster02::Update()
{
	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;

	switch (MODE)
	{
	case IDLE:
		Idle();
		break;
	case AWAKE:
		Awake();
		break;
	case CHASE:
		Chase();
		break;
	case BATTLE:
		Battle();
		break;
	case RETURN:
		Return();
		break;
	case DEATH:
		Death();
		break;
	case DISAPPEAR:
		Disappear();
		break;
	case REBIRTH:
		Rebirth();
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
	}

	// �̵����� �ִ� �ִϸ��̼��� ������Ʈ��
	// �ִϸ��̼� ��ŸƮ ������ ���忡�� ���� ������Ʈ
	// �ƴϸ� ���ó�� ����� ���忡�� ������Ʈ
	if (isUseLocalAnim())
	{
		m_matAnimWorld._42 = m_matWorld._42;

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

	//�̰� �����ָ� ���� �̻��ѵ� ���鼭 ����~
	m_fRotY = m_fCosVal;

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
}


//�ƹ��͵� ���� ����. ���������� ����Ÿ���.
void cMonster02::Idle()
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
		if (m_fCosVal < -1.0f)
			m_fCosVal = -0.99f;
		else if (m_fCosVal > 1.0f)
			m_fCosVal = 0.99;
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < NextSpot.z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		m_vPosition += (0.3f*m_fRunSpeed * v);

		//�̰� �������� �˳��ϰ� ��� �Ѵ�. �ȱ׷��� ��Ȯ�ϰ� ���߷��� �θ������� ����. 
		if (DistanceXZ(NextSpot, m_vPosition) < 1.0f)
		{
			m_bWalkOnOff = false;
			m_bStart = false;
		}
	}

	float Distance_Player_Monster = DistanceXZ(*g_vPlayerPos, m_vPosition);
	if (Distance_Player_Monster < m_fAreaRadius)
	{
		MODE = AWAKE;
		m_bWalkOnOff = false;
		m_bStart = false;
		return;
	}
}

//�ٽ� �������� ���ƿ��� �Լ�.
void cMonster02::Return()
{
	if (DistanceXZ(m_vPosition, m_vBehaviorSpot) < 1.0f)
		MODE = IDLE;
	else
	{
		m_state = MON_STATE_run;
		// u���� -> ���غ���
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v;
		D3DXVECTOR3 t;
		t = m_vBehaviorSpot - m_vPosition;
		t.y = 0;
		D3DXVec3Normalize(&v, &t);

		m_fCosVal = D3DXVec3Dot(&v, &u);
		if (m_fCosVal < -1.0f)
			m_fCosVal = -0.99f;
		else if (m_fCosVal > 1.0f)
			m_fCosVal = 0.99;
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < m_vBehaviorSpot.z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;

		m_vPosition += (1.5f * m_fRunSpeed * v);
	}
}

//Awake���´� �غ��¼��̴�. �÷��̾ �ٶ󺸸鼭 ȸ���Ѵ�.
//FightZone ���η� ������ ��Ʋ����, ����� �ٽ� Idle���·� ���ư���.
void cMonster02::Awake()
{
	m_state = MON_STATE_Wait;
	// u���� -> ���غ���
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 v;
	D3DXVec3Normalize(&v, &(*g_vPlayerPos - m_vPosition));

	m_fCosVal = D3DXVec3Dot(&v, &u);
	if (m_fCosVal < -1.0f)
		m_fCosVal = -0.99f;
	else if (m_fCosVal > 1.0f)
		m_fCosVal = 0.99;
	m_fCosVal = acosf(m_fCosVal);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	//����忡�� ���Ÿ����� ����� �ٽ� Idle�� ����
	if (DistanceXZ(*g_vPlayerPos, m_vPosition) > m_fAreaRadius)
	{
		MODE = IDLE;
		m_fTime = 0.0f;
		return;
	}

	//����忡�� �ο������� �Ÿ��� �������� ��������.
	if (DistanceXZ(*g_vPlayerPos, m_vPosition) < m_fFightZone)
	{
		MODE = BATTLE;
		m_fTime = 0.0f;
		return;
	}

	//SOUNDMANAGER->Play("M2_MON_STATE_Idle");
}

void cMonster02::Chase()
{
	//��Ʋ���->�߰ݸ���� ��� �ǰݸ�忡�� ������ bool������ float������ �ʱ�ȭ���ش�.(�ߺ�����)
	if (GetDamaged)
	{
		GetDamaged = false;
		DamageTerm = 0.0f;
	}


	//�� �Լ������� �׻� ���Ϳ� �÷��̾ �Ÿ��� �߿��ϹǷ� �׻� ���� ���� �������ش�.
	float Distance_Player_Monster = DistanceXZ(*g_vPlayerPos, m_vPosition);

	//�ο��� ���η� �Ÿ��� �������� �ٽ� ��Ʋ���. �׸���
	//���� ��輱��ó���� �ο�� �Ǹ� ��Ʋ�� ���ο��� �ְԵǾ� �ο�°� �켱�̴�.
	if (Distance_Player_Monster < m_fFightZone)
	{
		MODE = BATTLE;
		return;
	}
	else if (DistanceXZ(m_vPosition, m_vBehaviorSpot) > m_fTracableArea)
	{
		MODE = RETURN;
		return;
	}

	m_state = MON_STATE_run;
	// u���� -> ���غ���
	D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 v, v2;
	v2 = *g_vPlayerPos - m_vPosition;
	v2.y = 0;
	D3DXVec3Normalize(&v, &v2);

	m_fCosVal = D3DXVec3Dot(&v, &u);
	if (m_fCosVal < -1.0f)
		m_fCosVal = -0.99f;
	else if (m_fCosVal > 1.0f)
		m_fCosVal = 0.99;
	m_fCosVal = acosf(m_fCosVal);

	if (m_vPosition.z < g_vPlayerPos->z)
		m_fCosVal = D3DX_PI * 2 - m_fCosVal;

	m_vPosition += (m_fRunSpeed * v);
}

void cMonster02::Battle()
{
	//�ֻ�������. ���Ͱ� ������ ������ �� ���̾�.
	if (m_fHpCur <= 0)
	{
		MODE = DEATH;
		m_bAtkTerm = true;
		m_bAnimation = false;
		m_bAngleLock = false;
		return;
	}

	//�ο��� �����ϱ����� �׻� ������ ���� Ȯ���Ѵ�. �ο������� ����� �߰��� ����.
	if (!m_bAnimation && DistanceXZ(*g_vPlayerPos, m_vPosition) > m_fFightZone)
	{
		MODE = CHASE;
		m_bAtkTerm = true;
		m_bAnimation = false;
		m_bAngleLock = false;
		return;
	}

	//���� �ǰݴ��ߴٸ� �����ð����� �����̾�� �Ѵ�. GetDamaged�� On���Ѽ� �ð��� ���Ŀ� �����ð��� �Ǹ� �ٽ� OFF��Ų��.
	if (GetDamaged)
	{
		DamageTerm += TIMEMANAGER->GetEllapsedTime();
		if (DamageTerm > 0.5f)
		{
			GetDamaged = false;
			DamageTerm = 0.0f;
		}
			
	}

	//�ޱ۶� ���¿����� �����ս����߿� ȸ������ �ʴ´�.(�����鼭 ���ư��°� ����)
	if (!m_bAngleLock)
	{
		
		D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
		D3DXVECTOR3 v;
		D3DXVec3Normalize(&v, &(*g_vPlayerPos - m_vPosition));

		m_fCosVal = D3DXVec3Dot(&v, &u);
		if (m_fCosVal < -1.0f)
			m_fCosVal = -0.99f;
		else if (m_fCosVal > 1.0f)
			m_fCosVal = 0.99;
		m_fCosVal = acosf(m_fCosVal);

		if (m_vPosition.z < g_vPlayerPos->z)
			m_fCosVal = D3DX_PI * 2 - m_fCosVal;
	}

	//������ �����Ҷ�(���� �ִϸ��̼��� �������� ���� ���¿��� �Ѵ�.)
	if (!m_bAtkTerm && !m_bAnimation && DistanceXZ(*g_vPlayerPos, m_vPosition) < m_fFightZone)
	{
		SetAnimWorld();
		//�����ִϸ��̼��̹Ƿ� �̸� �� �����ش�.
		m_bAnimation = true;
		//�����߿��� ������ �ٲ��� �����Ƿ� �ޱ۶��� �½����ݴϴ�.
		m_bAngleLock = true;


		int patternNum = rand() % m_nNumofPattern;

		switch (patternNum)
		{
		case 0:
		{
			//��������� atk01Ÿ���̴�.
			m_state = MON_STATE_atk01;
			//���� �ִϸ��̼� �������̸� �Է����ݴϴ�.
			m_fCurAnimTime = m_fAnimTime[MON_STATE_atk01];

			SOUNDMANAGER->Play("M2_MON_STATE_atk01");
		}
			break;
		case 1:
		{
			m_state = MON_STATE_atk02;
			m_fCurAnimTime = m_fAnimTime[MON_STATE_atk02];

			SOUNDMANAGER->Play("M2_MON_STATE_atk01");
		}
			break;
		}
	}
	else if (m_bAtkTerm && !m_bAnimation)
	{
		//������ �����ִϸ��̼� ������ �̷���������Ƿ� �̷��� ������.
		m_bAnimation = true;
		m_state = MON_STATE_Wait;
		m_fCurAnimTime = m_fAnimTime[MON_STATE_Wait];
	}

	//�����ִϸ��̼� ó���κ�.
	if (m_bAnimation)
	{
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
		}
	}

	// ����
	if (m_state == MON_STATE_atk01)
		Attack(m_fAttack);
	if (m_state == MON_STATE_atk02)
		Attack(m_fAttack * 3);
}

void cMonster02::Death()
{
	m_fHpCur = 0.0f;

	m_state = MON_STATE_Death;
	m_fCurAnimTime = m_fAnimTime[MON_STATE_Death];
	m_bIsBlend = false;
	//�ִϸ��̼��� ó���ؾ� �ϹǷ� �ð��� �� ������ �ʿ��ϴ�.
	m_fTime += TIMEMANAGER->GetEllapsedTime();

	if (m_fCurAnimTime <= m_fTime)
	{
		m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
		m_vBeforeAnimPos = D3DXVECTOR3(0, 0, 0);
		m_fTime = 0.0f;
		MODE = DISAPPEAR;
	}

	SOUNDMANAGER->Play("M2_MON_STATE_Death");
}

void cMonster02::Disappear()
{
	//���� ������ ���ļ� ������ ������� �ٽ� �¾�� ����.
	if (!m_bIsGen)
	{
		MODE = REBIRTH;
		m_nTime = 0;
		return;
	}
	m_state = MON_STATE_deathwait;
	DissapearingMode = true;
	m_nTime += 1;
}

void cMonster02::Rebirth()
{
	m_vPosition = m_vBehaviorSpot;
	m_state = MON_STATE_unarmedwait;
	m_fRotY = 0.0f;
	m_vDirection = D3DXVECTOR3(1, 0, 0);
	m_vCurAnimPos = D3DXVECTOR3(0, 0, 0);
	m_fHpCur = 200.0f;

	//5�ʵڿ� ��Ȱ.
	if (GetTickCount() - m_fTimeofDeath >= 5000.0f)
	{
		MODE = IDLE;
		m_pMonster->AnimAdvanceTime();
		m_bIsGen = true;
	}
}

void cMonster02::Render()
{
	RimLightSetup(0, 0, 0, 0, 0, 0, 0);

	if (m_bIsGen)
	{
		if (DissapearingMode)
			m_pMonster->Render(NULL, DeathShader, m_nTime, SKIN, DissapearingMode, m_bIsGen, m_fTimeofDeath);
		else
		{
			if (m_isPicked)
				m_pMonster->Render(NULL, m_pRimLight);
			else
				m_pMonster->Render(NULL);
		}
	}

	cMonster::Render();

	if (SightSpere && m_pSphereR)
		m_pSphereR->Render();
	if (SightSpere && m_pSphereL)
		m_pSphereL->Render();

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "MODE : %d", MODE);
	RECT rc;
	SetRect(&rc, WINSIZEX - 200, 200, WINSIZEX, 300);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 0, 0));
}


// �̵����� �ִ� �ִϸ��̼��� ��ŸƮ ���� ��Ʈ������ ����
void cMonster02::SetAnimWorld()
{
	D3DXMATRIX matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matAnimWorld = matR * matT;
	m_matWorld = matR * matT;
}

bool cMonster02::isUseLocalAnim()
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

bool cMonster02::Attack(float damage)
{
	if (!OBJECTMANAGER->GiveDamagedChara(m_pSphereR, damage, m_vPosition))
	{
		if (OBJECTMANAGER->GiveDamagedChara(m_pSphereL, damage, m_vPosition))
			return true;
	}
	else
		return true;

	return false;
}

void cMonster02::Damaged(float damage, D3DXVECTOR3 pos)
{
	if (m_state == MON_STATE_deathwait ||
		m_state == MON_STATE_Death || GetDamaged)	 return;

	m_fHpCur -= damage;

	if (damage)
	{
		//�ǰ���ߴٸ� �ǰݴ��ߴٰ� ON�����ش�.
		GetDamaged = true;
		// ���� ��Ʈ�� ��ǥ�� ���� �����ϰ� ����
		D3DXMATRIX matTS, matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		float x = 30 + m_vPosition.x;
		float y = rand() % 10 + 10 + m_vPosition.y;
		float z = rand() % 60 - 30 + m_vPosition.z;
		D3DXMatrixTranslation(&matT, x, y, z);
		m_pParticleBleeding->SetWorld(matR * matT);
		m_pParticleBleeding->Start();

		//SOUNDMANAGER->Play("M2_MON_STATE_Damage");

	}
}