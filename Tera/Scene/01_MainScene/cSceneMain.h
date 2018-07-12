#pragma once
#include "../../cGameNode.h"

class cSprite;
class cProgressBar;

class cSceneMain : public cGameNode
{
private :

	cSprite*			m_pBackGround;
	cSprite*			m_pBackGroundBlack;
	cProgressBar*		m_pLoadingBar;
	int					m_nBGBlackAlpha;
	bool				m_isStart;
public:
	cSceneMain();
	virtual~cSceneMain();

	void Setup();
	void Update();
	void Render();
};

