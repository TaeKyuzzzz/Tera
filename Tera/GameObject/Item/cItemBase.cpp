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

	ST_PCT_VERTEX v;
	//v.p = D3DXVECTOR3(0, 0, 0);
	//D3DCOLOR color(0x880000ff);
	//v.c = color;
	//
	for (int i = 0; i < 10; i++)
		m_arrPos[i].c = D3DCOLOR_ARGB(125, 255, 255, 255);

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
		m_nIndex = (m_nIndex + 1) % 20;
		D3DXVec3TransformCoord(&m_arrPos[m_nIndex].p, &m_vDownPos, &m_matWorld);
		m_nIndex = (m_nIndex + 1) % 20;

		m_vecVertex.clear();

		for (int i = 0; i < 18; i += 2)
		{
			m_arrPos[i + 0].t = D3DXVECTOR2(0, 0);
			m_vecVertex.push_back(m_arrPos[i + 0]);
			m_arrPos[i + 0].t = D3DXVECTOR2(0, 1);
			m_vecVertex.push_back(m_arrPos[i + 2]);
			m_arrPos[i + 0].t = D3DXVECTOR2(1, 0);
			m_vecVertex.push_back(m_arrPos[i + 1]);

			m_arrPos[i + 0].t = D3DXVECTOR2(0, 1);
			m_vecVertex.push_back(m_arrPos[i + 2]);
			m_arrPos[i + 0].t = D3DXVECTOR2(1, 1);
			m_vecVertex.push_back(m_arrPos[i + 3]);
			m_arrPos[i + 0].t = D3DXVECTOR2(1, 0);
			m_vecVertex.push_back(m_arrPos[i + 1]);
		}
	}

	cGameObject::Update();
}

void cItemBase::Render()
{

	if (m_vecVertex.size() != 0)
	{
		// 알파
		// 텍스처 알파 옵션 셋팅
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);



		// 알파블랜딩 방식 결정
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

		g_pD3DDevice->SetTexture(0, m_pSlashEffectTexture);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PCT_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_pD3DDevice->SetTexture(0, NULL);

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pBody->Render();


	cGameObject::Render();
}
