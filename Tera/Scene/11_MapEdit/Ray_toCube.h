#pragma once
class cRay_toCube
{
public:
	cRay_toCube();
	~cRay_toCube();

	static cRay_toCube RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay_toCube RayAtWorldSpace(int nScreenX, int nScreenY);
	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2,
		OUT D3DXVECTOR3& vPickedPosition, OUT float& ray_dis);

	D3DXVECTOR3 m_vOriginal; //광선의 출발 지점(마우스로 클릭한 좌표)
	D3DXVECTOR3 m_vRay_Direction; //광선의 방향(화면 안쪽으로 향하게 됨)
};

