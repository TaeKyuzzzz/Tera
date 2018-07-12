#pragma once

class cXMesh;


class cXLoader
{
private :
	LPD3DXMESH				g_pMesh; // �޽� ��ü
	D3DMATERIAL9*			g_pMeshMaterials; // �޽��� ����
	LPDIRECT3DTEXTURE9*		g_pMeshTextures;// �޽��� �ؽ���
	DWORD					g_dwNumMaterials; // ������ ��

public:
	cXLoader();
	virtual~cXLoader();

	cXMesh* xFimeLoad(const char* xFileName);

};

