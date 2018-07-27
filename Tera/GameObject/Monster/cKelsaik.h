#pragma once
#include "cMonster.h"

class cSkinnedMesh;
class cParticleSet;
class cProgressBar;
class cSprite;

// �������� �ߵ��ϴ� ���Ͽ��� ���ϵ�
#define NUMOFPATTERN	3
#define LEFTTURN		(NUMOFPATTERN)
#define RIGHTTURN		(NUMOFPATTERN+1)
#define BACKTURN		(NUMOFPATTERN+2)
#define REACTION		(NUMOFPATTERN+3)
#define REACTIONGRGY	(NUMOFPATTERN+4)
#define REACTIONDOWN	(NUMOFPATTERN+5)
#define BERSERK			(NUMOFPATTERN+6)

class cKelsaik : public cMonster
{
protected:

	enum MON_STATE
	{
		IDLE,
		AWAKE,
		WALK,
		BATTLE,
		TURN,
		DIE
	};
	// 
	enum MON_Anim
	{
		MON_Anim_aggrochange,
		MON_Anim_atk01,
		MON_Anim_atk02,
		MON_Anim_backAtk,
		MON_Anim_Death,
		MON_Anim_deathwait,
		MON_Anim_flinch,		// ����
		MON_Anim_groggy,
		MON_Anim_heavyatk01,
		MON_Anim_heavyatk02,
		MON_Anim_jumpevasion01,
		MON_Anim_jumpevasion02,
		MON_Anim_modeAlarm,
		MON_Anim_moveAtk,
		MON_Anim_ReactionAdd,	// ������ ���չ���
		MON_Anim_ReactonAtk,	// ������
		MON_Anim_ReactionEnd,	// �Ͼ��
		MON_Anim_ReactionLoop,	// ���չ���
		MON_Anim_ReactionStart,	// ����������
		MON_Anim_roundAtk01,	// �·��ֵθ���
		MON_Anim_roundAtk02,	// ����ֵθ���
		MON_Anim_roundmove01,	// ��ȸ��
		MON_Anim_roundmove02,	 // ��ȸ��
		MON_Anim_run,
		MON_Anim_Spawn,
		MON_Anim_unarmedwait,
		MON_Anim_Wait,
		MON_Anim_Walk,
		MON_Anim_COUNT
	};

	MON_STATE		STATE;	//�꿡 ���� ȣ���ϴ� ����������Ʈ�� �ٸ���.

	cSkinnedMesh*	m_pMonster;						// ���� ���̷��� �޽�
	ST_BONE*		m_pDummyRoot;					// ��Ʈ ��
	ST_BONE*		m_pBIP;							// ������ ��

	MON_Anim		m_Anim;							// ����� �ִϸ��̼�
	MON_Anim		m_currAnim;						// �ٲ� �ִϸ��̼�

	bool			m_bIsDone;						// �ִϸ��̼��� ������?

	float			m_fCurAnimTime;					// ����� �ð� �ִϸ��̼�
	float			m_fAnimTime[MON_Anim_COUNT];	// ����ž��� �� �ð�
	float			m_fTime;						// �ִ� �ɸ��ð�
	bool			m_bIsBlend;						// �ִ� ���� ó������
	float			m_fCosVal;						// ������ ����
	float			m_fTargetAngle;

	bool			m_isDoingPattern;
	bool			m_partternCost;

	int				m_nPatternNum;
	float			m_fPatternCostTime;

	float			m_fDamagedStack;	// ������ ���� ���� ������ ( 500�� ����)

	bool			m_isPossibleGroggy; // �׷α� 1ȸ
	bool			m_isPossibleDown;	// �ٿ� 1ȸ
	bool			m_isPossibleBerserk; // ����ȭ 1ȸ
	//���ݿ� ���̴� ��

	ST_BONE*		m_pHandR;			// ������ (���̾�
	ST_BONE*		m_pHandL;			// ����	 (���̽�
	cSpere*			m_pSphereR;			// ������ �� (�浹��
	cSpere*			m_pSphereL;			// ���� �� (�浹��

	float			m_fFightZone;		// ��Ʋ ����


	// ��ƼŬ ȿ�� 1�� ��¿� ���� �� ����
	bool			m_pEffectCost;		//
	cParticleSet*	m_pParticleBleeding;// ���� ��ƼŬ
	cParticleSet*	m_pIceHand;			//IceHand2			// �޼� ���̽� ��ƼŬ
	cParticleSet*	m_pFireHand;		// FireHand			// ������ ���̾� ��ƼŬ
	cParticleSet*	m_pIceEffect;		// ���� �ñ����
	cParticleSet*	m_pFireEffect;		// ���� ȭ�����

										// ���� ���ݽ� �ǰ� �ڽ� ���� ����
	float			m_fHitCircleRadian;
	D3DXVECTOR3		m_vHitCirclePos[2];

	// ���α׷��� ��
	cProgressBar*		m_pHpBar;
	cSprite*			m_BackBar;

public:
	cKelsaik();
	~cKelsaik();

	void Setup();

	/////////Update Function//////////
	void Update();
	void Idle_Update();
	void Awake_Update();
	void Awake_Chase();
	void Awake_Battle();
	void Battle_Update();
	void Turn_Update();
	void Walk_Update();
	void Death_Update();
	void Death_Die();

	void AnimUpdate();
	void UpdateWorld();
	void ParticleUpdate();
	//////////////////////////////////

	void Render();
	void HitCircleRender();
	////////Rendering Function///////

	void SetAnimWorld();
	bool isUseLocalAnim();


	////// etc ////////////////////////
	void ChangeState(MON_STATE state);
	void ChangeAnim(MON_Anim anim, bool isBlend, float Time = 1.0f);

	bool isPlayerInDistance(float distance);					// �÷��̾ ��Ÿ����մ�
	bool isEndPattern();						// ����(anim)�� �������� Ȯ��
	void CreatePatternCost();					// ���� �ڽ�Ʈ ����
	void SetAngleWithPlayer();					// �÷��̾� �ٶ󺸴� ����
	void SetTargetAngle();
	///////////////////////////////////

	////// ���� ���� ���� /////
	void AttackPattern01();
	void AttackPattern02();
	void AttackPattern03();
	void TurnLeft();
	void TurnRight();
	void TurnBack();
	void Berserk();

	//// ���� �ǰ� ���� ///
	
	// �ǰ� ���� ����
	void SetReactionPattern(int patternNum);

	void DamageReaction();
	void ReactionGroggy();
	void ReactionDown();

	// ������ �޴� �Լ�
	void Damaged(float Damaged, D3DXVECTOR3 pos);


	// ���α׷����� ���� �Լ�

	void SetUpStateBar();
	void UpdateUpStateBar();
	void RenderUpStateBar();


	void SetLight(); // �ǰݽ� ���ڰŸ��� ����

};

// ���� �Ƕ�
