#include "stdafx.h"
#include "cSceneBossLoading.h"

#include "Scene\05_BossScene\cBossRoom_Wall.h"
#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"


cSceneBossLoading::cSceneBossLoading()
{
}


cSceneBossLoading::~cSceneBossLoading()
{
	SAFE_DELETE(m_pBossRoomWall);
	this->Destroy();
}

void cSceneBossLoading::Setup()
{
	Roader_WallGate();

	m_pBossRoomWall = new cBossRoom_Wall;
	m_pBossRoomWall->Setup();
}

void cSceneBossLoading::Update()
{
}

void cSceneBossLoading::Render()
{
	Render_Wall();
}

void cSceneBossLoading::Render_Wall()
{
	if (!m_vGroundMap.empty())
	{
		for (auto p : m_vGroundMap)
		{
			p->Render();
		}
	}

	for (auto p : m_pBossRoomWall->m_vecBossRoomWall)
	{
		for (auto p : m_pBossRoomWall->m_vecBossRoomWall)
		{
			p.Render();
		}
	}
}

void cSceneBossLoading::Roader_WallGate()
{
	const int size = 4;

	char fileName[size][256] = {
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P1.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P2.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P3.X",
		"XFile/Boss_Room/ARG_Room_A_Enter_SM_P4.X"
		//"XFile\Boss_Room\ARG_Room_A_Enter_SM_P5.X",
	};

	for (int i = 0; i < size; i++)
	{
		cXLoader  ground_meshX;
		m_vGroundMap.push_back(ground_meshX.xFimeLoad(fileName[i]));
	}
}

void cSceneBossLoading::Destroy()
{
	if (!m_vGroundMap.empty())
	{
		for (auto p : m_vGroundMap)
		{
			SAFE_DELETE(p);
		}
		delete this;
	}

	for (auto p : m_pBossRoomWall->m_vecBossRoomWall)
	{
		for (auto p : m_pBossRoomWall->m_vecBossRoomWall)
		{
			p.Destroy();
		}
	}


}
