#include "stdafx.h"
#include "cBossRoom_Road.h"

#include "XMesh/cXLoader.h"
#include "XMesh/cXMesh.h"


cBossRoom_Road::cBossRoom_Road()
	: pos(0, 0, 0)
{
	D3DXMatrixIdentity(&matWorld);
}


cBossRoom_Road::~cBossRoom_Road()
{
}

void cBossRoom_Road::Setup()
{
	const int size = 2;

	char fileName[size][256] = {
		"XFile/Boss_Room/ARG_Cor02_A_02_Floor_SM_1.X",
		"XFile/Boss_Room/ARG_Cor02_A_02_Floor_SM_2.X"
	};

	for (int i = 0; i < size; i++)
	{
		cXLoader  ground_meshX;
		m_vecBossRoomParts.push_back(ground_meshX.xFimeLoad(fileName[i]));
	}


	pos = D3DXVECTOR3(-1600.f, 0, 0);

	D3DXMATRIX matPos, world;
	D3DXMatrixIdentity(&matPos);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);
	world = matPos;
	matWorld = world;

	m_vecBossRoomRoad.push_back(*this);

}

void cBossRoom_Road::Render()
{
	if (!m_vecBossRoomParts.empty())
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for (auto p : m_vecBossRoomParts)
		{
			p->Render();
		}
	}
}

void cBossRoom_Road::Destroy()
{
	if (!m_vecBossRoomParts.empty())
	{
		for (auto p : m_vecBossRoomParts)
		{
			SAFE_DELETE(p);
		}
		delete this;

	}
}
