#include "stdafx.h"
#include "cParticleManager.h"

#include "Particle\cParticleSet.h"

cParticleManager::cParticleManager()
{
}


cParticleManager::~cParticleManager()
{
}

void cParticleManager::AddParticle(string key, const char * szFile)
{
	
		PARTICLE_TYPE _type; float _fTime;
		float _fSpeed;

		float _fAcc;		int	_nAccMin;		int	_nAccMax;

		int	_nPositionX;	int	_nRandPosXMin;	int	_nRandPosXMax;
		int	_nPositionY;	int	_nRandPosYMin;	int	_nRandPosYMax;
		int	_nPositionZ;	int	_nRandPosZMin;	int	_nRandPosZMax;
		int	_nDirectionX;	int	_nRandDirXMin;	int	_nRandDirXMax;

		int	_nDirectionY;	int	_nRandDirYMin;	int	_nRandDirYMax;

		int	_nDirectionZ;	int	_nRandDirZMin;	int	_nRandDirZMax;

		char _szFile[1024];

		int	_nAlpha;	int	_nColorR;	int	_nColorG;	int	_nColorB;
	
	
	cParticleSet * newParticleSet = new cParticleSet;
	
	FILE* fp;
	fopen_s(&fp, szFile, "r");

	char s[1024];

	fgets(s, 1024, fp);		_fTime = atof(s);
	fgets(s, 1024, fp);		_type = (PARTICLE_TYPE)atoi(s);
	fgets(s, 1024, fp);		_fSpeed = atof(s);

	fgets(s, 1024, fp);		_fAcc = atof(s);
	fgets(s, 1024, fp);		_nAccMin = atoi(s);
	fgets(s, 1024, fp);		_nAccMax = atoi(s);

	fgets(s, 1024, fp);		_nPositionX = atoi(s);
	fgets(s, 1024, fp);		_nRandPosXMin = atoi(s);
	fgets(s, 1024, fp);		_nRandPosXMax = atoi(s);
							 
	fgets(s, 1024, fp);		_nPositionY = atoi(s);
	fgets(s, 1024, fp);		_nRandPosYMin = atoi(s);
	fgets(s, 1024, fp);		_nRandPosYMax = atoi(s);
							 
	fgets(s, 1024, fp);		_nPositionZ = atoi(s);
	fgets(s, 1024, fp);		_nRandPosZMin = atoi(s);
	fgets(s, 1024, fp);		_nRandPosZMax = atoi(s);
							 
	fgets(s, 1024, fp);		_nDirectionX = atoi(s);
	fgets(s, 1024, fp);		_nRandDirXMin = atoi(s);
	fgets(s, 1024, fp);		_nRandDirXMax = atoi(s);
							 
	fgets(s, 1024, fp);		_nDirectionY = atoi(s);
	fgets(s, 1024, fp);		_nRandDirYMin = atoi(s);
	fgets(s, 1024, fp);		_nRandDirYMax = atoi(s);
							 
	fgets(s, 1024, fp);		_nDirectionZ = atoi(s);
	fgets(s, 1024, fp);		_nRandDirZMin = atoi(s);
	fgets(s, 1024, fp);		_nRandDirZMax = atoi(s);

	fgets(s, 1024, fp);		_nAlpha = atoi(s);
	fgets(s, 1024, fp);		_nColorR = atoi(s);
	fgets(s, 1024, fp);		_nColorG = atoi(s);
	fgets(s, 1024, fp);		_nColorB = atoi(s);

	fgets(s, 1024, fp);		strcpy(_szFile, s);

	fclose(fp);

	newParticleSet->Setup(
		_type,
		_fTime, _fSpeed,
		_fAcc, _nAccMin, _nAccMax,
		_nPositionX,  _nRandPosXMin, _nRandPosXMax,
		_nPositionY,  _nRandPosYMin, _nRandPosYMax,
		_nPositionZ,  _nRandPosZMin, _nRandPosZMax,
		_nDirectionX, _nRandDirXMin, _nRandDirXMax,
		_nDirectionY, _nRandDirYMin, _nRandDirYMax,
		_nDirectionZ, _nRandDirZMin, _nRandDirZMax,
		_szFile, D3DCOLOR_ARGB(_nAlpha, _nColorR, _nColorG, _nColorB));

	m_mapParticleSet[key] = newParticleSet;
}

cParticleSet * cParticleManager::GetParticle(string key)
{
	if (m_mapParticleSet.find(key) == m_mapParticleSet.end())
		return NULL;

	return m_mapParticleSet[key];
}

void cParticleManager::AddChild(cParticleSet * child)
{
	m_vecParticle.push_back(child);
}

void cParticleManager::Destroy()
{
	for (auto p : m_mapParticleSet)
	{
		if (p.second)
			SAFE_DELETE(p.second);
	}
	m_mapParticleSet.clear();

	//for (auto p : m_vecParticle)
	//{
	//	SAFE_DELETE(p);
	//}
}

void cParticleManager::Update()
{
	for (int i = 0; i < m_vecParticle.size(); i++)
		m_vecParticle[i]->Update();
}

void cParticleManager::Render()
{
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


	//
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	for (int i = 0; i < m_vecParticle.size(); i++)
		m_vecParticle[i]->RenderOnce();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
