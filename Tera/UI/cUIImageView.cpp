#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)

{
}


cUIImageView::~cUIImageView()
{
	//SAFE_RELEASE(m_pTexture);
	//m_pTexture->Release();
	//TEXTUREMANAGER->Destroy();
}

void cUIImageView::SetTexture(const char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = TEXTUREMANAGER->GetTexture(szFullPath, &stImageInfo);

	m_stSize.fHeight = stImageInfo.Height;
	m_stSize.fWidth = stImageInfo.Width;

	m_enClickState = NON;

	m_nAlpha = UIMANAGER->GetAlpha();

}

void cUIImageView::Update()
{
	cUIObject::Update();



	SetRect(&m_CollisionRect
		,  m_matWorld._41
		, m_matWorld._42
		, m_matWorld._41 + m_stSize.fWidth
		, m_matWorld._42 + m_stSize.fHeight);


		
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
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
		m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255)
	);
	

		
	pSprite->End();
	
	cUIObject::Render(pSprite);	

	
}






// ui ������Ʈ�� ��������Ʈ�� �Ѱ��� ���� �ʿ�� ����