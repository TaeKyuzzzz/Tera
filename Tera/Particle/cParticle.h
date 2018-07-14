#pragma once
class cParticle
{
private :
	
	//bool				m_isUse;		// ��뿩�� 
	SYNTHESIZE(bool, m_isUse, IsUse);
	ST_PC_VERTEX		m_stPaticle;	// ������ ������ ���ؽ�

	D3DXMATRIX			m_matTS;

	float				m_fFirstSpeed;
	float				m_fTime;		// ��ƼŬ�� ���� �ð�
	LPDIRECT3DTEXTURE9	m_pTexture;		// ��ƼŬ�� �ؽ���
	
	D3DXVECTOR3			m_vPosition;	// ��ƼŬ�� ��ġ
	D3DXVECTOR3			m_vDirecton;	// ��ƼŬ�� �̵� ����
	float				m_fSpeed;		// ��ƼŬ�� �ӵ�
	float				m_fAcc;			// ��ƼŬ�� ���ӵ�
	float				m_fRdian;		// ��ƼŬ�� ȸ����
	D3DXCOLOR			m_stColor;		// ��ƼŬ�� ����

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

// �ϴ� ������ ���ķ� �׷������� �غ���
// �ؽ��� ���� ����� ���? �ƴ� �״��?? 
// �翬�� ��η� �ؾ��� ��û��

// ��ƼŬ�� Ŭ���� -> �ؽ����� ��θ� �����ؾ���
// ��ƼŬ -> ��ƼŬ �¿��� ����� ��η� �ʱ�ȭ�� �������
// ����