#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_buttonState(BT_UP)
	, m_pDelegate(NULL)
	, m_isButton(true)

{
}


cUIButton::~cUIButton()
{
}

void cUIButton::SetTexture(const char * szUp, const char * szOver, const char * szDown)
{
	D3DXIMAGE_INFO stImageInfo;
	
	m_arrTexture[BT_UP] = TEXTUREMANAGER->GetTexture(szUp,&stImageInfo);
	m_stSize.fHeight = stImageInfo.Height;
	m_stSize.fWidth  = stImageInfo.Width;

	m_arrTexture[BT_OVER] = TEXTUREMANAGER->GetTexture(szOver, &stImageInfo);
	m_arrTexture[BT_DOWN] = TEXTUREMANAGER->GetTexture(szDown, &stImageInfo);

	

}

void cUIButton::Update(ST_UI_SIZE dragSize)
{
	cUIObject::Update();

	SetRect(&m_CollisionRectBT,
		m_matWorld._41,
		m_matWorld._42,
		m_matWorld._41 + m_stSize.fWidth,
		m_matWorld._42 + m_stSize.fHeight);

	if (PtInRect(&m_CollisionRectBT, ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			if (m_buttonState == BT_OVER)
				m_buttonState = BT_DOWN;
		}
		else
		{
			if (BT_DOWN == m_buttonState)
			{
				//if(m_szCallPlace == "Inventory")
			}
			m_buttonState = BT_OVER;
		}
	}
	else
	{

		m_buttonState = BT_UP;
	}

	m_move.x = 0;
	m_move.y = 0;
	m_beforeMousePT = { 0, 0 };

}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	// ��������Ʈ �׸���
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	// ���� ��Ʈ������ ����� ��ġ�� ����
	pSprite->SetTransform(&m_matWorld);
	// ����� ��Ʈ ����
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight); // �������� �ʺ�
														   // ��ο�
	
	pSprite->Draw
	(		
		m_arrTexture[m_buttonState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(UIMANAGER->GetAlpha(), 255, 255, 255)
	);

	pSprite->End();

	cUIObject::Render(pSprite);

	
}






