#include "stdafx.h"
#include "cMainGame.h"

#include "cCamera.h"
#include "cGrid.h"

#include "Scene\cSceneTest.h"
#include "Scene\01_MainScene\cSceneMain.h"

#include "Scene\02_LobbyScene\cSceneLobbyLoading.h"
#include "Scene\06_PaticleEdit\cScenePaticleEdit.h"
#include "Scene\05_BossScene\cSceneBossLoading.h"
#include "Scene\05_BossScene\cSceneBoss.h"

#include "Scene/11_MapEdit/cSceneMapEdit.h"
cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	
	surfcursor->Release();
	m_cursorArrow->Release();
	m_cursorEmpty->Release();

	SCENEMANAGER->Destroy();
	TEXTUREMANAGER->Destroy();
	KEYMANAGER->Delete();
	TIMEMANAGER->Delete();
	SOUNDMANAGER->Release();
	FONTMANAGER->Destroy();
	SKINNEDMESHMANAGER->Destroy();
	STATICMESHMANAGER->Destroy();
	PARTICLEMANAGER->Destroy();
	CAMERAMANAGER->Destroy();
	ITEMMANAGER->Destroy();
	UIMANAGER->Destroy();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	SetLight();

	//m_pCamera = new cCamera;
	//m_pCamera->Setup();
	
	CAMERAMANAGER->Create();
	
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	SCENEMANAGER->AddScene("PaticleEdit", new cScenePaticleEdit);

	SCENEMANAGER->AddScene("Main", new cSceneMain);
	SCENEMANAGER->AddScene("LobbyLoading", new cSceneLobbyLoading);
	SCENEMANAGER->AddScene("Test", new cSceneTest);
	SCENEMANAGER->AddScene("Boss", new cSceneBoss);
	SCENEMANAGER->AddScene("BossLoading", new cSceneBossLoading);
	SCENEMANAGER->AddScene("MapEdit", new cSceneMapEdit);


	SCENEMANAGER->ChangeScene("Main");
	
	// 커서 설정하는 부분
	//m_cursorArrow = TEXTUREMANAGER->GetTexture("Texture/Cursor/Arrow.png");
	//m_cursorEmpty = TEXTUREMANAGER->GetTexture("Texture/Cursor/Empty.png");
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/Cursor/Arrow.png", &m_cursorArrow);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/Cursor/Empty.png", &m_cursorEmpty);
	
	m_cursorArrow->GetSurfaceLevel(0, &surfcursor);
	g_pD3DDevice->SetCursorProperties(0, 0, surfcursor);


	// 커서 가두기
	//RECT Clip;
	//GetClientRect(g_hWnd, &Clip);
	//ClientToScreen(g_hWnd, (LPPOINT)&Clip);
	//ClientToScreen(g_hWnd, (LPPOINT)(&Clip.right));
	//ClipCursor(&Clip);
}

void cMainGame::Update()
{
	CAMERAMANAGER->Update();
	OBJECTMANAGER->PickObject();
	SCENEMANAGER->Update();

	RemoteMode();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(254, 254,254), 1.0f, 0);

	SetCursor(NULL);
	
	if(isOptionMode)
		g_pD3DDevice->ShowCursor(true);
	else
		g_pD3DDevice->ShowCursor(false);

	g_pD3DDevice->BeginScene();
	
	/////////////////////////////////////////////////////////////////
	

	//m_pGrid->Render();
	SCENEMANAGER->Render();

	TIMEMANAGER->Render();

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "%d %d", ptMouse.x, ptMouse.y);
	RECT rc;
	SetRect(&rc, WINSIZEX - 200, 0100, WINSIZEX, 200);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 0, 0));
	///////////////////////////////////////////////////////////////////
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;

	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // 환경광
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//stLight.Range = 10000.0f;
	D3DXVECTOR3 vDir(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDevice->SetLight(100, &stLight);
	g_pD3DDevice->LightEnable(100, true);

	vDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDevice->SetLight(101, &stLight);
	g_pD3DDevice->LightEnable(101, true);
	
	vDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	
	g_pD3DDevice->SetLight(102, &stLight);
	g_pD3DDevice->LightEnable(102, true);
	
	vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	
	g_pD3DDevice->SetLight(103, &stLight);
	g_pD3DDevice->LightEnable(103, true);
	
	vDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	
	g_pD3DDevice->SetLight(104, &stLight);
	g_pD3DDevice->LightEnable(104, true);
}

void cMainGame::RemoteMode()
{
	if (KEYMANAGER->IsStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->IsOnceKeyDown('F'))
		{
			DWORD n;
			g_pD3DDevice->GetRenderState(D3DRS_FILLMODE, &n);
			if (n == D3DFILL_WIREFRAME)
				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			else
				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
	}


}
