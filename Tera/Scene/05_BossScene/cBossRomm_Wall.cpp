#include "stdafx.h"
#include "cBossRomm_Wall.h"

#include "XMesh/cXLoader.h"
#include "XMesh/cXMesh.h"


cBossRomm_Wall::cBossRomm_Wall()
	: rotY(D3DX_PI / 4)
{
	D3DXMatrixIdentity(&matWorld);
}


cBossRomm_Wall::~cBossRomm_Wall()
{
}

void cBossRomm_Wall::Setup()
{
	const int size = 5;

	char fileName[size][256] = {
		"XFile/Boss_Room/ARG_Room_A_SM_P5.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P1.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P2.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P3.X",
		"XFile/Boss_Room/ARG_Room_A_SM_P4.X"
	};

	for (int i = 0; i < size; i++)
	{
		cXLoader  ground_meshX;
		m_vecBossRoom.push_back(ground_meshX.xFimeLoad(fileName[i]));
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
			m_vecBossRoom.clear();
			cXLoader  ground_meshX;
			char name[] = "XFile/Boss_Room/ARG_Room_A_SM_P4.X";
			m_vecBossRoom.push_back(ground_meshX.xFimeLoad(name));
		}

		m_vecBossRoomWall.push_back(*this);
	}
}

void cBossRomm_Wall::Render()
{
	if (!m_vecBossRoom.empty())
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for (auto p : m_vecBossRoom)
		{
			p->Render();
		}
	}
}

void cBossRomm_Wall::Destroy()
{
	if (!m_vecBossRoom.empty())
	{
		for (auto p : m_vecBossRoom)
		{
			SAFE_DELETE(p);
		}
		delete this;
		
	}
}
