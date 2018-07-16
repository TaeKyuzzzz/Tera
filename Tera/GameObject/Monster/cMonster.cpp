#include "stdafx.h"
#include "cMonster.h"

#include "iMap.h"

cMonster::cMonster()
	: m_fRotY(0.0f)
	, m_vDirection(1, 0, 0)
	, m_vPosition(1400, 0, 0)
	, m_fSpeed(1.0f)
	, m_vBeforeAnimPos(0, 0, 0)
	, m_vCurAnimPos(0, 0, 0)
	, m_bIsGen(true)
	, m_bAwake(false)
	, m_bFight(false)
	, m_vBehaviorSpot(500, 0, 0)
	, m_pMap(NULL)
	, m_bAnimation(false)
	, m_bEscapeToggle(false)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matAnimWorld);
}


cMonster::~cMonster()
{
}

void cMonster::Setup()
{
}

void cMonster::Update()
{
	PlusMapHeight();
}

void cMonster::Render()
{
}

void cMonster::PlusMapHeight()
{
	if (m_pMap)
		m_pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
}
