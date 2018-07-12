#pragma once
class cUIObject
{
protected :
	D3DXMATRIX				m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);		// ��ġ
	SYNTHESIZE(cUIObject*, m_pParent, Parent);	// �θ� ����
	vector<cUIObject*>		m_vecChild;			// �ڽ� ����
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

