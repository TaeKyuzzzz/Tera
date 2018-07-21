#pragma once
#include "../cGameNode.h"

class cCamera;
class cGrid;

class cSceneTest;
class cSceneMain;

class cSceneLobbyLoading;
class cScenePaticleEdit;
class cSceneBossLoading;

class cMainGame : public cGameNode
{
private :
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;

	cSceneTest*				m_pSceneTest;
	
	cSceneMain*				m_pSceneMain;

	cSceneLobbyLoading*		m_pSceneLobbyLoading;
	cScenePaticleEdit*		m_pScenePaticleEdit;
	cSceneBossLoading*		m_pSceneBossLoading;

	LPDIRECT3DSURFACE9 surfcursor;
	LPDIRECT3DTEXTURE9 m_cursorArrow;
	LPDIRECT3DTEXTURE9 m_cursorEmpty;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void SetLight();
	void RemoteMode();
};

