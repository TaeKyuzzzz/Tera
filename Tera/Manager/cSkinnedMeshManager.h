#pragma once

#define SKINNEDMESHMANAGER cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;
class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*>	m_mapSkinnedMesh;

private:
	SINGLETONE(cSkinnedMeshManager);


public:
	cSkinnedMesh * GetSkinnedMesh(const char* szFolder, const char* szFileName);
	cSkinnedMesh * GetSkinnedMesh(const char * szFullPath);

	void AddSkinnedMesh(const char * szFolder, const char* szFileName);

	void Destroy();
};

