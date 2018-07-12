#pragma once
#include "cCharacter.h"

class cCharacterClass03 : public cCharacter
{
protected:
	enum CHARA_STATE
	{
		CH_STATE_AdvLeap,
		CH_STATE_BackAttackShot,
		CH_STATE_BackAttackStart,
		CH_STATE_BehindCartchShot,
		CH_STATE_BehindCatchStart,
		CH_STATE_bReactionCom2,
		CH_STATE_bReactionCom3,
		CH_STATE_bReactionDown2,
		CH_STATE_bReactionDown3,
		CH_STATE_bReactionLand3,
		CH_STATE_bReactionRolling3,
		CH_STATE_bReactionStart,
		CH_STATE_bReactionStart3,
		CH_STATE_combo1,
		CH_STATE_combo1R,
		CH_STATE_combo2,
		CH_STATE_combo2R,
		CH_STATE_combo3,
		CH_STATE_combo3R,
		CH_STATE_combo4,
		CH_STATE_CutHead,
		CH_STATE_CuttingSlash,
		CH_STATE_Death,
		CH_STATE_Dearhwait,
		CH_STATE_DwonBlow,
		CH_STATE_DrawSword,
		CH_STATE_DrawSwordCharge,
		CH_STATE_DrawSwordEnd,
		CH_STATE_DrawSwordLoop,
		CH_STATE_DrawSwordMove,
		CH_STATE_FlatBlade,
		CH_STATE_gaiaCrush01,
		CH_STATE_gaiaCrush02,
		CH_STATE_gaiaCrush03,
		CH_STATE_groggy1,
		CH_STATE_GuardReaction1,
		CH_STATE_handySlash,
		CH_STATE_inweapon,
		CH_STATE_JawBreaker,
		CH_STATE_outweapon,
		CH_STATE_RagingStrike,
		CH_STATE_RetreatKick,
		CH_STATE_RisingAttack,
		CH_STATE_run,
		CH_STATE_slidingCharge,
		CH_STATE_slidingEnd,
		CH_STATE_slidingSlash,
		CH_STATE_slidingSlash01Shot,
		CH_STATE_sReaction,
		CH_STATE_StingerBlade,
		CH_STATE_swordDanceLoop,
		CH_STATE_swordDanceShot,
		CH_STATE_swordDanceStart,
		CH_STATE_tumbling,
		CH_STATE_Wait,
		CH_STATE_WindCutter1,
		CH_STATE_WindCutter1R,
		CH_STATE_WindCutter2,
		CH_STATE_WindCutter2R,
		CH_STATE_WindCutter3,
		CH_STATE_COUNT
	};


	CHARA_STATE			m_state;
	bool				m_bIsDone;

	float				m_fCurAnimTime;
	float				m_fAnimTime[CH_STATE_COUNT];

	float				m_fTime;

	bool				m_bIsBlend;

	bool				m_bDoCombo; // 연격중 콤보 입력여부
public:
	cCharacterClass03();
	~cCharacterClass03();


	void Setup();
	void Update();
	void Render();

	// 애니메이션 월드 좌표를 세팅
	void SetAnimWorld();

	void ProcessCombo();
	void ProcessDamaged();
	void ProcessGaiaCrash();

	void ProcessBigDamaged();
	void ProcessDie();

	void Move();

	void Damaged(float damage);
	void BigDamaged();
	void Die();

};

