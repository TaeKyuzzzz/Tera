#include "stdafx.h"
#include "cXMesh.h"


cXMesh::cXMesh()
{
}


cXMesh::~cXMesh()
{
	SAFE_RELEASE(g_pMesh);
	SAFE_DELETE(g_pMeshMaterials);
	SAFE_DELETE(g_pMeshTextures);
}

void cXMesh::Render()
{
	for (size_t i = 0; i < g_dwNumMaterials; i++)
	{
		g_pD3DDevice->SetMaterial(&g_pMeshMaterials[i]);
		// 현재 sub Set에 대한 재질 설정
		g_pD3DDevice->SetTexture(0, g_pMeshTextures[i]);
		// 그리자
		g_pMesh->DrawSubset(i);
	}
	g_pD3DDevice->SetTexture(0, NULL);
}
