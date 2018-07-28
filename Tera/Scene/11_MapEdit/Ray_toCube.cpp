#include "stdafx.h"
#include "Ray_toCube.h"


cRay_toCube::cRay_toCube()
	: m_vOriginal(0, 0, 0)
	, m_vRay_Direction(0., 0, 0)
{
}


cRay_toCube::~cRay_toCube()
{
}

cRay_toCube cRay_toCube::RayAtViewSpace(int nScreenX, int nScreenY)
{
	//==���� Viewport�� Projection�� ��Ʈ������ �����´�.
	D3DVIEWPORT9 ViewPort;
	g_pD3DDevice->GetViewport(&ViewPort);

	D3DXMATRIX MatProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &MatProjection);

	cRay_toCube r;
	//==�þ߰����� ���� �������� ����ϴ� �ڵ�. �þ� ���� ������ ����
	r.m_vRay_Direction.x = ((2.0f * nScreenX) / ViewPort.Width - 1.0f) / MatProjection._11;
	r.m_vRay_Direction.y = ((-2.0f * nScreenY) / ViewPort.Height + 1.0f) / MatProjection._22;
	r.m_vRay_Direction.z = 1.0f;

	return r; //�������� ���ϰ� cBBoxŬ������ ����.
}

cRay_toCube cRay_toCube::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay_toCube r = cRay_toCube::RayAtViewSpace(nScreenX, nScreenY);

	//== World ��ǥ�踦 Local��ǥ��� ��ȯ.
	D3DXMATRIX matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	// ���� ��ȯ�Ҷ��� D3DXVec3TransformCoord��, ���͸� ��ȯ�� ������ D3DXVec3TransformNormal�� ��� �Ѵ�.
	D3DXVec3TransformCoord(&r.m_vOriginal, &r.m_vOriginal, &matInvView); // ù��° �Ű������� w = 1
	D3DXVec3TransformNormal(&r.m_vRay_Direction, &r.m_vRay_Direction, &matInvView); // ù���� �Ű������� w = 0

																					// ���� ������ ���� ������ ���� ���͸� ���� ���̷� �����.
	D3DXVec3Normalize(&r.m_vRay_Direction, &r.m_vRay_Direction);

	return r;
}

bool cRay_toCube::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2,
	OUT D3DXVECTOR3 & vPickedPosition, OUT float & ray_dis)
{
	float u, v;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOriginal, &m_vRay_Direction, &u, &v, &ray_dis);
	vPickedPosition = m_vOriginal + (ray_dis * m_vRay_Direction);
	//vPickedPosition  = v0 + (u * (v1 - v0)) + (v * (v2 - v0));
	return b;
}

