#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_vPosition(0,0,0)
	, m_pParent(NULL)
	, m_stSize(0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
}

void cUIObject::AddChild(cUIObject * pChild)
{
	m_vecChild.push_back(pChild);
	pChild->SetParent(this);
}
void cUIObject::Destroy()
{
	for (auto p : m_vecChild)
		p->Destroy();

	delete this;
}

void cUIObject::Update()
{
	// 자기 위치로 월드 행렬 변환 
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	// 부모가 있다면 부모의 월드를 더해서 부모와 상대적인 위치로
	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for (auto child : m_vecChild)
		child->Update();
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	for (auto child : m_vecChild)
		child->Render(pSprite);
}
