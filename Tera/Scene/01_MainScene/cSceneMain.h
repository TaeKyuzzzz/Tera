#pragma once
#include "../../cGameNode.h"

class cSprite;
class cProgressBar;

class cSceneMain : public cGameNode
{
private :

	cSprite*			m_pBackGround;
	cSprite*			m_pBackGroundBlack;
	cSprite*			m_pBackGroundWhite;

	cProgressBar*		m_pLoadingBar;
	int					m_nBGBlackAlpha;
	bool				m_isStart;


	RECT rc[5];

	D3DCOLOR			m_colorOver;
	D3DCOLOR			m_colorDefault;

	string				m_sNextScene;
public:
	cSceneMain();
	virtual~cSceneMain();

	void Setup();
	void Release();
	void Update();
	void Render();
};

