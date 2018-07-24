#pragma once
#include "cMonster.h"

class cSkinnedMesh;
class cParticleSet;

class cMonster02 : public cMonster
{
protected:

	enum MON_MODE
	{
		IDLE,
		AWAKE,
		DEATH
	};

	enum MON_STATE
	{
		MON_STATE_Walk,
		MON_STATE_Wait,
		MON_STATE_unarmedwait,
		MON_STATE_Spawn,
		MON_STATE_run,
		MON_STATE_roundmove02,
		MON_STATE_roundmove01,
		MON_STATE_roundAtk02,
		MON_STATE_roundAtk01,
		MON_STATE_ReactionStart,
		MON_STATE_ReactionLoop,
		MON_STATE_ReactionEnd,
		MON_STATE_ReactonAtk,
		MON_STATE_ReactionAdd,
		MON_STATE_moveAtk,
		MON_STATE_modeAlarm,
		MON_STATE_jumpevasion02,
		MON_STATE_jumpevasion01,
		MON_STATE_heavyatk02,
		MON_STATE_heavyatk01,
		MON_STATE_groggy,
		MON_STATE_flinch,
		MON_STATE_deathwait,
		MON_STATE_Death,
		MON_STATE_backAtk,
		MON_STATE_atk02,
		MON_STATE_atk01,
		MON_STATE_aggrochange,
		MON_STATE_COUNT
	};

	MON_MODE			MODE;	//�꿡 ���� ȣ���ϴ� ����������Ʈ�� �ٸ���.

	cSkinnedMesh*		m_pMonster;						// ���� ���̷��� �޽�
	ST_BONE*			m_pDummyRoot;					// ��Ʈ ��
	ST_BONE*			m_pBIP;							// ������ ��

	MON_STATE			m_state;							// ����� �ִϸ��̼�
	MON_STATE			m_currState;						// �ٲ� �ִϸ��̼�

	bool				m_bIsDone;						// �ִϸ��̼��� ������?

	float				m_fCurAnimTime;					// ����� �ð� �ִϸ��̼�
	float				m_fAnimTime[MON_STATE_COUNT];	// ����ž��� �� �ð�
	float				m_fTime;						// �ִ� �ɸ��ð�
	bool				m_bIsBlend;						// �ִ� ���� ó������
	float				m_fCosVal;						// ������ ����

	
														
	//�ൿ���� �����ο� ���� �ӽú���
	D3DXVECTOR3			temp;
	D3DXVECTOR2			tt;

	//���ݿ� ���̴� ��

	ST_BONE*			m_pHandR;						// ������ (���̾�
	ST_BONE*			m_pHandL;						// ����	 (���̽�
	cSpere*				m_pSphereR;						// ������ �� (�浹��
	cSpere*				m_pSphereL;						// ���� �� (�浹��

	float				m_fFightZone;

public:
	cMonster02();
	~cMonster02();

	void Setup();

	/////////Update Function//////////
	void Update();
	void Idle_Update();
	void Awake_Update();
	void Awake_Chase();
	void Awake_Battle();
	void Death_Update();
	void Death_Die();

	void AnimUpdate();
	void UpdateWorld();
	void ParticleUpdate();
	//////////////////////////////////

	void Render();

	////////Rendering Function///////

	void SetAnimWorld();
	bool isUseLocalAnim();


	////// etc ////////////////////////
	void ChangeState(MON_MODE STATE);
	void ChangeAnim(MON_STATE anim, bool isBlend);
	///////////////////////////////////
};