#include "stdafx.h"
#include "Scene\06_PaticleEdit\cScenePaticleEdit.h"

#include "Particle\cParticleSet.h"
#include "Sprite\cSprite.h"

cScenePaticleEdit::cScenePaticleEdit()
{
}


cScenePaticleEdit::~cScenePaticleEdit()
{
	SAFE_DELETE(m_pParticleSet);
	//SAFE_DELETE(m_pSprite);
}

void cScenePaticleEdit::Setup()
{
	//m_pSprite = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");
	
	m_pParticleSet = new cParticleSet;
	
	
	//m_pParticleSet->Setup(
	//1.0f,1.0f,
	//	-0.001f,0,0,
	//	0,-10,10,
	//	0,0,0,
	//	0,-20,20,
	//	0,-30,30,
	//	100,0,0,
	//	0,-30,30,
	//	"Texture/Particle/fire_01.png"
	//	,D3DCOLOR_ARGB(50,255,0,0));

	m_pParticleSet->Setup(
		0.5f, 1.0f, 
		-0.001f,0,0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, -100, 100,
		0, -100, 100,
		0, -100, 100,
		"Texture/Particle/fire_01.png"
		, D3DCOLOR_ARGB(100, 0, 255, 0));
}

void cScenePaticleEdit::Update()
{
	m_pParticleSet->Update();
}

void cScenePaticleEdit::Render()
{
	//m_pSprite->Render(D3DXVECTOR3(m_pSprite->textureInfo.Width / 2, 0, 0), D3DXVECTOR3(WINSIZEX / 2, 0, 0));
	m_pParticleSet->Render();
}

void cScenePaticleEdit::LoadTexture()
{
}
