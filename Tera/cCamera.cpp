#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye( -100, 50, 0)
	, m_vLookAt(300, 0, 0)
	, m_vUp(0, 1, 0)
	, beforePt{ 0,0 }
	, isDrag(false)
	, m_fWorldX(0.0f)
	, m_fWorldY(0.0f)
	, m_fWorldZ(0.0f)
{
	D3DXMatrixIdentity(&m_matRotateX);
	D3DXMatrixIdentity(&m_matRotateY);
	D3DXMatrixIdentity(&m_matRotateZ);
	D3DXMatrixIdentity(&m_matTraslation);
}


cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	m_position = D3DXVECTOR3(0, 0, 0);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH // 왼손 좌표계의 프로젝션 매트릭스를 만드는 함수
	(
		&matProj,
		D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom,
		1.0f,
		10000.0f
	);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj); // 세팅

}

void cCamera::Update(D3DXVECTOR3 target)
{
	//if (g_pKeyManager->IsStayKeyDown(VK_CONTROL))
	//{
	//	if (g_pKeyManager->IsStayKeyDown(VK_RBUTTON))
	//	{
	//		if (isDrag == false)
	//		{
	//			isDrag = true;
	//			beforePt = ptMouse;
	//		}
	//		else
	//		{
	//			//
	//m_fWorldX += (ptMouse.y - beforePt.y);
	//if (m_fWorldX > 90) m_fWorldX = 89;
	//if (m_fWorldX < -90) m_fWorldX = -89;
	//D3DXMatrixRotationX(&m_matRotateX, m_fWorldX * D3DX_PI / 180.0f);

	m_fWorldY += (ptMouse.x - beforePt.x);
	//D3DXMatrixRotationY(&m_matRotateY, m_fWorldY * D3DX_PI / 180.0f);

	beforePt = ptMouse;
	
	//
	//		}
	//	}
	//}

	//if (g_pKeyManager->IsOnceKeyUp(VK_RBUTTON))
	//{
	//	isDrag = false;
	//	beforePt = { 0,0 };
	//}

	//if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD8))
	//	m_fWorldX++;
	//else if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD2))
	//	m_fWorldX--;
	//
	//if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD1))
	//	m_fWorldY++;
	//else if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD3))
	//	m_fWorldY--;
	//
	//if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD7))
	//	Wheel += 10;
	//else if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD9))
	//	Wheel -= 10;
	//
	//if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD4))
	//	m_fWorldZ += 10;
	//else if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD6))
	//	m_fWorldZ -= 10;

	//D3DXMatrixRotationX(&m_matRotateX, m_fWorldX * D3DX_PI / 180.0f);
	D3DXMatrixRotationY(&m_matRotateY, m_fWorldY * D3DX_PI / 180.0f);
	//D3DXMatrixRotationZ(&m_matRotateZ, m_fWorldZ * D3DX_PI / 180.0f);

	D3DXMatrixTranslation(&m_matTraslation, Wheel, 0, 0);

	D3DXVECTOR3 vEye;
	float x = m_vEye.x;

	D3DXVec3TransformCoord(&vEye, &m_vEye, &m_matTraslation);
	D3DXVec3TransformCoord(&vEye, &vEye, &m_matRotateX);
	D3DXVec3TransformCoord(&vEye, &vEye, &m_matRotateY);
	//D3DXVec3TransformCoord(&vEye, &vEye, &m_matRotateZ);
	x = vEye.x - x;

	if (target)
		vEye += target;


	D3DXVECTOR3 vLookAt = m_vLookAt;
	//vLookAt.x += x;

	//D3DXVec3TransformCoord(&vLookAt, &m_vLookAt, &m_matTraslation);
	//D3DXVec3TransformCoord(&vLookAt, &vLookAt, &m_matRotateX);
	D3DXVec3TransformCoord(&vLookAt, &vLookAt, &m_matRotateY);

	if (target)
		vLookAt += target;


	g_vCamera = vLookAt - vEye;
	g_vCamera.y = 0;
	D3DXVec3Normalize(&g_vCamera,&g_vCamera);

	D3DXVECTOR3 vUp = m_vUp;

	//D3DXVec3TransformCoord(&vUp, &vUp, &m_matRotateZ);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);


	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}
