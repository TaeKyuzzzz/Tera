#include "stdafx.h"
#include "cPoalong.h"

#include "iMap.h"
#include "SkinnedMesh\cSkinnedMesh.h"
#include "BoundingBox\cBoundingBox.h"
#include "Spere\cSpere.h"

#include "Particle\cParticleSet.h"

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

	//처음에 얘로 셋팅해놓는다.
	m_vWhere_To_Stay = D3DXVECTOR3(1247, 0, 1578);

	m_fAnimTime = 80.0f / 30.0f;
}


cPoalong::~cPoalong()
{
	SAFE_DELETE(m_pPoalong);
}

void cPoalong::Setup()
{
	m_pPoalong = new cSkinnedMesh;
	m_pPoalong->Setup("XFile", "Poalong.X");
	m_pPoalong->SetAnimationIndexBlend(m_currState);

	// 위치를 가진 루트 본
	m_pDummyRoot = (ST_BONE*)D3DXFrameFind(m_pPoalong->GetFrame(),
		"Dummy_root");

	// 구 생성(말걸수 있는 Zone 생성)
	m_pSpere = new cSpere;
	m_pSpere->Setup(m_vWhere_To_Stay, 40);
}

void cPoalong::Update()
{
	D3DXVECTOR2 temp1;
	temp1.x = m_vWhere_To_Stay.x - g_vPlayerPos->x;
	temp1.y = m_vWhere_To_Stay.z - g_vPlayerPos->z;
	float DialogZone = D3DXVec2Length(&temp1);

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

	///////////////////////////상점처리///////////////////////////////
	
	if (!UIMANAGER->GetIsCallConShop() && KEYMANAGER->IsOnceKeyDown('F') && DialogZone < 40)
	{
		UIMANAGER->SetIsCallConShop(true);
		isOptionMode = true;
		CAMERAMANAGER->SetType(CAMERA_FIX);
		SOUNDMANAGER->Play("OpenInterface");
	}
	else if (UIMANAGER->GetIsCallConShop() && KEYMANAGER->IsOnceKeyDown('F') && DialogZone < 40)
	{
		UIMANAGER->SetIsCallConShop(false);
		SOUNDMANAGER->Play("CloseInterface");
	}
	//////////////////////////////////////////////////////////////////
}

void cPoalong::Render()
{
	m_pPoalong->Render(NULL);

	cGameObject::Render();
}

void cPoalong::PlusMapHeight()
{
	if (m_pMap)
		m_pMap->GetHeight(m_vWhere_To_Stay.x, m_vWhere_To_Stay.y, m_vWhere_To_Stay.z);
}
