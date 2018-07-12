#pragma once
class cUIObject
{
protected :
	D3DXMATRIX				m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);		// 위치
	SYNTHESIZE(cUIObject*, m_pParent, Parent);	// 부모 정보
	vector<cUIObject*>		m_vecChild;			// 자식 정보
	ST_UI_SIZE				m_stSize;

public:
	cUIObject();
	virtual~cUIObject();

	virtual void AddChild(cUIObject * pChild);
	virtual void Destroy();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	//virtual void Render(LPD3DXSPRITE pSprite);
};

