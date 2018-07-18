#pragma once

// �ؽ��� �Ŵ������� ������ �޾Ƽ� ����ؾ���

class cSprite
{
public:

	LPDIRECT3DTEXTURE9	texture;		// �ؽ���
	D3DXIMAGE_INFO		textureInfo;	// �ؽ��� ����
	//int					x;				// ���� x ��ǥ
	//int					y;				// ���� y ��ǥ

	LPD3DXSPRITE			m_pSprite;
public:
	cSprite();
	~cSprite();

	void Setup();
	void Render();

	void Render(D3DXVECTOR3 location);
	void Render(D3DXVECTOR3 center,D3DXVECTOR3 location);
	void Render(RECT rc,D3DXVECTOR3 center, D3DXVECTOR3 location);
	void Render(int x, int y);
	void AlphaRender(D3DXVECTOR3 center, D3DXVECTOR3 location, int alpha);
	void AlphaRender(RECT rc,D3DXVECTOR3 center, D3DXVECTOR3 location, int alpha);
	void AlphaRenderWinSize(D3DXVECTOR3 center, D3DXVECTOR3 location, int alpha);
};

