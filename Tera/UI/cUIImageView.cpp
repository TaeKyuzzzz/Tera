#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
{
}


cUIImageView::~cUIImageView()
{
	//SAFE_RELEASE(m_pTexture);
}

void cUIImageView::SetTexture(const char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = TEXTUREMANAGER->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nHeight = stImageInfo.Height;
	m_stSize.nWidth = stImageInfo.Width;
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
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
		m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	
	pSprite->End();

	cUIObject::Render(pSprite);
}

// ui ������Ʈ�� ��������Ʈ�� �Ѱ��� ���� �ʿ�� ����