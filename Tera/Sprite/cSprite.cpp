#include "stdafx.h"
#include "cSprite.h"


cSprite::cSprite()
	: texture(NULL)
	, m_pSprite(NULL)
{
	ZeroMemory(&textureInfo, sizeof(D3DXIMAGE_INFO));

	HRESULT hr;
	hr = D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	assert(SUCCEEDED(hr));
}


cSprite::~cSprite()
{
	SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(texture);
}

void cSprite::Setup()
{
}

void cSprite::Render()
{
}

void cSprite::Render(D3DXVECTOR3 location)
{
	RECT rc;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	{

		SetRect(&rc, 0, 0, 
			textureInfo.Width, textureInfo.Height); // 시작점과 너비
															   // 드로우
		m_pSprite->Draw
		(
			texture,
			&rc,
			&D3DXVECTOR3(textureInfo.Width /2, 0, 0),
			&D3DXVECTOR3(WINSIZEX / 2, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	m_pSprite->End();

}

void cSprite::Render(D3DXVECTOR3 center, D3DXVECTOR3 location)
{
	RECT rc;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	{

		SetRect(&rc, 0, 0,
			textureInfo.Width, textureInfo.Height); // 시작점과 너비
													// 드로우
		m_pSprite->Draw
		(
			texture,
			&rc,
			&center,
			&location,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	m_pSprite->End();
}

void cSprite::Render(RECT rc, D3DXVECTOR3 center, D3DXVECTOR3 location)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	{													
		m_pSprite->Draw
		(
			texture,
			&rc,
			&center,
			&location,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	m_pSprite->End();
}

void cSprite::AlphaRender(D3DXVECTOR3 center, D3DXVECTOR3 location, int alpha)
{
	RECT rc;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	{

		SetRect(&rc, 0, 0,
			textureInfo.Width, textureInfo.Height); // 시작점과 너비
													// 드로우
		m_pSprite->Draw
		(
			texture,
			&rc,
			&center,
			&location,
			D3DCOLOR_ARGB(alpha, 255, 255, 255)
		);
	}
	m_pSprite->End();
}
