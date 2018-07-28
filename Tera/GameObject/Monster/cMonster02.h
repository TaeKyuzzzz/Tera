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
		CHASE,
		BATTLE,
		RETURN,
		DEATH,
		DISAPPEAR,
		REBIRTH
	};

	enum MON_STATE
	{
		MON_STATE_Walk,
		MON_STATE_Wait,
		MON_STATE_unarmedwait,
		MON_STATE_run,
		MON_STATE_KnockBackStart,
		MON_STATE_KnockBackLoop,
		MON_STATE_KnockBackEnd,
		MON_STATE_jumpevasion,
		MON_STATE_Idle,
		MON_STATE_DownStart,
		MON_STATE_DownLoop,
		MON_STATE_DownEnd,
		MON_STATE_deathwait,
		MON_STATE_Death,
		MON_STATE_commandreceive,
		MON_STATE_atk03,
		MON_STATE_atk02,
		MON_STATE_atk01,
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
	int					m_nTime;						// �������̵��� �� �ð�����.
	bool				m_bIsBlend;						// �ִ� ���� ó������
	float				m_fCosVal;						// ������ ����

	
														
	//�ൿ���� �����ο� ���� �ӽú���
	D3DXVECTOR3			temp;
	D3DXVECTOR2			tt;

	//���ݿ� ���̴� ��

	ST_BONE*			m_pHandR;						
	ST_BONE*			m_pHandL;						
	cSpere*				m_pSphereR;						
	cSpere*				m_pSphereL;						

	float				m_fFightZone;


public:
	cMonster02();
	~cMonster02();

	void Setup(D3DXVECTOR3 v);

	/////////Update Function//////////
	void Update();
	void Idle();
	void Awake();
	void Chase();
	void Battle();
	void Return();
	void Death();
	void Disappear();
	void Rebirth();
	

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