#pragma once
#include "../cGameObject.h"

class iMap;
class cProgressBar;
class vItem;

class cCharacter : public cGameObject
{
public:
	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXMATRIX			m_matWorld;

	float				m_fSpeed;

	SYNTHESIZE(iMap*, m_pMap, Map);

	float				m_fCosVal; // ī�޶� ���� ����


	D3DXMATRIX			m_matAnimWorld;
	D3DXVECTOR3			m_vCurAnimPos;
	D3DXVECTOR3			m_vBeforeAnimPos;

	float				m_fHpMax;
	float				m_fHpCur;
	float				m_fHpUI;

	float				m_fMpMax;
	float				m_fMpCur;
	float				m_fMpUI;

	float				m_fAttack;
	float				m_fDefense;

	// ���α׷��� ��
	cProgressBar*		m_pHpBar;
	cProgressBar*		m_pMpBar;
	cSprite*			m_BackBar;


	cSprite*			m_pBleeding;
	int					m_pBleedingAlpha;

	// ��� ���� ����...

	cItemInfo*			m_pEquitWeapon;
	cItemInfo*			m_pEquitBody;
	cItemInfo*			m_pEquitHand;
	cItemInfo*			m_pEquitLeg;

public:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	cCharacter();
	~cCharacter();

	void Setup();
	void Update();
	void Render();

	void PlusMapHeight();

	void SetUpStateBar();
	void UpdateUpStateBar();
	void RenderUpStateBar();

	virtual void Damaged();

	// ĳ���� ����
	virtual bool Attack(float damage);

	// ��� �ٲٱ�
	virtual int ChangeEquit();
};

