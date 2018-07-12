#pragma once

// 텍스쳐 매니져에서 정보를 받아서 사용해야함

class cSprite
{
public:

	LPDIRECT3DTEXTURE9	texture;		// 텍스쳐
	D3DXIMAGE_INFO		textureInfo;	// 텍스쳐 정보
	//int					x;				// 시작 x 좌표
	//int					y;				// 시작 y 좌표

	LPD3DXSPRITE			m_pSprite;
public:
	cSprite();
	~cSprite();

	void Setup();
	void Render();

	void Render(D3DXVECTOR3 location);
	void Render(D3DXVECTOR3 center,D3DXVECTOR3 location);
	void Render(RECT rc,D3DXVECTOR3 center, D3DXVECTOR3 location);
	void AlphaRender(D3DXVECTOR3 center, D3DXVECTOR3 location, int alpha);
};

