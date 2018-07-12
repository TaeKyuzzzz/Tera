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
	// 스프라이트 그리기
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
	// 월드 매트릭스로 출력할 위치를 지정
	pSprite->SetTransform(&m_matWorld);
	// 출력할 렉트 생성
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight); // 시작점과 너비
	// 드로우
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

// ui 오브젝트가 스프라이트를 한개씩 가질 필요는 없음