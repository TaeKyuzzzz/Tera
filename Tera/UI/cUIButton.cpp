#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_buttonState(BT_UP)
	, m_pDelegate(NULL)
{
}


cUIButton::~cUIButton()
{
}

void cUIButton::SetTexture(const char * szUp, const char * szOver, const char * szDown)
{
	D3DXIMAGE_INFO stImageInfo;
	
	m_arrTexture[BT_UP] = TEXTUREMANAGER->GetTexture(szUp,&stImageInfo);
	m_stSize.nHeight = stImageInfo.Height;
	m_stSize.nWidth = stImageInfo.Width;

	m_arrTexture[BT_OVER] = TEXTUREMANAGER->GetTexture(szOver, &stImageInfo);
	m_arrTexture[BT_DOWN] = TEXTUREMANAGER->GetTexture(szDown, &stImageInfo);

}

void cUIButton::Update()
{
	//POINT pt;
	//GetCursorPos(&pt);
	//ScreenToClient(g_hWnd, &pt);
	
	RECT rc;
	SetRect(&rc,
		(int)m_matWorld._41,
		(int)m_matWorld._42,
		(int)m_matWorld._41 + m_stSize.nWidth,
		(int)m_matWorld._42 + m_stSize.nHeight);

	if (PtInRect(&rc, ptMouse))
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
			//	if (m_pDelegate)
			//		m_pDelegate->OnClick(this);
			}
			m_buttonState = BT_OVER;
		}
	}
	else
	{
		m_buttonState = BT_UP;
	}

	cUIObject::Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	// ��������Ʈ �׸���
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	// ���� ��Ʈ������ ����� ��ġ�� ����
	pSprite->SetTransform(&m_matWorld);
	// ����� ��Ʈ ����
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight); // �������� �ʺ�
														   // ��ο�
	pSprite->Draw
	(
		m_arrTexture[m_buttonState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	pSprite->End();

	cUIObject::Render(pSprite);
}
