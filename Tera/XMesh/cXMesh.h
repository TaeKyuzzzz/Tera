#pragma once
class cXMesh
{
private :
	SYNTHESIZE_REF(LPD3DXMESH, g_pMesh, Mesh);
	SYNTHESIZE_REF(D3DMATERIAL9*, g_pMeshMaterials, Materials);
	SYNTHESIZE_REF(LPDIRECT3DTEXTURE9*, g_pMeshTextures, Texture);
	SYNTHESIZE_REF(DWORD, g_dwNumMaterials, NumMaterial);

public:
	cXMesh();
	~cXMesh();

	void Render();
};

