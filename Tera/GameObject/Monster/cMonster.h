#pragma once
#include "../cGameObject.h"

class iMap;

class cMonster : public cGameObject
{
public:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXMATRIX		m_matWorld;

	float			m_fSpeed;

	//iMap*			m_pMap;
	SYNTHESIZE(iMap*, m_pMap, Map);

	float			m_fCosVal; // 카메라 기준 각도

	D3DXMATRIX		m_matAnimWorld;
	D3DXVECTOR3		m_vCurAnimPos;
	D3DXVECTOR3		m_vBeforeAnimPos;

	float			m_fHpMax;
	float			m_fHpCur;
	float			m_fHpUI;

	float			m_fMpMax;
	float			m_fMpCur;
	float			m_fMpUI;

	//구간 애니메이션이 진행중이냐
	bool			m_bAnimation;
	bool			m_bAngleLock;

	//몬스터 네비게이션 관련

	bool			m_bIsGen;									//몬스터 젠여부. 죽어 사라지면 false.
	bool			m_bAwake;									//캐릭터를 인지했을경우 True, 다시 멀어지면 false
	bool			m_bFight;									//특정거리로 좁혀지면 전투시작.
	SYNTHESIZE_REF(D3DXVECTOR3, m_vBehaviorSpot, Spot);			//몬스터 활동 지점
	float			m_fAreaRadius;								//중점을 기준으로 한 몬스터 활동반경.
	float			m_fRunSpeed;								//몬스터 이동속도, Awake된 경우에는 별도로 +처리.
	float			m_fTimeofDeath;								//몬스터죽은 시점을 기록. 몬스터가 죽은후 일정시간뒤에 다시 해당위치에 부활.
	float			m_fEscapeTime;								//인식범위에서 탈출한 시점을 기록
	bool			m_bEscapeToggle;							//토글변수를 이용하여 시점 기록
	float			m_fEscapeTime2;								//인식범위에서 탈출한 시점을 기록(전투인 경우)
	bool			m_bEscapeToggle2;							//토글변수를 이용하여 시점 기록(전투인 경우)
	bool			m_bIdle;									//아무인식도 없는 상태. 
	bool			m_bAtkTerm;									//공격사이사이의 쉬는거

	bool			m_bDeath;									//죽음을 알리는 불변수
	bool			m_bFlinch;									//피격을 알리는 불변수




public:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	cMonster();
	~cMonster();

	void Setup();
	void Update();
	void Render();

	//몬스터 높이맵 적용
	void PlusMapHeight();

	//몬스터 어슬렁거리는것 구현
	virtual void MonoBehavior(void) = 0;

	// 공격
	virtual bool Attack(float damage);
};

