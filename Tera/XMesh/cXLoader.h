#pragma once

class cXMesh;


class cXLoader
{
private :
	LPD3DXMESH				g_pMesh; // 메시 객체
	D3DMATERIAL9*			g_pMeshMaterials; // 메시의 재질
	LPDIRECT3DTEXTURE9*		g_pMeshTextures;// 메시의 텍스쳐
	DWORD					g_dwNumMaterials; // 재질의 수

public:
	cXLoader();
	virtual~cXLoader();

	cXMesh* xFimeLoad(const char* xFileName);

};

