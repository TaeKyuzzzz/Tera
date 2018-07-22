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

	MON_MODE			MODE;	//얘에 따라서 호출하는 하위업데이트가 다르다.

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
	//////////////////////////////////

	void Render();

	////////Rendering Function///////

	void SetAnimWorld();
	bool isUseLocalAnim();



};

