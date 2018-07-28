#include "stdafx.h"
#include "cMonster.h"

#include "iMap.h"

cMonster::cMonster()
	: m_fRotY(0.0f)
	, m_vDirection(1, 0, 0)
	, m_vPosition(0, 0, 0)
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
	, m_bEscapeToggle2(false)
	, m_bIdle(true)
	, m_bAtkTerm(true)
	, m_bAngleLock(false)
	, m_bDeath(false)
	, m_bFlinch(false)
	, m_bWalkOnOff(false)
	, m_bStart(false)
	, m_pRimLight(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matAnimWorld);
}


cMonster::~cMonster()
{
	SAFE_RELEASE(m_pRimLight);
}

void cMonster::Setup()
{
	cGameObject::Setup();
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

void cMonster::MonoBehavior(void)
{
}

bool cMonster::Attack(float damage)
{

	return false;
}

void cMonster::RimLightSetup(float start, float end, float multiplier,
	float RimColor, float LightDirection, float lightColor, float AmbientColor)
{
	D3DXMATRIX   matView, matWorld, matProj;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixIdentity(&matWorld);
	m_pRimLight->SetMatrix("WorldMatrix", &matWorld);
	m_pRimLight->SetMatrix("ViewMatrix", &matView);
	m_pRimLight->SetMatrix("ProjectionMatrix", &matProj);
	
	D3DXVECTOR3 v = CAMERAMANAGER->GetCameraPosition();

	m_pRimLight->SetFloat("Rim_Start", 0.7f);
	m_pRimLight->SetFloat("Rim_End", 1.00f);
	m_pRimLight->SetFloat("Rim_Multiplier", 1.00f);
	m_pRimLight->SetVector("Rim_Color", &D3DXVECTOR4(1,0,0,0));
	m_pRimLight->SetVector("LightDirection", &D3DXVECTOR4(-v.x, -v.y, -v.z,0.0f));
	m_pRimLight->SetVector("LightColor", &D3DXVECTOR4(0.9f, 0.9f, 0.9f,0.0f));
	m_pRimLight->SetVector("AmbientColor", &D3DXVECTOR4(0.4f,0.4f,0.4f,0.0f));
	m_pRimLight->SetVector("ViewI", &D3DXVECTOR4(v.x, v.y, v.z, 1));
	m_pRimLight->SetFloat("Alpha",0.0f);
}

void cMonster::RimLightSetup(D3DXVECTOR4 color, float offset, float Alpha)
{
	D3DXMATRIX   matView, matWorld, matProj;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixIdentity(&matWorld);
	m_pRimLight->SetMatrix("WorldMatrix", &matWorld);
	m_pRimLight->SetMatrix("ViewMatrix", &matView);
	m_pRimLight->SetMatrix("ProjectionMatrix", &matProj);

	D3DXVECTOR3 v = CAMERAMANAGER->GetCameraPosition();

	m_pRimLight->SetFloat("Rim_Start", 0.7f);
	m_pRimLight->SetFloat("Rim_End", 1.00f);
	m_pRimLight->SetFloat("Rim_Multiplier", 1.00f);
	m_pRimLight->SetVector("Rim_Color", &color);
	m_pRimLight->SetVector("LightDirection", &D3DXVECTOR4(-v.x, -v.y, -v.z, 0.0f));
	m_pRimLight->SetVector("LightColor", &D3DXVECTOR4(0.9f, 0.9f, 0.9f, 0.0f));
	m_pRimLight->SetVector("AmbientColor", &D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	m_pRimLight->SetVector("ViewI", &D3DXVECTOR4(v.x, v.y, v.z, 1));
	m_pRimLight->SetFloat("Alpha", Alpha);
	m_pRimLight->SetFloat("Offset", offset);
}
