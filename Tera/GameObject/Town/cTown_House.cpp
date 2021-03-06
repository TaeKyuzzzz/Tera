#include "stdafx.h"
#include "GameObject/Town/cTown_House.h"
#include "Spere/cSpere.h"
#include "BoundingBox/cBoundingBox.h"

#include "XMesh/cXLoader.h"
#include "XMesh/cXMesh.h"

#include "Particle\cParticleSet.h"


cTown_House::cTown_House()
{
}

cTown_House::~cTown_House()
{
}

void cTown_House::Setup()
{
	const int size = 6;

	char fileName[size][256] = {
		"XFile/Map/Field/ANC_B_4858_SL.X",
		"XFile/Map/Field/Skydom2048_1024.X",
		"XFile/Town/House01.X",
		"XFile/Town/House02.X",
		"XFile/Town/House03.X",
		"XFile/Town/WarpGate.X"

	};

	for (int i = 0; i < size; i++)
	{
		cXLoader  ground_meshX;
		m_vTownHouse.push_back(ground_meshX.xFimeLoad(fileName[i]));
	}

	// 파티클 설치
	m_pParticleWarp = PARTICLEMANAGER->GetParticle("PortalEffect");
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 969, -406, 4157);
	m_pParticleWarp->SetWorld(mat);
	m_pParticleWarp->Start();

	PARTICLEMANAGER->AddChild(m_pParticleWarp);
}

void cTown_House::Update()
{
	//m_pParticleWarp->Update();
}

void cTown_House::Render()
{
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX matWorld, matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);  // 1/256 = 0.00390625
												 //D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (!m_vTownHouse.empty())
	{
		for (auto p : m_vTownHouse)
		{
			p->Render();
		}
	}
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	//m_pParticleWarp->Render();

}

void cTown_House::Destroy()
{
	for (auto a : m_vTownHouse)
	{
		SAFE_DELETE(a);
	}
	delete this;
}



