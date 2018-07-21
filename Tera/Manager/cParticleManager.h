#pragma once

#define PARTICLEMANAGER	cParticleManager::GetInstance()

class cParticleSet;

class cParticleManager
{
	SINGLETONE(cParticleManager);

private :

	map<string, cParticleSet*>	m_mapParticleSet;

	vector<cParticleSet*>		m_vecParticle;
public :

	void AddParticle(string key, const char * szFile);
	cParticleSet* GetParticle(string key);

	void AddChild(cParticleSet* child);

	void Destroy();

	void Update();
	void Render();

};

