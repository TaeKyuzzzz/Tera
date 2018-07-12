#include "stdafx.h"
#include "cStaticMeshManager.h"
#include "XMesh/cXMesh.h"
#include "XMesh/cXLoader.h"

cStaticMeshManager::cStaticMeshManager()
{
}


cStaticMeshManager::~cStaticMeshManager()
{
}

void cStaticMeshManager::AddStaticMesh(const char * szFullPath)
{
	wchar_t wtext[1024];
	size_t outSize;
	mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));

	cXLoader loader;
	cXMesh* pStaticMesh;
	pStaticMesh = loader.xFimeLoad(szFullPath);

	m_mapStaticMesh[szFullPath] = pStaticMesh;
}

cXMesh * cStaticMeshManager::GetStaticMesh(const char * szFullPath)
{

	if (m_mapStaticMesh.find(szFullPath) == m_mapStaticMesh.end())
	{
		wchar_t wtext[1024];
		size_t outSize;
		mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));

		cXLoader loader;
		cXMesh* pStaticMesh;
		pStaticMesh = loader.xFimeLoad(szFullPath);
	
		m_mapStaticMesh[szFullPath] = pStaticMesh;
	}

	return m_mapStaticMesh[szFullPath];
}

void cStaticMeshManager::Destroy()
{
	for (auto p : m_mapStaticMesh)
	{
		//p.second->Destroy();
		SAFE_DELETE(p.second);
	}
}
