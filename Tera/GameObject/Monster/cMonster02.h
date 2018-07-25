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

	MON_MODE			MODE;	//얘에 따라서 호출하는 하위업데이트가 다르다.

	cSkinnedMesh*		m_pMonster;						// 몬스터 스켈레톤 메시
	ST_BONE*			m_pDummyRoot;					// 루트 본
	ST_BONE*			m_pBIP;							// 고정된 본

	MON_STATE			m_state;							// 재생중 애니메이션
	MON_STATE			m_currState;						// 바뀔 애니메이션

	bool				m_bIsDone;						// 애니메이션이 끝났니?

	float				m_fCurAnimTime;					// 재생된 시간 애니메이션
	float				m_fAnimTime[MON_STATE_COUNT];	// 재생돼야할 총 시간
	float				m_fTime;						// 애니 걸린시간
	bool				m_bIsBlend;						// 애니 블렌딩 처리여부
	float				m_fCosVal;						// 봐야할 각도

	
														
	//행동패턴 디자인에 쓰인 임시변수
	D3DXVECTOR3			temp;
	D3DXVECTOR2			tt;

	//공격에 쓰이는 본

	ST_BONE*			m_pHandR;						// 오른팔 (파이어
	ST_BONE*			m_pHandL;						// 왼팔	 (아이스
	cSpere*				m_pSphereR;						// 오른팔 구 (충돌용
	cSpere*				m_pSphereL;						// 왼팔 구 (충돌용

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