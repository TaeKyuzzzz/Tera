#pragma once
#include "../cGameObject.h"

class iMap;

class cMonster : public cGameObject
{
public:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXMATRIX		m_matWorld;

	float			m_fSpeed;

	//iMap*			m_pMap;
	SYNTHESIZE(iMap*, m_pMap, Map);

	float			m_fCosVal; // ī�޶� ���� ����

	D3DXMATRIX		m_matAnimWorld;
	D3DXVECTOR3		m_vCurAnimPos;
	D3DXVECTOR3		m_vBeforeAnimPos;

	float			m_fHpMax;
	float			m_fHpCur;
	float			m_fHpUI;

	float			m_fMpMax;
	float			m_fMpCur;
	float			m_fMpUI;

	//���� �ִϸ��̼��� �������̳�
	bool			m_bAnimation;

	//���� �׺���̼� ����

	bool			m_bIsGen;									//���� ������. �׾� ������� false.
	bool			m_bAwake;									//ĳ���͸� ����������� True, �ٽ� �־����� false
	bool			m_bFight;									//Ư���Ÿ��� �������� ��������.
	SYNTHESIZE_REF(D3DXVECTOR3, m_vBehaviorSpot, Spot);			//���� Ȱ�� ����
	float			m_fAreaRadius;								//������ �������� �� ���� Ȱ���ݰ�.
	float			m_fRunSpeed;								//���� �̵��ӵ�, Awake�� ��쿡�� ������ +ó��.
	float			m_fTimeofDeath;								//�������� ������ ���. ���Ͱ� ������ �����ð��ڿ� �ٽ� �ش���ġ�� ��Ȱ.
	float			m_fEscapeTime;
	bool			m_bEscapeToggle;




public:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	cMonster();
	~cMonster();

	void Setup();
	void Update();
	void Render();

	//���� ���̸� ����
	void PlusMapHeight();

	//���� ����Ÿ��°� ����
	virtual void MonoBehavior(void) = 0;
};

