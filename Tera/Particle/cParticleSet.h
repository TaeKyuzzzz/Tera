#pragma once

class cParticle;

enum PARTICLE_TYPE
{
	PTC_TYPE_LOOP,
	PTC_TYPE_ONCE
};

class cParticleSet
{
private :

	PARTICLE_TYPE			m_type;

	vector<cParticle*>		m_vecParticle;

	float					m_fTime;		// 파티클 수명
	float					m_fSpeed;

	float					m_fAcc;
	int						m_fAccMin;
	int						m_fAccMax;

	float					m_fCurTime;

	// 초기 위치들
	int						m_fPositionX;
	int						m_fRandPosXMin;
	int						m_fRandPosXMax;

	int						m_fPositionY;
	int						m_fRandPosYMin;
	int						m_fRandPosYMax;
	
	int						m_fPositionZ;
	int						m_fRandPosZMin;
	int						m_fRandPosZMax;
	
	// 방향 값 ( 렌덤부분은 -1.0f ~ 1.0f )
	int						m_fDirectionX;
	int						m_fRandDirXMin;
	int						m_fRandDirXMax;

	int						m_fDirectionY;
	int						m_fRandDirYMin;
	int						m_fRandDirYMax;

	int						m_fDirectionZ;
	int						m_fRandDirZMin;
	int						m_fRandDirZMax;

	char 					m_szFile[1024];
	D3DXCOLOR				m_stColor;
	LPDIRECT3DTEXTURE9		m_pTexture;
public:
	cParticleSet();
	~cParticleSet();

	void Setup(PARTICLE_TYPE type,float time, float speed,
		int acc,  int accMin,	   int accMax,
		int posX, int randPosXMin, int randPosXMax,
		int posY, int randPosYMin, int randPosYMax,
		int posZ, int randPosZMin, int randPosZMax,
		int dirX, int randDirXMin, int randDirXMax,
		int dirY, int randDirYMin, int randDirYMax,
		int dirZ, int randDirZMin, int randDirZMax,
		const char * szFile, D3DXCOLOR color);
	void Update();
	
	void Render();
	
	void Start();
};

