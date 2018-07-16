#include "stdafx.h"
#include "cParticle.h"


cParticle::cParticle()
	: m_curTime(0.0f)
{
	m_isUse = true;
}


cParticle::~cParticle()
{
}

void cParticle::Setup(float _fTime, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vDir,
	float _speed, float _acc, float _radian, D3DXCOLOR _color, const char * szFile)
{
	m_isUse = true;
	m_fTime = _fTime;
	m_stPaticle.p = _vPos;
	m_vPosition = _vPos;
	m_vDirecton = _vDir;
	m_fSpeed = _speed;
	m_fFirstSpeed = _speed;
	m_fAcc = _acc;
	m_fRdian = _radian;
	m_stPaticle.c = _color;
	
	m_pTexture = TEXTUREMANAGER->GetTexture(szFile);
	
}

void cParticle::Setup()
{
	m_isUse = true;
	m_stPaticle.p = m_vPosition;
	m_curTime = 0.0f;
	m_fSpeed = m_fFirstSpeed;
}

void cParticle::Update()
{

	if (m_isUse)
	{
		m_curTime += TIMEMANAGER->GetEllapsedTime();
		// 정해진 방향에 회전각을 입히고 // 일단 보류
		D3DXMATRIX matS, matT;
		//ST_PCT_VERTEX  vertex = m_stPaticle;
		// 시간에 따른 스케일 변경
		scale = m_curTime / m_fTime;
		
		if (scale > 1.0f)
		{
			m_isUse = false;
			return;
		}

		D3DXMatrixScaling(&matS, scale, scale, scale);
		
		// 이동 방향, 스피드가 적용된 벡터로 T 행렬 만듦
		D3DXVECTOR3 v = m_vDirecton * m_fSpeed;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, v.x, v.y,v.z);
		
		// 변환 행렬 생성
		m_matTS = matT;
		D3DXVec3TransformCoord(&m_stPaticle.p, &m_stPaticle.p, &m_matTS);
		
		// 스피드에 가속도를 적용
		m_fSpeed += m_fAcc;
	}
}

void cParticle::Render()
{
	if (m_isUse)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matTS);
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW((1.0f - scale) * 100));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
			1,&m_stPaticle,sizeof(ST_PC_VERTEX));
	}

}
