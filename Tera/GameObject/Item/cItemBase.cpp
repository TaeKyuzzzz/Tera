#include "stdafx.h"
#include "cItemBase.h"

#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"

#include "BoundingBox\cBoundingBox.h"


cItemBase::cItemBase()
	: m_sName(NULL)
	, m_pBody(NULL)
	, m_nIndex(0)
	, m_fTime(0.0f)
	, m_pSlashEffectTexture(NULL)
	, m_vOnPos(0, 0, 0)
	, m_vDownPos(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);

	ST_PC_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	D3DCOLOR color(0x880000ff);
	v.c = color;

	for (int i = 0; i < 10; i++)
		m_arrPos[i] = v;

}


cItemBase::~cItemBase()
{
	SAFE_DELETE(m_sName);
	SAFE_DELETE(m_pBody);
}

void cItemBase::Setup()
{
}

void cItemBase::Update()
{
	m_pBoundingBox->SetWorld(m_matWorld);

	m_fTime += TIMEMANAGER->GetEllapsedTime();
	if (m_fTime > 0.0005)
	{
		m_fTime = 0.0f;

		D3DXVec3TransformCoord(&m_arrPos[m_nIndex].p, &m_vOnPos, &m_matWorld);
		m_nIndex = (m_nIndex+1) % 50;		
		D3DXVec3TransformCoord(&m_arrPos[m_nIndex].p, &m_vDownPos, &m_matWorld);
		m_nIndex = (m_nIndex + 1) % 50;

	}

	m_vecVertex.clear();

	for (int i = 0; i < 48; i += 2)
	{
		m_vecVertex.push_back(m_arrPos[i + 0]);
		m_vecVertex.push_back(m_arrPos[i + 2]);
		m_vecVertex.push_back(m_arrPos[i + 1]);

		m_vecVertex.push_back(m_arrPos[i + 2]);
		m_vecVertex.push_back(m_arrPos[i + 3]);
		m_vecVertex.push_back(m_arrPos[i + 1]);
	}

	cGameObject::Update();
}

void cItemBase::Render()
{

	if (m_vecVertex.size() != 0)
	{
		//g_pD3DDevice->SetTexture(0, m_pSlashEffectTexture);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PC_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		//g_pD3DDevice->SetTexture(0, NULL);
	}

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pBody->Render();


	cGameObject::Render();
}
