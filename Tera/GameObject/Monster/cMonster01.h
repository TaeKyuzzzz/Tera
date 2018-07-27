#pragma once
#include "cMonster.h"

class cSkinnedMesh;
class cParticleSet;

class cMonster01 : public cMonster
{
private:
	enum MON_STATE
	{
		MON_STATE_Walk,
		MON_STATE_Wait,
		MON_STATE_unarmedwait,
		MON_STATE_stun,
		MON_STATE_SideWalk02,
		MON_STATE_SideWalk01,
		MON_STATE_run,
		MON_STATE_ReadyAction,
		MON_STATE_KnockBackStart,
		MON_STATE_KnockBackLoop,
		MON_STATE_KnockBackEnd,
		MON_STATE_jumpevasion02,
		MON_STATE_jumpevasion01,
		MON_STATE_flinch,
		MON_STATE_DyingWait,
		MON_STATE_DownStart,
		MON_STATE_DownLoop,
		MON_STATE_DownEnd,
		MON_STATE_deathwait,
		MON_STATE_Death,
		MON_STATE_atk06,
		MON_STATE_atk05,
		MON_STATE_atk04,
		MON_STATE_atk03,
		MON_STATE_atk02,
		MON_STATE_atk01,
		MON_STATE_aggrochange,
		MON_STATE_COUNT
	};



	cSkinnedMesh*		m_pMonster;
	ST_BONE*			m_pDummyRoot;

	MON_STATE			m_state;
	MON_STATE			m_currState;

	bool				m_bIsDone;

	float				m_fCurAnimTime;
	float				m_fAnimTime[MON_STATE_COUNT];

	float				m_fTime;

	bool				m_bIsBlend;

	float				m_fCosVal;

	//�ൿ���� �����ο� ���� �ӽú���
	D3DXVECTOR3			temp;
	D3DXVECTOR2			tt;

	//���ݿ� ���̴� ��

	ST_BONE*			m_pHandR;
	ST_BONE*			m_pHandL;
	cSpere*				m_pSphereR;
	cSpere*				m_pSphereL;

	float				m_fFightZone;


	cParticleSet*		m_pParticleBleeding;


public:
	cMonster01();
	~cMonster01();


	//------------------------�⺻�Լ�


	void Setup(D3DXVECTOR3 v);
	void Update();
	void Render();


	//--------------------------�ɼǼ���



	bool isUseLocalAnim();

	// �ִϸ��̼� ���� ��ǥ�� ����
	void SetAnimWorld();







	//---------------------------����

	void ProcessCombo();
	void ProcessDamaged();

	void ProcessBigDamaged();
	void ProcessDie();

	void Move();

	void Damaged();
	void BigDamaged();
	void Die();

	void MonoBehavior(void);
	void Roaming(void);

	//���Ͱ� ĳ���͸� �����ϴ� �Լ�
	virtual bool Attack(float damage);

	//���Ͱ� ĳ���Ϳ��� ���ظ� �޴� �Լ�
	void Damaged(float damage, D3DXVECTOR3 pos);
};

