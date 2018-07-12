#pragma once
#include "../cGameObject.h"

class cMonster : public cGameObject
{
public:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXMATRIX		m_matWorld;

	float			m_fSpeed;

	//iMap*			m_pMap;

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

	//몬스터 네비게이션 관련

	bool			m_bIsGen;									//몬스터 젠여부. 죽어 사라지면 false.
	bool			m_bAwake;									//캐릭터를 인지했을경우 True, 다시 멀어지면 false
	SYNTHESIZE_REF(D3DXVECTOR3, m_vBehaviorSpot, Spot);			//몬스터 활동 지점
	float			m_fAreaRadius;								//중점을 기준으로 한 몬스터 활동반경.
	float			m_fRunSpeed;								//몬스터 이동속도, Awake된 경우에는 별도로 +처리.
	float			m_fTimeofDeath;								//몬스터죽은 시점을 기록. 몬스터가 죽은후 일정시간뒤에 다시 해당위치에 부활.




public:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	cMonster();
	~cMonster();

	void Setup();
	void Update();
	void Render();

	//몬스터 어슬렁거리는것 구현
	virtual void MonoBehavior(void) = 0;
};

