#pragma once

#define PARTICLEMANAGER	cParticleManager::GetInstance()

class cParticleSet;

class cParticleManager
{
	SINGLETONE(cParticleManager);

private :

	map<string, cParticleSet*>	m_mapParticleSet;
public :

	void AddParticle(string key, const char * szFile);
	cParticleSet* GetParticle(string key);

	void Destroy();

};

