#pragma once

class cSpere;
class cBoundingBox;

class cBoundingObject
{
private:
	//bool SightBox;
	//bool SightSpere;

protected:
	SYNTHESIZE_REF(cSpere*, m_pSpere, Spere);
	SYNTHESIZE_REF(cBoundingBox*, m_pBoundingBox, BoundingBox);
	SYNTHESIZE_REF(vector<cBoundingBox*>, m_vecBBoxGroup, vecBBoxGroup); // �ϳ��� Object�� �������� �浹box

	SYNTHESIZE(bool, m_bSightBox, SightBox);
	SYNTHESIZE(bool, m_bSightSpere, SightSpere);


public:
	cBoundingObject();
	virtual~cBoundingObject();

	void Setup();
	void Update();
	void Render();

	void Destroy_g();
};

