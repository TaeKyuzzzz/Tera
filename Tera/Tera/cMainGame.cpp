#include "stdafx.h"
#include "cMainGame.h"

#include "cCamera.h"
#include "cGrid.h"

#include "Scene\cSceneTest.h"
#include "Scene\01_MainScene\cSceneMain.h"

#include "Scene\02_LobbyScene\cSceneLobbyLoading.h"
#include "Scene\06_PaticleEdit\cScenePaticleEdit.h"
#include "Scene\05_BossScene\cSceneBossLoading.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pSceneTest(NULL)
{
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	
	surfcursor->Release();
	m_cursortex->Release();

	SCENEMANAGER->Destroy();
	TEXTUREMANAGER->Destroy();
	KEYMANAGER->Delete();
	TIMEMANAGER->Delete();
	SOUNDMANAGER->Release();
	FONTMANAGER->Destroy();
	SKINNEDMESHMANAGER->Destroy();
	STATICMESHMANAGER->Destroy();
	PARTICLEMANAGER->Destroy();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	SetLight();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pSceneTest = new cSceneTest;
	m_pSceneMain = new cSceneMain;
	m_pSceneLobbyLoading = new cSceneLobbyLoading;
	m_pScenePaticleEdit = new cScenePaticleEdit;
	m_pSceneBossLoading = new cSceneBossLoading;

	SCENEMANAGER->AddScene("Test", m_pSceneTest);
	SCENEMANAGER->AddScene("LobbyLoading", m_pSceneLobbyLoading);
	SCENEMANAGER->AddScene("Main", m_pSceneMain);
	SCENEMANAGER->AddScene("Boss", m_pSceneBossLoading);
	SCENEMANAGER->AddScene("PaticleEdit", m_pScenePaticleEdit);


	SCENEMANAGER->ChangeScene("Boss");
	
	// Ŀ�� �����ϴ� �κ�
	//m_cursortex = TEXTUREMANAGER->GetTexture("Texture/Cursor/Arrow.png");
	//m_cursortex = TEXTUREMANAGER->GetTexture("Texture/Cursor/Empty.png");
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/Cursor/Arrow.png", &m_cursortex);
	m_cursortex->GetSurfaceLevel(0, &surfcursor);

	// Ŀ�� ���α�
	//RECT Clip;
	//GetClientRect(g_hWnd, &Clip);
	//ClientToScreen(g_hWnd, (LPPOINT)&Clip);
	//ClientToScreen(g_hWnd, (LPPOINT)(&Clip.right));
	//ClipCursor(&Clip);

	g_pD3DDevice->SetCursorProperties(0, 0, surfcursor);
}

void cMainGame::Update()
{

	SCENEMANAGER->Update();
	
	if (g_vPlayerPos)
		m_pCamera->Update(*g_vPlayerPos);
	else
		m_pCamera->Update(D3DXVECTOR3(0, 0, 0));
	
	RemoteMode();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(254, 254,254), 1.0f, 0);

	g_pD3DDevice->BeginScene();
	
	/////////////////////////////////////////////////////////////////
	SetCursor(NULL);
	g_pD3DDevice->ShowCursor(true);
	

	m_pGrid->Render();
	SCENEMANAGER->Render();

	TIMEMANAGER->Render();
	///////////////////////////////////////////////////////////////////
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;

	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // ȯ�汤
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

	//g_pD3DDevice->SetLight(101, &stLight);
	//g_pD3DDevice->LightEnable(101, true);
	//
	//vDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//D3DXVec3Normalize(&vDir, &vDir);
	//stLight.Direction = vDir;
	//
	//g_pD3DDevice->SetLight(102, &stLight);
	//g_pD3DDevice->LightEnable(102, true);
	//
	//vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//D3DXVec3Normalize(&vDir, &vDir);
	//stLight.Direction = vDir;
	//
	//g_pD3DDevice->SetLight(102, &stLight);
	//g_pD3DDevice->LightEnable(103, true);
	//
	//vDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//D3DXVec3Normalize(&vDir, &vDir);
	//stLight.Direction = vDir;
	//
	//g_pD3DDevice->SetLight(102, &stLight);
	//g_pD3DDevice->LightEnable(104, true);
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
