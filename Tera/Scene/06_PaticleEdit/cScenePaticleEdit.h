#pragma once
#include "cGameNode.h"

class cParticleSet;

class cSprite;

class cScenePaticleEdit : public cGameNode
{
private :

	cSprite*					m_pSprite;

	LPDIRECT3DTEXTURE9			m_pTexture;

	cParticleSet*				m_pParticleSet;
public:
	cScenePaticleEdit();
	~cScenePaticleEdit();

	void Setup();
	void Update();
	void Render();

	void LoadTexture();

};

