#pragma once
class cCube
{
protected	:

	vector<ST_PC_VERTEX>		m_vecVertex;

public:
	cCube();
	~cCube();

	virtual void Setup();
	virtual void Setup(D3DXVECTOR3 min, D3DXVECTOR3 max);
	virtual void Update();
	virtual void Render();
};

