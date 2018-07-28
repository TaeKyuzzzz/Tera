#pragma once

class cSpere;

class cRay
{
public :

	D3DXVECTOR3		m_vOriginal;	// ������ �ù���
	D3DXVECTOR3		m_vDirection;	// ���� ����

public:
	cRay();
	~cRay();

	cRay RayAtViewSpace(int nScreenX, int nScreenY);
	cRay RayAtWorldSpace(int nScreenX, int nScreenY);
	float IsPicked(cSpere* spere);
	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3 & vPickedPosition);
};

