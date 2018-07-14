#pragma once
class cParticle
{
private :
	
	//bool				m_isUse;		// 사용여부 
	SYNTHESIZE(bool, m_isUse, IsUse);
	ST_PC_VERTEX		m_stPaticle;	// 실제로 렌더될 버텍스

	D3DXMATRIX			m_matTS;

	float				m_fFirstSpeed;
	float				m_fTime;		// 파티클의 생존 시간
	LPDIRECT3DTEXTURE9	m_pTexture;		// 파티클의 텍스쳐
	
	D3DXVECTOR3			m_vPosition;	// 파티클의 위치
	D3DXVECTOR3			m_vDirecton;	// 파티클의 이동 방향
	float				m_fSpeed;		// 파티클의 속도
	float				m_fAcc;			// 파티클의 가속도
	float				m_fRdian;		// 파티클의 회전각
	D3DXCOLOR			m_stColor;		// 파티클의 색상

	float				scale;

	float				m_curTime;
public:
	cParticle();
	~cParticle();

	void Setup(float _fTime, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vDir,
		float _speed, float _acc, float _radian, D3DXCOLOR _color, 
		 const char * szFile);

	void Setup();
	void Update();
	void Render();
};

// 일단 지정된 알파로 그려내도록 해보자
// 텍스쳐 저장 방법은 경로? 아님 그대로?? 
// 당연히 경로로 해야지 멍청아

// 파티클셋 클래스 -> 텍스쳐의 경로를 저장해야함
// 파티클 -> 파티클 셋에서 저장된 경로로 초기화를 해줘야함
// ㄱㄱ