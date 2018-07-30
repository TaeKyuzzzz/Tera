#include "stdafx.h"
#include "cPoalong.h"

#include "iMap.h"
#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "Particle\cParticleSet.h"
#include "Shader\cShader.h"

cPoalong::cPoalong()
	: m_pPoalong(NULL)
	, m_currState(IDLE)
	, m_pMap(NULL)
	, m_fRotY(0.0f)
	, m_vDirection(-1, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);

	m_state = IDLE;

	m_fCurAnimTime = 0.0f;
	m_fTime = 0.0f;

	//ó���� ��� �����س��´�.
	//m_vWhere_To_Stay = D3DXVECTOR3(1247, 0, 1578);

	m_fAnimTime = 80.0f / 30.0f;
}


cPoalong::~cPoalong()
{
	SAFE_DELETE(m_pPoalong);
}

void cPoalong::Setup(D3DXVECTOR3 v)
{
	m_vWhere_To_Stay = v;
	m_pPoalong = new cSkinnedMesh;
	m_pPoalong->Setup("XFile", "Poalong.X");
	m_pPoalong->SetAnimationIndexBlend(m_currState);

	// ��ġ�� ���� ��Ʈ ��
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pPoalong->GetFrame(),
		"Dummy_root");

	// �� ����(���ɼ� �ִ� Zone ����)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vWhere_To_Stay, 40);

	m_pRimLight = cShader::LoadShader("Shader/Effect/", "RimFlash.fx");
	m_pRimLight->SetFloat("Offset", 0.2);
}

void cPoalong::Update()
{
	/*D3DXVECTOR2 temp1;
	temp1.x = m_vWhere_To_Stay.x - g_vPlayerPos->x;
	temp1.y = m_vWhere_To_Stay.z - g_vPlayerPos->z;
	float DialogZone = D3DXVec2Length(&temp1);
	*/
	 DialogZone = DistanceXZ(m_vWhere_To_Stay, *g_vPlayerPos);

	m_pDummyRoot->TransformationMatrix._42 = m_matWorld._42;
	m_pPoalong->Update(m_matWorld);

	D3DXMATRIX mat, matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXMatrixTranslation(&matT, m_vWhere_To_Stay.x, m_vWhere_To_Stay.y, m_vWhere_To_Stay.z);


	m_matWorld = matR * matT;
	//m_pBoundingBox->SetWorld(m_matWorld);
	m_pSpere->SetWorld(m_matWorld);

	PlusMapHeight();

	cGameObject::Update();

	///////////////////////////����ó��///////////////////////////////
	
	if (!UIMANAGER->GetIsCallConShop() && KEYMANAGER->IsOnceKeyDown('F') && DialogZone < 40)
	{
		// â Ű�� �÷��̾ �Ĵٺ���.
		{
			D3DXVECTOR3 u = D3DXVECTOR3(1, 0, 0);
			D3DXVECTOR3 v;
			D3DXVec3Normalize(&v, &(*g_vPlayerPos - m_vWhere_To_Stay));

			m_fCosVal = D3DXVec3Dot(&v, &u);
			m_fCosVal = acosf(m_fCosVal);

			if (m_vWhere_To_Stay.z < g_vPlayerPos->z)
				m_fCosVal = D3DX_PI * 2 - m_fCosVal;
		}

		UIMANAGER->SetIsCallConShop(true);
		isOptionMode = true;
		CAMERAMANAGER->SetType(CAMERA_FIX);
		SOUNDMANAGER->Play("OpenInterface");
	}
	else if (UIMANAGER->GetIsCallConShop() && KEYMANAGER->IsOnceKeyDown('F') && DialogZone < 40)
	{
		//â�� ���� �ٽ� ���� �Ĵٺ��� ������.
		{
			m_fCosVal = 0.0f;
			m_vDirection = D3DXVECTOR3(-1, 0, 0);
		}
		UIMANAGER->SetIsCallConShop(false);
		SOUNDMANAGER->Play("CloseInterface");
	}
	//////////////////////////////////////////////////////////////////

	m_fRotY = m_fCosVal;
}

void cPoalong::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	RimLightSetup(0, 0, 0, 0, 0, 0, 0);

	if (DialogZone < 40)
	{
		m_pPoalong->Render(NULL);
		m_pPoalong->Render(NULL,m_pRimLight);
	}
	else
		m_pPoalong->Render(NULL);

	cGameObject::Render();
}

void cPoalong::PlusMapHeight()
{
	if (m_pMap)
		m_pMap->GetHeight(m_vWhere_To_Stay.x, m_vWhere_To_Stay.y, m_vWhere_To_Stay.z);
}
