#include "stdafx.h"
#include "cBossRoom_Wall.h"

#include "XMesh/cXLoader.h"
#include "XMesh/cXMesh.h"


cBossRoom_Wall::cBossRoom_Wall()
	: rotY(D3DX_PI / 4)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._42 = -48;
}


cBossRoom_Wall::~cBossRoom_Wall()
{
}

void cBossRoom_Wall::Setup()
{
	//D3DXMatrixIdentity(&m_matWorld);

	m_pFloor = STATICMESHMANAGER->GetStaticMesh("XFile/Boss_Room/Bottom_ray.X");

	const int size = 5;

	char fileName[size][256] = {
		"XFile/Boss_Room/ARG_Room_A_SM_P4.X", //�ٴ�
		"XFile/Boss_Room/ARG_Room_A_SM_P5.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P1.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P2.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P3.X"
	};

	for (int i = 0; i < size; i++)
	{
		//cXLoader  ground_meshX;
		m_vecWallParts.push_back(STATICMESHMANAGER->GetStaticMesh(fileName[i]));
	}

	for (int i = 0; i < 8; i++)
	{
		rotY += D3DX_PI / 4;

		D3DXMATRIX matRotY, world;
		D3DXMatrixRotationY(&matRotY, rotY);
		world = matRotY;
		matWorld = world;

		// �� ������ ������ �Ա��� ��ġ�Ƿ�, �ٴڸ� �׷��ش�.
		if (i == 7)
		{
			m_vecWallParts.clear();
			cXLoader  ground_meshX;
			char name[] = "XFile/Boss_Room/ARG_Room_A_SM_P4.X";
			m_vecWallParts.push_back(ground_meshX.xFimeLoad(name));
		}

		m_vecBossRoom_Wall.push_back(*this);
	}

	// ���� ���� ���� ���� ��������

	//cXMesh * floor = m_vecWallParts[0];
	//m_pFloor = m_vecBossRoom_Wall[0].m_vecWallParts[0];
	
	numOfVertex = m_pFloor->GetMesh()->GetNumVertices();

	numOfIndex = m_pFloor->GetMesh()->GetNumFaces() * 3;

	LPDIRECT3DVERTEXBUFFER9 pVB;

	m_pFloor->GetMesh()->GetVertexBuffer(&pVB);

	LPDIRECT3DINDEXBUFFER9	pIB;
	void* pIndex;
	m_pFloor->GetMesh()->GetIndexBuffer(&pIB);
	pIB->Lock(0, sizeof(WORD) * numOfIndex, (void**)&pIndex, 0);

	m_pIndex = (WORD*)pIndex;

	pIB->Unlock();
	pIB->Release();


	void* pVertices;
	pVB->Lock(0, sizeof(ST_PNT_VERTEX) * numOfVertex, (void**)&pVertices, 0);
	m_pVertex = (ST_PNT_VERTEX*)pVertices;

	//for (DWORD i = 0; i < numOfVertex; i++)
	//	D3DXVec3TransformCoord(&m_pVertex[i].p, &m_pVertex[i].p, &m_matWorld);


	pVB->Unlock();
	pVB->Release();

	//D3DXMatrixIdentity(&m_matWorld);
}

void cBossRoom_Wall::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (!m_vecWallParts.empty())
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
		for (auto p : m_vecWallParts)
		{
			p->Render();
		}
	}
}

void cBossRoom_Wall::Destroy()
{
	if (!m_vecWallParts.empty())
	{
		for (auto p : m_vecWallParts)
		{
			SAFE_DELETE(p);
		}
		delete this;
		
	}
}

bool cBossRoom_Wall::GetHeight(IN float x, OUT float & y, IN float z)
{
	float	rayHeight = 1000.0f;
	D3DXVECTOR3 vRayPos(x, rayHeight, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	D3DXVECTOR3 v0,v1, v2;
	for (int i = 0; i <numOfIndex; i += 3)
	{
		float u, v, f;

		D3DXVec3TransformCoord(&v0, &m_pVertex[m_pIndex[i + 0]].p, &m_matWorld);
		D3DXVec3TransformCoord(&v1, &m_pVertex[m_pIndex[i + 1]].p,&m_matWorld);
		D3DXVec3TransformCoord(&v2, &m_pVertex[m_pIndex[i + 2]].p, &m_matWorld);

		if (D3DXIntersectTri(&v0,
			&v1,
			&v2,
			&vRayPos,
			&vRayDir,
			&u, &v, &f))
		{
			y = rayHeight - f;
			return true;
		}
	}
	return false;

}
