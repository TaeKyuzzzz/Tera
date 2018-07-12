#pragma once

#define STATICMESHMANAGER cStaticMeshManager::GetInstance()

class cXMesh;

class cStaticMeshManager
{
private:
	std::map<std::string, cXMesh*>	m_mapStaticMesh;

private:
	SINGLETONE(cStaticMeshManager);


public:
	void AddStaticMesh(const char * szFullPath);
	cXMesh * GetStaticMesh(const char * szFullPath);
	void Destroy();
};

