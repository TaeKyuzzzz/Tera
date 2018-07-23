#pragma once
#include "cMonster.h"

class cSkinnedMesh;
class cParticleSet;

class cKelsaik : public cMonster
{
protected:
	enum MON_MODE
	{
		IDLE,
		AWAKE,
		DEATH
	};
	
	enum MON_IDLE
	{
		ROAMING,
		COMEBACK
	};
	enum MON_AWAKE
	{
		CHASE,
		BATTLE
	};
	enum MON_DEATH
	{
		DIE,
		REBIRTH
	};

	enum MON_STATE
	{
		MON_Anim_Walk,
		MON_Anim_Wait,
		MON_Anim_unarmedwait,
		MON_Anim_Spawn,
		MON_Anim_run,
		MON_Anim_roundmove02,
		MON_Anim_roundmove01,
		MON_Anim_roundAtk02,
		MON_Anim_roundAtk01,
		MON_Anim_ReactionStart,
		MON_Anim_ReactionLoop,
		MON_Anim_ReactionEnd,
		MON_Anim_ReactonAtk,
		MON_Anim_ReactionAdd,
		MON_Anim_moveAtk,
		MON_Anim_modeAlarm,
		MON_Anim_jumpevasion02,
		MON_Anim_jumpevasion01,
		MON_Anim_heavyatk02,
		MON_Anim_heavyatk01,
		MON_Anim_groggy,
		MON_Anim_flinch,
		MON_Anim_deathwait,
		MON_Anim_Death,
		MON_Anim_backAtk,
		MON_Anim_atk02,
		MON_Anim_atk01,
		MON_Anim_aggrochange,
		MON_Anim_COUNT
	};

	MON_MODE			MODE;	//얘에 따라서 호출하는 하위업데이트가 다르다.
	MON_IDLE			eIDLE;
	MON_AWAKE			eAWAKE;
	MON_DEATH			eDEATH;

	cSkinnedMesh*		m_pMonster;
	ST_BONE*			m_pDummyRoot;
	ST_BONE*			m_pBIP;

	MON_STATE			m_state;
	MON_STATE			m_currState;

	bool				m_bIsDone;

	float				m_fCurAnimTime;
	float				m_fAnimTime[MON_Anim_COUNT];

	float				m_fTime;

	bool				m_bIsBlend;

	float				m_fCosVal;

	//행동패턴 디자인에 쓰인 임시변수
	D3DXVECTOR3			temp;
	D3DXVECTOR2			tt;

	//공격에 쓰이는 본

	ST_BONE*			m_pHandR;
	ST_BONE*			m_pHandL;
	cSpere*				m_pSphereR;
	cSpere*				m_pSphereL;

	float				m_fFightZone;


	cParticleSet*		m_pParticleBleeding;

public:
	cKelsaik();
	~cKelsaik();
	
	void Setup();

	/////////Update Function//////////
	void Update();
	void Idle_Update();
	void Idle_Roaming();
	void Idle_Back_to_SquareOne();
	void Awake_Update();
	void Awake_Chase();
	void Awake_Battle();
	void Death_Update();
	void Death_Die();
	void Death_Rebirth();

	void AnimUpdate();
	//////////////////////////////////

	void Render();

	////////Rendering Function///////

	void SetAnimWorld();
	bool isUseLocalAnim();



};

