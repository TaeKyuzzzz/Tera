#include "stdafx.h"
#include "cTestMap.h"
#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"

cTestMap::cTestMap()
	: m_pGround(NULL)
	, m_pVertex(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXVECTOR3 pos(15000, 0, -1500);
	D3DXMatrixTranslation(&m_matWorld, pos.x, pos.y, pos.z);

}


cTestMap::~cTestMap()
{
	//SAFE_DELETE(m_pGround);
}

void cTestMap::Setup()
{
	m_pGround = STATICMESHMANAGER->GetStaticMesh(
		"XFile/Map/Field/ANC_B_4858_SL(Ori).X");
	//"XFile/Item/Weapon/TwoHandSword_00.X"
	//"XFile/Map/Field/ANC_B_4858_SL.X"
	numOfVertex = m_pGround->GetMesh()->GetNumVertices();

	numOfIndex = m_pGround->GetMesh()->GetNumFaces() * 3;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPDIRECT3DINDEXBUFFER9	pIB;

	m_pGround->GetMesh()->GetVertexBuffer(&pVB);

	void* pIndex;
	m_pGround->GetMesh()->GetIndexBuffer(&pIB);	
	pIB->Lock(0, sizeof(WORD) * numOfIndex, (void**)&pIndex, 0);

	m_pIndex = (WORD*)pIndex;

	pIB->Unlock();
	pIB->Release();
	

	void* pVertices;
	pVB->Lock(0, sizeof(ST_PNT_VERTEX) * numOfVertex, (void**)&pVertices, 0);
	m_pVertex = (ST_PNT_VERTEX*)pVertices;
	
	for (int i = 0; i < numOfIndex; i += 3)
	{
		// 법선벡터를 만들어야해..
		D3DXVECTOR3 v0, v1, v2, u, v;
		v0 = m_pVertex[m_pIndex[i + 0]].p;
		v1 = m_pVertex[m_pIndex[i + 1]].p;
		v2 = m_pVertex[m_pIndex[i + 2]].p;
		
		u = v1 - v0;
		v = v2 - v0;
		D3DXVECTOR3 faceNormal;
		D3DXVec3Cross(&faceNormal,&u, &v);
		
		m_pVertex[m_pIndex[i + 0]].n = m_pVertex[m_pIndex[i + 0]].n + faceNormal;
		D3DXVec3Normalize(&m_pVertex[m_pIndex[i + 0]].n, &m_pVertex[m_pIndex[i + 0]].n);
		
		m_pVertex[m_pIndex[i + 1]].n = m_pVertex[m_pIndex[i + 1]].n + faceNormal;
		D3DXVec3Normalize(&m_pVertex[m_pIndex[i + 1]].n, &m_pVertex[m_pIndex[i + 1]].n);
		
		m_pVertex[m_pIndex[i + 2]].n = m_pVertex[m_pIndex[i + 2]].n + faceNormal;
		D3DXVec3Normalize(&m_pVertex[m_pIndex[i + 2]].n, &m_pVertex[m_pIndex[i + 2]].n);
	}

	for (DWORD i = 0; i < numOfVertex; i++)
	{
		D3DXVec3TransformCoord(&m_pVertex[i].p, &m_pVertex[i].p, &m_matWorld);
		D3DXVec3TransformNormal(&m_pVertex[i].n, &m_pVertex[i].n, &m_matWorld);
	}

	pVB->Unlock();
	pVB->Release();

	
	D3DXMatrixIdentity(&m_matWorld);

}

void cTestMap::Update()
{
}

void cTestMap::Render()
{
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//m_pGround->Render();
}

bool cTestMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, 1000.0f, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (int i = 0; i <numOfIndex; i += 3)
	{
		float u, v, f;
		if (D3DXIntersectTri(&m_pVertex[m_pIndex[i + 0]].p,
			&m_pVertex[m_pIndex[i + 1]].p,
			&m_pVertex[m_pIndex[i + 2]].p,
			&vRayPos,
			&vRayDir,
			&u, &v, &f))
		{
			y = 1000.0f - f;
			return true;
		}
	}
	
	return false;
}
