#pragma once
#include "cMonster.h"

class cSkinnedMesh;
class cParticleSet;

#define NUMOFPATTERN	3

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

	enum MON_Anim
	{
		MON_Anim_aggrochange,
		MON_Anim_atk01,
		MON_Anim_atk02,
		MON_Anim_backAtk,
		MON_Anim_Death,
		MON_Anim_deathwait,
		MON_Anim_flinch,
		MON_Anim_groggy,
		MON_Anim_heavyatk01,
		MON_Anim_heavyatk02,
		MON_Anim_jumpevasion01,
		MON_Anim_jumpevasion02,
		MON_Anim_modeAlarm,
		MON_Anim_moveAtk,
		MON_Anim_ReactionAdd,
		MON_Anim_ReactonAtk,
		MON_Anim_ReactionEnd,
		MON_Anim_ReactionLoop,
		MON_Anim_ReactionStart,
		MON_Anim_roundAtk01,
		MON_Anim_roundAtk02,
		MON_Anim_roundmove01,
		MON_Anim_roundmove02,
		MON_Anim_run,
		MON_Anim_Spawn,
		MON_Anim_unarmedwait,
		MON_Anim_Wait,
		MON_Anim_Walk,
		MON_Anim_COUNT
	};

	MON_STATE		STATE;	//얘에 따라서 호출하는 하위업데이트가 다르다.

	cSkinnedMesh*	m_pMonster;						// 몬스터 스켈레톤 메시
	ST_BONE*		m_pDummyRoot;					// 루트 본
	ST_BONE*		m_pBIP;							// 고정된 본

	MON_Anim		m_Anim;							// 재생중 애니메이션
	MON_Anim		m_currAnim;						// 바뀔 애니메이션

	bool			m_bIsDone;						// 애니메이션이 끝났니?
		
	float			m_fCurAnimTime;					// 재생된 시간 애니메이션
	float			m_fAnimTime[MON_Anim_COUNT];	// 재생돼야할 총 시간
	float			m_fTime;						// 애니 걸린시간
	bool			m_bIsBlend;						// 애니 블렌딩 처리여부
	float			m_fCosVal;						// 봐야할 각도
	float			m_fTargetAngle;

	bool			m_isDoingPattern;
	bool			m_partternCost;

	int				m_nPatternNum;
	float			m_fPatternCostTime;
	//행동패턴 디자인에 쓰인 임시변수
	D3DXVECTOR3		temp;
	D3DXVECTOR2		tt;

	//공격에 쓰이는 본

	ST_BONE*		m_pHandR;						// 오른팔 (파이어
	ST_BONE*		m_pHandL;						// 왼팔	 (아이스
	cSpere*			m_pSphereR;						// 오른팔 구 (충돌용
	cSpere*			m_pSphereL;						// 왼팔 구 (충돌용

	float			m_fFightZone;


	// 파티클 효과 1번 출력에 쓰는 불 변수
	bool			m_pEffectCost;					//
	cParticleSet*	m_pParticleBleeding;			// 출혈 파티클
	cParticleSet*	m_pIceHand;			//IceHand2			// 왼손 아이스 파티클
	cParticleSet*	m_pFireHand;		// FireHand			// 오른손 파이어 파티클
	cParticleSet*	m_pIceEffect;		// 보스 냉기충격
	cParticleSet*	m_pFireEffect;		// 보스 화염충격

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

	////////Rendering Function///////

	void SetAnimWorld();
	bool isUseLocalAnim();


	////// etc ////////////////////////
	void ChangeState(MON_STATE state);
	void ChangeAnim(MON_Anim anim, bool isBlend);
	
	bool isPlayerInDistance(float distance);					// 플레이어가 사거리에잇니
	bool isEndPattern();						// 패턴(anim)이 끝났는지 확인
	void CreatePatternCost();					// 패턴 코스트 생성
	void SetAngleWithPlayer();					// 플레이어 바라보는 각도
	void SetTargetAngle();
	///////////////////////////////////

	////// 몬스터 공격 패턴 /////
	void AttackPattern01();
	void AttackPattern02();
	void AttackPattern03();

};

