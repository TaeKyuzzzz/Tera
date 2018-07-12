#include "stdafx.h"
#include "cDummyObj.h"
#include "Spere\cSpere.h"
#include "BoundingBox\cBoundingBox.h"

cDummyObj::cDummyObj()
{
}


cDummyObj::~cDummyObj()
{
	SAFE_DELETE(m_pSpere);
	SAFE_DELETE(m_pBoundingBox);
}


void cDummyObj::Setup(D3DXVECTOR3 pos)
{
	m_vPosition = pos;

	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(D3DXVECTOR3(-10, -10, -10), D3DXVECTOR3(10, 10, 10));

	//D3DXMatrixTranslation(&m_matWorld, )

	// 备 面倒 康开 积己
	m_pSpere = new cSpere;
	m_pSpere->Setup(D3DXVECTOR3(0, 0, 0), 20);
}

void cDummyObj::Update()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_pBoundingBox->SetWorld(mat);
	m_pSpere->SetWorld(mat);

	cGameObject::Update();
}

void cDummyObj::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	cGameObject::Render();
}
