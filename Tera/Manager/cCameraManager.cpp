#include "stdafx.h"
#include "cCameraManager.h"
#include "cCamera.h"

cCameraManager::cCameraManager()
	: m_pCamera(NULL)
	, m_fShakingTime(0.0f)
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Create()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();
	m_type = CAMERA_FREE;
}

void cCameraManager::Update()
{
	D3DXMATRIX	mat;
	D3DXMatrixIdentity(&mat);
	if (m_fShakingTime > 0.0f)
	{
		m_fShakingTime -= TIMEMANAGER->GetEllapsedTime();

		mat._41 = rand() % 10 - 5;
		mat._42 = rand() % 10 - 5;
		mat._43 = rand() % 10 - 5;
	}
	m_pCamera->SetWorld(mat);

	switch (m_type)
	{
	case CAMERA_FREE:
		if (g_vPlayerPos)
			m_pCamera->Update(*g_vPlayerPos);
		else
			m_pCamera->Update(D3DXVECTOR3(0, 0, 0));
		break;
	case CAMERA_FIX:
		if (g_vPlayerPos)
			m_pCamera->UpdateFix(*g_vPlayerPos);
		else
			m_pCamera->UpdateFix(D3DXVECTOR3(0, 0, 0));
		break;
	}
}

void cCameraManager::Shaking(float time)
{
	m_fShakingTime = time;
}

void cCameraManager::Destroy()
{
	SAFE_DELETE(m_pCamera);
}

void cCameraManager::SetType(CAMERA_TYPE type)
{
	m_type = type;
	if (m_type == CAMERA_FREE)
	{
		m_pCamera->SetBeforePT(POINT{ 0,0 });
		m_pCamera->SetCurrentPT(POINT{ 0,0 });
	}
}

D3DXVECTOR3 cCameraManager::GetCameraPosition()
{

	return m_pCamera->GetCameraPosition();
}
