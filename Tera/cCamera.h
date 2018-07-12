#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT			beforePt;
	bool			isDrag;
	float			m_fWorldX;
	float			m_fWorldY;
	float			m_fWorldZ;

	D3DXMATRIX		m_matRotateX;
	D3DXMATRIX		m_matRotateY;
	D3DXMATRIX		m_matRotateZ;
	D3DXMATRIX		m_matTraslation;

	D3DXVECTOR3		m_position;

public:
	cCamera();
	~cCamera();

	void Setup();
	void Update(D3DXVECTOR3 target);


};

