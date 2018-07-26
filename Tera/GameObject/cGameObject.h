#pragma once

class cSpere;
class cBoundingBox;

enum OBJ_TYPE
{
	OBJ_CHARACTER,

};

enum CONDITION
{
	CDT_NORMAL,
	CDT_BURN,
	CDT_ICE,
	CDT_STURN
};

class cGameObject
{
protected:

	bool			SightBox;
	bool			SightSpere;


protected:

	SYNTHESIZE_REF(cSpere*, m_pSpere, Spere);
	SYNTHESIZE_REF(cBoundingBox*, m_pBoundingBox, BoundingBox);

	// 상태이상 변수
	SYNTHESIZE(CONDITION, m_eCondition, Condition);

	bool				m_isPossibleDamaged;
	float				m_PossbleDamagedTime;

public:
	cGameObject();
	virtual~cGameObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void Damaged(float damage, D3DXVECTOR3 pos);
	virtual void Damaged(float damage, D3DXVECTOR3 pos, CONDITION con, float per);

	virtual void CountPossibleDamaged(float time);
};

