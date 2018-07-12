#include "stdafx.h"
#include "cMonster.h"


cMonster::cMonster()
	: m_fRotY(0.0f)
	, m_vDirection(1, 0, 0)
	, m_vPosition(0, 0, 0)
	, m_fSpeed(1.0f)
	, m_vBeforeAnimPos(0, 0, 0)
	, m_vCurAnimPos(0, 0, 0)
	, m_bIsGen(true)
	, m_bAwake(false)
	, m_vBehaviorSpot(0, 0, 0)
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

}

void cMonster::Render()
{
}
