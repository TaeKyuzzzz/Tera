#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
{
}


cCube::~cCube()
{
}

void cCube::Setup()
{
}

void cCube::Setup(D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	ST_PC_VERTEX v;
	D3DCOLOR color(0xff00ff00);

	v.c = color;

	v.p = D3DXVECTOR3(min.x, max.y, min.z); m_vecVertex.push_back(v);  // -1 1 -1
	v.p = D3DXVECTOR3(max.x, max.y, min.z); m_vecVertex.push_back(v);  // 1 1 -1
	v.p = D3DXVECTOR3(min.x, min.y, min.z); m_vecVertex.push_back(v); // -1 -1 -1

	v.p = D3DXVECTOR3(max.x, max.y, min.z); m_vecVertex.push_back(v);  // 1 1 -1
	v.p = D3DXVECTOR3(max.x, min.y, min.z); m_vecVertex.push_back(v);   // 1 -1 -1
	v.p = D3DXVECTOR3(min.x, min.y, min.z); m_vecVertex.push_back(v);  // -1 1 -1

	v.p = D3DXVECTOR3(max.x, max.y, max.z); m_vecVertex.push_back(v);  // 1 1 1
	v.p = D3DXVECTOR3(min.x, max.y, max.z); m_vecVertex.push_back(v);  // -1 1 1
	v.p = D3DXVECTOR3(max.x, min.y, max.z); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(min.x, max.y, max.z); m_vecVertex.push_back(v);  // -1 1 1
	v.p = D3DXVECTOR3(min.x, min.y, max.z); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, max.z); m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(max.x, max.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, min.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(max.x, max.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, max.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(min.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, min.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, min.y, max.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(min.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, max.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, min.y, min.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(min.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, max.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, max.y, min.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(min.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, max.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, max.y, min.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(max.x, min.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, min.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, min.z);  m_vecVertex.push_back(v);
										    
										    
	v.p = D3DXVECTOR3(min.x, min.y, max.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(min.x, min.y, min.z);  m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(max.x, min.y, min.z);  m_vecVertex.push_back(v);

}

void cCube::Update()
{
}

void cCube::Render()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
