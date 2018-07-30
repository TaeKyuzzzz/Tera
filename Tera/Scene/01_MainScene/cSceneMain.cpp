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
	m_colorOver = D3DCOLOR_ARGB(255, 255, 255, 0);
	m_colorDefault = D3DCOLOR_ARGB(255, 0, 0, 0);
}


cSceneMain::~cSceneMain()
{
	SAFE_DELETE(m_pBackGround);
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pBackGroundWhite);
}

void cSceneMain::Setup()
{
	m_pBackGround = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/Loadingimage2.png"); // Loadingimage2 LoadingImage
	m_pBackGroundBlack = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");
	m_pBackGroundWhite = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGWhite.png");

	rc[0] = RectMakeCenter(WINSIZEX / 2, (float)WINSIZEY / 2.0f,	   400, 50);
	rc[1] = RectMakeCenter(WINSIZEX / 2, (float)WINSIZEY / 2.0f + 100, 400, 50);
	rc[2] = RectMakeCenter(WINSIZEX / 2, (float)WINSIZEY / 2.0f + 200, 400, 50);
	rc[3] = RectMakeCenter(WINSIZEX / 2, (float)WINSIZEY / 2.0f + 300, 400, 50);
	rc[4] = RectMakeCenter(WINSIZEX / 2, (float)WINSIZEY / 2.0f - 200, 400, 400);

	m_nBGBlackAlpha = 255;
	m_isStart = false;
	m_colorOver = D3DCOLOR_ARGB(255, 255, 255, 0);
	m_colorDefault = D3DCOLOR_ARGB(255, 0, 0, 0);

	// 메인 씬 사운드 등록
	SOUNDMANAGER->AddSound("Main", "Sound/Main/ServerTheme.ogg", true,true);
	SOUNDMANAGER->Play("Main");

}

void cSceneMain::Release()
{
	SAFE_DELETE(m_pBackGround);
	SAFE_DELETE(m_pBackGroundBlack);
	SAFE_DELETE(m_pBackGroundWhite);
	//TEXTUREMANAGER->Destroy();
}

void cSceneMain::Update()
{
	if (m_isStart == false && m_nBGBlackAlpha > 0)
		m_nBGBlackAlpha -= 5;


	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&rc[0], ptMouse))
			{
				m_isStart = true;
				m_sNextScene = "LobbyLoading";
			}
			else if (PtInRect(&rc[1], ptMouse))
			{
				m_isStart = true;
				m_sNextScene = "PaticleEdit";
			}
			else if (PtInRect(&rc[2], ptMouse))
			{

			}
			else if (PtInRect(&rc[3], ptMouse))
			{
				DestroyWindow(g_hWnd);
			}
		}
	
		
	}
	if (m_isStart)
	{
		m_nBGBlackAlpha += 5;

		if (m_nBGBlackAlpha > 255)
		{
			SOUNDMANAGER->Stop("Main");
			SCENEMANAGER->ChangeScene(m_sNextScene.c_str());
		}
	}
}

void cSceneMain::Render()
{
	m_pBackGround->Render(D3DXVECTOR3(m_pBackGround->textureInfo.Width/2, 0, 0),D3DXVECTOR3(WINSIZEX / 2, 0, 0));	

	m_pBackGroundWhite->AlphaRender(rc[4],
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(rc[4].left, rc[4].top + 350, 0), 80);

	char szTemp[1024];
	LPD3DXFONT pFont;
	pFont = FONTMANAGER->GetFont(cFontManager::TF_MAIN);

	sprintf_s(szTemp, 1024, "GAME  START");
	if(PtInRect(&rc[0], ptMouse))
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[0], DT_CENTER | DT_VCENTER, m_colorOver);
	else
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[0], DT_CENTER | DT_VCENTER, m_colorDefault);

	sprintf_s(szTemp, 1024, "PARTICLE  EDIT");
	if (PtInRect(&rc[1], ptMouse))
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[1], DT_CENTER | DT_VCENTER, m_colorOver);
	else
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[1], DT_CENTER | DT_VCENTER, m_colorDefault);

	sprintf_s(szTemp, 1024, "OPTION");
	if (PtInRect(&rc[2], ptMouse))
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[2], DT_CENTER | DT_VCENTER, m_colorOver);
	else
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[2], DT_CENTER | DT_VCENTER, m_colorDefault);

	sprintf_s(szTemp, 1024, "EXIT");
	if (PtInRect(&rc[3], ptMouse))
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[3], DT_CENTER | DT_VCENTER, m_colorOver);
	else
		pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[3], DT_CENTER | DT_VCENTER, m_colorDefault);
	
	m_pBackGroundBlack->AlphaRender(D3DXVECTOR3(m_pBackGround->textureInfo.Width / 2, 0, 0), D3DXVECTOR3(WINSIZEX / 2, 0, 0), m_nBGBlackAlpha);
}
