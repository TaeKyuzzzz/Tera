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

	D3DXVECTOR3 m_vOriginal; //������ ��� ����(���콺�� Ŭ���� ��ǥ)
	D3DXVECTOR3 m_vRay_Direction; //������ ����(ȭ�� �������� ���ϰ� ��)
};

