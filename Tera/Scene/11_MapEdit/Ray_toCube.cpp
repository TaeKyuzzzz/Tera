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
	//==각각 Viewport와 Projection의 매트릭스를 가져온다.
	D3DVIEWPORT9 ViewPort;
	g_pD3DDevice->GetViewport(&ViewPort);

	D3DXMATRIX MatProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &MatProjection);

	cRay_toCube r;
	//==시야공간의 선택 반직선을 계산하는 코드. 시야 공간 반직선 정의
	r.m_vRay_Direction.x = ((2.0f * nScreenX) / ViewPort.Width - 1.0f) / MatProjection._11;
	r.m_vRay_Direction.y = ((-2.0f * nScreenY) / ViewPort.Height + 1.0f) / MatProjection._22;
	r.m_vRay_Direction.z = 1.0f;

	return r; //반직선만 구하고 cBBox클래스를 리턴.
}

cRay_toCube cRay_toCube::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay_toCube r = cRay_toCube::RayAtViewSpace(nScreenX, nScreenY);

	//== World 좌표계를 Local좌표계로 전환.
	D3DXMATRIX matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	// 점을 변환할때는 D3DXVec3TransformCoord를, 벡터를 변환할 때에는 D3DXVec3TransformNormal을 써야 한다.
	D3DXVec3TransformCoord(&r.m_vOriginal, &r.m_vOriginal, &matInvView); // 첫번째 매개변수의 w = 1
	D3DXVec3TransformNormal(&r.m_vRay_Direction, &r.m_vRay_Direction, &matInvView); // 첫번재 매개변수의 w = 0

																					// 교차 판정을 위해 반직선 방향 벡터를 단위 길이로 만든다.
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

