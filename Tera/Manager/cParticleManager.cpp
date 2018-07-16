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

void cParticleManager::Destroy()
{
	for (auto p : m_mapParticleSet)
	{
		if (p.second)
			SAFE_DELETE(p.second);
	}
	m_mapParticleSet.clear();
}
