#pragma once

class cSpere;
class cBoundingBox;


class cGameObject
{
private :

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

};

