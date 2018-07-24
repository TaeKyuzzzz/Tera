#pragma once
#include "GameObject/cGameObject.h"
#include "Manager/cUIManager.h"

class iMap;
class cSkinnedMesh;
class cParticleSet;

class cPoalong : public cGameObject
{
private:
	enum STATE
	{
		IDLE
	};

	float				m_fRotY;
	D3DXVECTOR3			m_vDirection;
	D3DXMATRIX			m_matWorld;
	SYNTHESIZE(iMap*, m_pMap, Map);
	float				m_fCosVal; // 카메라 기준 각도

	cSkinnedMesh*		m_pPoalong;
	ST_BONE*			m_pDummyRoot;

	STATE				m_state;
	STATE				m_currState;

	float				m_fCurAnimTime;
	float				m_fAnimTime;

	float				m_fTime;

	D3DXVECTOR3			m_vWhere_To_Stay;

public:
	cPoalong();
	~cPoalong();
	//------------------------기본함수


	void Setup();
	void Update();
	void Render();

	//높이맵 적용
	void PlusMapHeight();
};

