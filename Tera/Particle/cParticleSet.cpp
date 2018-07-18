#include "stdafx.h"
#include "cParticleSet.h"
#include "cParticle.h"

cParticleSet::cParticleSet()
	: m_fCurTime(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cParticleSet::~cParticleSet()
{
	for (int i = 0; i < m_vecParticle.size(); i++)
		SAFE_DELETE(m_vecParticle[i]);
}

void cParticleSet::Setup(PARTICLE_TYPE type,float time, float speed,
	int acc, int accMin, int accMax,
	int posX, int randPosXMin, int randPosXMax,
	int posY, int randPosYMin, int randPosYMax,
	int posZ, int randPosZMin, int randPosZMax,
	int dirX, int randDirXMin, int randDirXMax,
	int dirY, int randDirYMin, int randDirYMax,
	int dirZ, int randDirZMin, int randDirZMax,
	const char * szFile, D3DXCOLOR color)
{
	m_type = type;
	m_fTime = time;
	m_fSpeed = speed;
	m_fAcc = acc;
	m_fAccMin = accMin;
	m_fAccMax = accMax;
	m_fPositionX = posX;
	m_fRandPosXMin = randPosXMin;
	m_fRandPosXMax = randPosXMax;
	m_fPositionY = posY;
	m_fRandPosYMin = randPosYMin;
	m_fRandPosYMax = randPosYMax;
	m_fPositionZ = posZ;
	m_fRandPosZMin = randPosZMin;
	m_fRandPosZMax = randPosZMax;
	m_fDirectionX = dirX;
	m_fRandDirXMin = randDirXMin;
	m_fRandDirXMax = randDirXMax;
	m_fDirectionY = dirY;
	m_fRandDirYMin = randDirYMin;
	m_fRandDirYMax = randDirYMax;
	m_fDirectionZ = dirZ;
	m_fRandDirZMin = randDirZMin;
	m_fRandDirZMax = randDirZMax;

	//strcpy(m_szFile, szFile);
	m_stColor = color;

	m_pTexture = TEXTUREMANAGER->GetTexture(szFile);

	m_vecParticle.resize(1000);
	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		// 위치 방향 렌덤하게, 속도 가속도 타임 전달받은데로
		// 퉥스쳐 경로 받은데로, 칼라 또한 입력받은 걸루
		D3DXVECTOR3		pos(0, 0, 0);
		D3DXVECTOR3		dir(0, 0, 0);

		if (m_fAccMax - m_fAccMin > 0)
			m_fAcc = rand() % ((m_fAccMax - m_fAccMin + 1) + m_fAccMin) * 0.001f;

		if (m_fRandPosXMax - m_fRandPosXMin > 0)
			pos.x = rand() % (m_fRandPosXMax - m_fRandPosXMin + 1) + m_fRandPosXMin;
		else
			pos.x = m_fPositionX;

		if (m_fRandPosYMax - m_fRandPosYMin > 0)
			pos.y = rand() % (m_fRandPosYMax - m_fRandPosYMin + 1) + m_fRandPosYMin;
		else
			pos.y = m_fPositionY;

		if (m_fRandPosZMax - m_fRandPosZMin > 0)
			pos.z = rand() % (m_fRandPosZMax - m_fRandPosZMin + 1) + m_fRandPosZMin;
		else
			pos.z = m_fPositionZ;

		if (m_fRandDirXMax - m_fRandDirXMin > 0)
			dir.x = (rand() % (m_fRandDirXMax - m_fRandDirXMin + 1) + m_fRandDirXMin) * 0.01f;
		else
			dir.x = m_fDirectionX * 0.01f;

		if (m_fRandDirYMax - m_fRandDirYMin > 0)
			dir.y = (rand() % (m_fRandDirYMax - m_fRandDirYMin + 1) + m_fRandDirYMin) * 0.01f;
		else
			dir.y = m_fDirectionY * 0.01f;

		if (m_fRandDirZMax - m_fRandDirZMin > 0)
			dir.z = (rand() % (m_fRandDirZMax - m_fRandDirZMin + 1) + m_fRandDirZMin) * 0.01f;
		else
			dir.z = m_fDirectionZ * 0.01f;

		D3DXVec3Normalize(&dir, &dir);
		
		cParticle * newParticle = new cParticle;
		newParticle->Setup(m_fTime, pos, dir, m_fSpeed, m_fAcc, 0.0f, m_stColor, m_szFile);
		if (m_type == PTC_TYPE_LOOP)
			newParticle->SetIsUse(false);
		
		m_vecParticle[i] = newParticle;
	}

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(10.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDW(100.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	
	// 텍스처 알파 옵션 셋팅
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// 알파블랜딩 방식 결정
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void cParticleSet::Update()
{
	m_fCurTime += TIMEMANAGER->GetEllapsedTime();
	

	if (m_type == PTC_TYPE_LOOP)
	{
		for (int i = 0; i < m_vecParticle.size(); i++)
		{
			if (m_vecParticle[i]->GetIsUse() == false)
			{
				m_vecParticle[i]->Setup();
				break;
			}
		}
	}

	for (int i = 0; i < m_vecParticle.size(); i++)
		m_vecParticle[i]->Update(m_matWorld);
}

void cParticleSet::Render()
{
	//
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(10.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDW(100.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));

	// 텍스처 알파 옵션 셋팅
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 알파블랜딩 방식 결정
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for (int i = 0; i < m_vecParticle.size(); i++)
		m_vecParticle[i]->Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void cParticleSet::Start()
{
	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		if (m_vecParticle[i]->GetIsUse() == false)
		{
			m_vecParticle[i]->Setup();
		}
	}

}


// 나아가는 방향을
// 각도가 아닌 수치로 해야할 것 같다.
// -1.0 ~ 1.0  의 사이의 랜덤값이나 고정 값으로 정하고
// 그걸 노멀라이즈해서 넘겨줘야함
