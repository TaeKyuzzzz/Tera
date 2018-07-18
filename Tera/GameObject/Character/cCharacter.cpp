#include "stdafx.h"
#include "cCharacter.h"
#include "ProgressBar\cProgressBar.h"
#include "Sprite\cSprite.h"
#include "iMap.h"

cCharacter::cCharacter()
	: m_fRotY(0.0f)
	, m_vDirection(1, 0, 0)
	, m_vPosition(0, 0, 0)
	, m_fSpeed(1.0f)
	, m_vBeforeAnimPos(0, 0, 0)
	, m_vCurAnimPos(0, 0, 0)
	, m_fHpMax(300.0f)
	, m_fHpCur(300.0f)
	, m_fMpMax(150.0f)
	, m_fMpCur(150.0f)
	, m_pHpBar(NULL)
	, m_pMpBar(NULL)
	, m_BackBar(NULL)
	, m_pMap(NULL)
	, m_pBleedingAlpha(0)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matAnimWorld);
}


cCharacter::~cCharacter()
{
	SAFE_DELETE(m_pHpBar);
	SAFE_DELETE(m_pMpBar);
	SAFE_DELETE(m_BackBar);
	SAFE_DELETE(m_pBleeding);
}

void cCharacter::Setup()
{
	SetUpStateBar();

	m_pBleeding = TEXTUREMANAGER->GetSprite("Texture/Effect/bleeding.png");
	
	float xSize = (float) WINSIZEX / m_pBleeding->textureInfo.Width;
	D3DXMATRIX mat;
	D3DXMatrixScaling(&mat, xSize, 1, 1);
	m_pBleeding->m_pSprite->SetTransform(&mat);
}

void cCharacter::Update()
{
	UpdateUpStateBar();
	PlusMapHeight();

	if (m_pBleedingAlpha > 0)
		m_pBleedingAlpha -= 2;
	//m_matWorld._42 = m_vPosition.y;
}

void cCharacter::Render()
{
	RenderUpStateBar();
	//AlphaRender AlphaRenderWinSize
	m_pBleeding->AlphaRender(D3DXVECTOR3( WINSIZEX/2, 0, 0), D3DXVECTOR3(WINSIZEX / 2, 0, 0), m_pBleedingAlpha);
}

void cCharacter::PlusMapHeight()
{
	if (m_pMap)
		m_pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void cCharacter::SetUpStateBar()
{

	m_BackBar = TEXTUREMANAGER->GetSprite("Texture/CharacterInfo/CharacterInfo.png");

	m_pHpBar = new cProgressBar;
	m_pHpBar->Setup("Texture/CharacterInfo/HP.png",
		"Texture/CharacterInfo/HPLose.png",
		19 + m_BackBar->textureInfo.Width / 7.0f,
		26,
		WINSIZEX / 3.0f, WINSIZEY / 30.0f);

	m_pMpBar = new cProgressBar;
	m_pMpBar->Setup("Texture/CharacterInfo/MP.png",
		"Texture/CharacterInfo/MPLose.png",
		19 + m_BackBar->textureInfo.Width / 7.0f,
		32 + WINSIZEY / 30.0f,
		WINSIZEX / 3.0f, WINSIZEY / 30.0f);
}

void cCharacter::UpdateUpStateBar()
{
	m_pHpBar->SetGauge(m_fHpCur, m_fHpMax);
	m_pMpBar->SetGauge(m_fMpCur, m_fMpMax);

}

void cCharacter::RenderUpStateBar()
{
	m_BackBar->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(20, 20, 0));
	m_pHpBar->Render();
	m_pMpBar->Render();

	// ü�� ���� ����
	char szTemp[1024];
	RECT rc;

	sprintf_s(szTemp, 1024, "%d / %d", (int)m_fHpCur, (int)m_fHpMax);
	SetRect(&rc,
		300,
		26,
		300 + m_BackBar->textureInfo.Width,
		26 + 26);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::TF_UI_NUMBER);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc,
		DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));

	sprintf_s(szTemp, 1024, "%d / %d", (int)m_fMpCur, (int)m_fMpMax);
	SetRect(&rc,
		300,
		66,
		300 + m_BackBar->textureInfo.Width,
		66 + 26);

	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc,
		DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));


	pFont = FONTMANAGER->GetFont(cFontManager::TF_UI_TEXT);

	sprintf_s(szTemp, 1024, "HP", (int)m_fMpCur, (int)m_fMpMax);
	SetRect(&rc,
		120,
		26,
		350,
		26 + 26);

	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc,
		DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));

	sprintf_s(szTemp, 1024, "MP", (int)m_fMpCur, (int)m_fMpMax);
	SetRect(&rc,
		120,
		66,
		350,
		66 + 26);

	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc,
		DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
}

void cCharacter::Damaged()
{
	m_pBleedingAlpha = 120;
}
