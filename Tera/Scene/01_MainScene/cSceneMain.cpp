#include "stdafx.h"
#include "cSceneMain.h"

#include "Sprite\cSprite.h"
#include "ProgressBar\cProgressBar.h"

cSceneMain::cSceneMain()
	: m_pBackGround(NULL)
	, m_pBackGroundBlack(NULL)
	, m_pLoadingBar(NULL)
	, m_nBGBlackAlpha(255)
	, m_isStart(false)
{
}


cSceneMain::~cSceneMain()
{
	SAFE_DELETE(m_pBackGround);
	SAFE_DELETE(m_pBackGroundBlack);
	//SAFE_DELETE(m_pLoadingBar);
	//TEXTUREMANAGER->Destroy();
}
//"Textrue/SceneTexture/LoadingBar.png"
//"Textrue/SceneTexture/BGLoadingBar.png"

void cSceneMain::Setup()
{
	m_pBackGround = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/LoadingImage.png");
	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");

	//m_pLoadingBar = new cProgressBar;
	//m_pLoadingBar->Setup("Texture/SceneTexture/LoadingBar.png", 
	//	"Texture/SceneTexture/BGLoadingBar.png",
	//	100,100,1200,28
	//	);
}

void cSceneMain::Update()
{
	if (m_isStart == false && m_nBGBlackAlpha > 0)
		m_nBGBlackAlpha -= 5;


	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		m_isStart = true;

	if (m_isStart)
	{
		m_nBGBlackAlpha += 5;

		if (m_nBGBlackAlpha > 255)
		{
			//TEXTUREMANAGER->Destroy();
			SCENEMANAGER->ChangeScene("LobbyLoading");
			//SCENEMANAGER->ChangeScene("TEST");
		}
	}
}

void cSceneMain::Render()
{
	m_pBackGround->Render(D3DXVECTOR3(m_pBackGround->textureInfo.Width/2, 0, 0),D3DXVECTOR3(WINSIZEX / 2, 0, 0));	
	m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(m_pBackGround->textureInfo.Width / 2, 0, 0), D3DXVECTOR3(WINSIZEX / 2, 0, 0), m_nBGBlackAlpha);

	//m_pLoadingBar->Render();
}
