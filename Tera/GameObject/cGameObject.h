#pragma once

class cSpere;
class cBoundingBox;

enum OBJ_TYPE
{
	OBJ_CHARACTER,

};
class cGameObject
{
protected :

	bool SightBox;
	bool SightSpere;

protected :

	SYNTHESIZE_REF(cSpere*, m_pSpere, Spere);
	SYNTHESIZE_REF(cBoundingBox*, m_pBoundingBox, BoundingBox);

public:
	cGameObject();
	virtual~cGameObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void Damaged(float damage, D3DXVECTOR3 pos);

};

