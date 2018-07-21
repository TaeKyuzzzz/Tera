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
		ATTACK,
		DAMAGED,
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


	/////////Update Function//////////

	MON_STATE Status;	//얘에 따라서 호출하는 하위업데이트가 다르다.

	/////////////////////////////////



public:
	cKelsaik();
	~cKelsaik();
	
	void Setup();

	/////////Update Function//////////
	void Update();
	void Idle_Update();
	void Awake_Update();
	void Attack_Update();
	void Damaged_Update();
	void Death_Update();
	//////////////////////////////////

	void Render();



};

