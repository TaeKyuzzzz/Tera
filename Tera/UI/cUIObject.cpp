#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_vPosition(0,0,0)
	, m_pParent(NULL)
	, m_stSize(0,0)
	, m_isCollisionPT(false)
	, m_nReduceDragRange{ 1,1 }
	, m_isMove(true)
	, m_nAlpha(UIMANAGER->GetAlpha())
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

void cUIObject::DelChild(int index)
{
	m_vecChild.erase(m_vecChild.begin() + index);
}

void cUIObject::Destroy()
{
	for (auto p : m_vecChild)
		p->Destroy();

	delete this;

	
}

void cUIObject::Update(ST_UI_SIZE dragSize)
{
	// �ڱ� ��ġ�� ���� ��� ��ȯ 
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	// �θ� �ִٸ� �θ��� ���带 ���ؼ� �θ�� ������� ��ġ��
	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	
	ImageDrag(m_nReduceDragRange);

	for (auto child : m_vecChild)
	{
		child->Update(dragSize);
	}


	
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	for (auto child : m_vecChild)
		child->Render(pSprite);

	//for (int i = 0; i < m_vInvenSlot.size(); i++)
	//{
	//	Rectangle(hdc, m_vInvenSlot[i].rc.left, m_vInvenSlot[i].rc.top, m_vInvenSlot[i].rc.right, m_vInvenSlot[i].rc.bottom);
	//}

}

void cUIObject::ImageDrag(D3DXVECTOR2 vec2ReduceDragRange)
{
	if (m_enClickState != UNMOVABLE && m_isColDragRcAndPT && isOptionMode)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			m_beforeMousePT = ptMouse;
			m_enClickState = CLICK;
		}

		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
		{
			//�˿��尡 x,y�� �� ��ġ��
			m_matWorld._41 += (ptMouse.x - m_beforeMousePT.x);
			m_matWorld._42 += (ptMouse.y - m_beforeMousePT.y);
			m_enClickState = CLICKING;
		}
		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			m_move.x += (ptMouse.x - m_beforeMousePT.x);
			m_move.y += (ptMouse.y - m_beforeMousePT.y);
			m_enClickState = NON;
		}
	}

	if (m_isMove)
	{
		m_matWorld._41 += m_move.x;
		m_matWorld._42 += m_move.y;
	}

	SetRect(&m_CollisionRect
		, m_matWorld._41
		, m_matWorld._42
		, m_matWorld._41 + m_stSize.fWidth
		, m_matWorld._42 + m_stSize.fHeight);

	SetRect(&m_resizeRect,
		m_CollisionRect.left + 11,
		m_CollisionRect.top + 11,
		m_CollisionRect.right - 11,
		m_CollisionRect.bottom - 11);


	SetRect(&m_DragRect
		, m_matWorld._41
		, m_matWorld._42
		, m_matWorld._41 + (m_stSize.fWidth * vec2ReduceDragRange.x)
		, m_matWorld._42 + (m_stSize.fHeight * vec2ReduceDragRange.y)
	);

	if (PtInRect(&m_DragRect, ptMouse))
	{

		m_isColDragRcAndPT = true;

	}
	else m_isColDragRcAndPT = false;

	if (PtInRect(&m_DragRect, ptMouse))
	{

		m_isColDragRcAndPT = true;

	}
	else m_isColDragRcAndPT = false;
}


