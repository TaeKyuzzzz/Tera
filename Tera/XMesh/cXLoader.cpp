#include "stdafx.h"
#include "cXLoader.h"
#include "cXMesh.h"

cXLoader::cXLoader()
{
}


cXLoader::~cXLoader()
{
}

cXMesh * cXLoader::xFimeLoad(const char * xFileName)
{
	wchar_t wtext[1024];
	size_t outSize;
	mbstowcs_s(&outSize, wtext, strlen(xFileName) + 1, xFileName, strlen(xFileName));

	LPD3DXBUFFER pD3DXMtrBuffer;

	// x ������ �ҷ����� �κ�
	D3DXLoadMeshFromX(wtext, D3DXMESH_SYSTEMMEM,
		g_pD3DDevice, NULL, &pD3DXMtrBuffer, NULL, &g_dwNumMaterials, &g_pMesh);

	// �ؽ��� ������ �ٸ� ������ ���� ��� �ؽ��� �н� ��ġ �ݱ�?
	char texturePath[256];
	// ���� �������

	char temp[256];
	char* pChar;
	strcpy_s(temp, 256, xFileName);
	_strrev(temp);
	pChar = strchr(temp, '/');
	strcpy_s(texturePath, 256, pChar);
	_strrev(texturePath);

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	for (size_t i = 0; i < g_dwNumMaterials; i++)
	{
		// ���� ����
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// ������ ���� �����Ʈ ���� ���� (d3dx�� �ϵ����� �����شٰ� �Ѵ�)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;

		// ���⼭ �ؽ��� ������ �����Ѵٸ�!!
		if (d3dxMaterials[i].pTextureFilename > 0)
		{
			// ���, �ؽ��� �̸��� ���� �ؽ��ĸ� �־������
			char tempFile[256];
			sprintf_s(tempFile, "%s%s", texturePath, d3dxMaterials[i].pTextureFilename, 256);
			g_pMeshTextures[i] = TEXTUREMANAGER->GetTexture(tempFile);
		}
	}
	// ���� ���� ��� ��, ����
	pD3DXMtrBuffer->Release();

	cXMesh* newGroup = new cXMesh;
	newGroup->SetMesh(g_pMesh);
	newGroup->SetMaterials(g_pMeshMaterials);
	newGroup->SetTexture(g_pMeshTextures);
	newGroup->SetNumMaterial(g_dwNumMaterials);

	return newGroup;
}
