#pragma once
#include "../cGameNode.h"

class cCamera;
class cGrid;

class cSceneTest;
class cSceneMain;

class cSceneMapEdit; //lsc

class cMainGame : public cGameNode
{
private :
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;

	LPDIRECT3DSURFACE9 surfcursor;
	LPDIRECT3DTEXTURE9 m_cursorArrow;
	LPDIRECT3DTEXTURE9 m_cursorEmpty;

	cSceneMapEdit* m_pSceneMapEdit; //lsc

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void SetLight();
	void RemoteMode();
};

