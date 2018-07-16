#include "stdafx.h"
#include "Scene\06_PaticleEdit\cScenePaticleEdit.h"

#include "Sprite\cSprite.h"

cScenePaticleEdit::cScenePaticleEdit()
{
	m_type = PTC_TYPE_LOOP;
	m_fTime = 0.0f;
	m_fSpeed = 0.0f;
	m_fAcc = 0.0f;
	m_fAccMin = 0;
	m_fAccMax = 0;

	m_fPositionX = 0;
	m_fRandPosXMin = 0;
	m_fRandPosXMax = 0;

	m_fPositionY = 0;
	m_fRandPosYMin = 0;
	m_fRandPosYMax = 0;

	m_fPositionZ = 0;
	m_fRandPosZMin = 0;
	m_fRandPosZMax = 0;

	m_fDirectionX = 0;
	m_fRandDirXMin = 0;
	m_fRandDirXMax = 0;

	m_fDirectionY = 0;
	m_fRandDirYMin = 0;
	m_fRandDirYMax = 0;

	m_fDirectionZ = 0;
	m_fRandDirZMin = 0;
	m_fRandDirZMax = 0;

	m_szFile[1024];
	char * asd= "Texture/asd/asdasd.png";
	strcpy(m_szFile, asd);
}


cScenePaticleEdit::~cScenePaticleEdit()
{
	SAFE_DELETE(m_pParticleSet);
	//SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pMainImamge);
}

void cScenePaticleEdit::Setup()
{
	//m_pSprite = TEXTUREMANAGER->GetSprite("Texture/SceneTexture/BGBlack.png");
	
	m_pParticleSet = new cParticleSet;
	
	
	//m_pParticleSet->Setup(
	//1.0f,1.0f,
	//	-0.001f,0,0,
	//	0,-10,10,
	//	0,0,0,
	//	0,-20,20,
	//	0,-30,30,
	//	100,0,0,
	//	0,-30,30,
	//	"Texture/Particle/fire_01.png"
	//	,D3DCOLOR_ARGB(50,255,0,0));

	m_pParticleSet->Setup(
		PTC_TYPE_ONCE,
		0.4f, 1.0f,
		0,100,200,
		0, 0, 100,
		0, 0, 0,
		0, -5, 5,
		0, -50, 50,
		100, 0,0,
		0, -50, 50,
		"Texture/Particle/fire_01.png"
		, D3DCOLOR_ARGB(100, 255, 255, 255));

	UISetup();

}

void cScenePaticleEdit::Update()
{
	m_pParticleSet->Update();
	UIUpdate();

}

void cScenePaticleEdit::Render()
{
	//m_pSprite->Render(D3DXVECTOR3(m_pSprite->textureInfo.Width / 2, 0, 0), D3DXVECTOR3(WINSIZEX / 2, 0, 0));
	m_pParticleSet->Render();
	UIRender();

	char szTemp[1024];
	sprintf_s(szTemp, 1024, "%d %d", ptMouse.x,ptMouse.y);
	RECT rc;
	SetRect(&rc, 300, 0, 500, 100);

	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_DEFAULT);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc,
		DT_LEFT | DT_VCENTER,
		D3DCOLOR_XRGB(255, 0, 0));
}

void cScenePaticleEdit::UISetup()
{
	m_pMainImamge = TEXTUREMANAGER->GetSprite("Texture/UI/ParticleEdit/particleEdit_main.png");

	x = 0;
	y = 0;

	// \ui ³ë°¡´Ù...

	rc[0]  = RectMake(95, 15, 50, 15);
	rc[1]  = RectMake(95, 35, 50, 15);
	rc[2]  = RectMake(95, 60, 105, 15);
	rc[3]  = RectMake(95, 105, 50, 15);

	rc[4]  = RectMake(95, 125, 50, 15);
	rc[5]  = RectMake(155, 125, 50, 15);
	rc[6]  = RectMake(220, 125, 50, 15);
	
	rc[7]  = RectMake(95, 175, 50, 15);
	rc[8]  = RectMake(155, 175, 50, 15);
	rc[9]  = RectMake(220, 175, 50, 15);
	
	rc[10] = RectMake(95,  200, 50, 15);
	rc[11] = RectMake(155, 200, 50, 15);
	rc[12] = RectMake(220, 200, 50, 15);
	
	rc[13] = RectMake(95,  225, 50, 15);
	rc[14] = RectMake(155, 225, 50, 15);
	rc[15] = RectMake(220, 225, 50, 15);
	
	rc[16] = RectMake(95,  265, 50, 15);
	rc[17] = RectMake(155, 265, 50, 15);
	rc[18] = RectMake(220, 265, 50, 15);
	
	rc[19] = RectMake(95,  290, 50, 15);
	rc[20] = RectMake(155, 290, 50, 15);
	rc[21] = RectMake(220, 290, 50, 15);
	
	rc[22] = RectMake(95,  315, 50, 15);
	rc[23] = RectMake(155, 315, 50, 15);
	rc[24] = RectMake(220, 315, 50, 15);

	rc[25] = RectMake(95, 360, 300, 15);

}

void cScenePaticleEdit::UIUpdate()
{
	for (int i = 0; i < 26; i++)
	{
		if (PtInRect(&rc[i], ptMouse))
		{
			if (KEYMANAGER->IsStayKeyDown(VK_CONTROL))
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					switch (i)
					{
					case  1:	m_fTime += 0.1f;	break;
					case 2:
						if (m_type == PTC_TYPE_LOOP)
							m_type = PTC_TYPE_ONCE;
						else
							m_type = PTC_TYPE_LOOP;
						break;
					case  3:	m_fSpeed += 0.1f;	break;
					case  4:	m_fAcc += 0.001f;	break;
					case  5:	m_fAccMin++;		break;
					case  6:	m_fAccMax++;		break;
					case  7:	m_fPositionX++;		break;
					case  8:	m_fRandPosXMin++;	break;
					case  9:	m_fRandPosXMax++;	break;
					case 10:	m_fPositionY++;		break;
					case 11:	m_fRandPosYMin++;	break;
					case 12:	m_fRandPosYMax++;	break;
					case 13:	m_fPositionZ++;		break;
					case 14:	m_fRandPosZMin++;	break;
					case 15:	m_fRandPosZMax++;	break;
					case 16:	m_fDirectionX++;	break;
					case 17:	m_fRandDirXMin++;	break;
					case 18:	m_fRandDirXMax++;	break;
					case 19:	m_fDirectionY++;	break;
					case 20:	m_fRandDirYMin++;	break;
					case 21:	m_fRandDirYMax++;	break;
					case 22:	m_fDirectionZ++;	break;
					case 23:	m_fRandDirZMin++;	break;
					case 24:	m_fRandDirZMax++;	break;
					}
				}
				else if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
				{
					switch (i)
					{
					case  1:	m_fTime -= 0.1f;	break;
					case 2:
						if (m_type == PTC_TYPE_LOOP)
							m_type = PTC_TYPE_ONCE;
						else
							m_type = PTC_TYPE_LOOP;
						break;
					case  3:	m_fSpeed -= 0.1f;	break;
					case  4:	m_fAcc -= 0.001f;	break;
					case  5:	m_fAccMin--;		break;
					case  6:	m_fAccMax--;		break;
					case  7:	m_fPositionX--;		break;
					case  8:	m_fRandPosXMin--;	break;
					case  9:	m_fRandPosXMax--;	break;
					case 10:	m_fPositionY--;		break;
					case 11:	m_fRandPosYMin--;	break;
					case 12:	m_fRandPosYMax--;	break;
					case 13:	m_fPositionZ--;		break;
					case 14:	m_fRandPosZMin--;	break;
					case 15:	m_fRandPosZMax--;	break;
					case 16:	m_fDirectionX--;	break;
					case 17:	m_fRandDirXMin--;	break;
					case 18:	m_fRandDirXMax--;	break;
					case 19:	m_fDirectionY--;	break;
					case 20:	m_fRandDirYMin--;	break;
					case 21:	m_fRandDirYMax--;	break;
					case 22:	m_fDirectionZ--;	break;
					case 23:	m_fRandDirZMin--;	break;
					case 24:	m_fRandDirZMax--;	break;
					}
				}
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				switch (i)
				{
				case  1:	m_fTime += 0.1f;	break;
				case 2 : 
					if (m_type == PTC_TYPE_LOOP)
						m_type = PTC_TYPE_ONCE;
					else
						m_type = PTC_TYPE_LOOP;
					break;
				case  3:	m_fSpeed += 0.1f;	break;
				case  4:	m_fAcc += 0.001f;	break;
				case  5:	m_fAccMin++;		break;
				case  6:	m_fAccMax++;		break;
				case  7:	m_fPositionX++;		break;
				case  8:	m_fRandPosXMin++;	break;
				case  9:	m_fRandPosXMax++;	break;
				case 10:	m_fPositionY++;		break;
				case 11:	m_fRandPosYMin++;	break;
				case 12:	m_fRandPosYMax++;	break;
				case 13:	m_fPositionZ++;		break;
				case 14:	m_fRandPosZMin++;	break;
				case 15:	m_fRandPosZMax++;	break;
				case 16:	m_fDirectionX++;	break;
				case 17:	m_fRandDirXMin++;	break;
				case 18:	m_fRandDirXMax++;	break;
				case 19:	m_fDirectionY++;	break;
				case 20:	m_fRandDirYMin++;	break;
				case 21:	m_fRandDirYMax++;	break;
				case 22:	m_fDirectionZ++;	break;
				case 23:	m_fRandDirZMin++;	break;
				case 24:	m_fRandDirZMax++;	break;
				}
			}
			else if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
			{
				switch (i)
				{
				case  1:	m_fTime -= 0.1f;	break;
				case 2:
					if (m_type == PTC_TYPE_LOOP)
						m_type = PTC_TYPE_ONCE;
					else
						m_type = PTC_TYPE_LOOP;
					break;
				case  3:	m_fSpeed -= 0.1f;	break;
				case  4:	m_fAcc -= 0.001f;	break;
				case  5:	m_fAccMin--;		break;
				case  6:	m_fAccMax--;		break;
				case  7:	m_fPositionX--;		break;
				case  8:	m_fRandPosXMin--;	break;
				case  9:	m_fRandPosXMax--;	break;
				case 10:	m_fPositionY--;		break;
				case 11:	m_fRandPosYMin--;	break;
				case 12:	m_fRandPosYMax--;	break;
				case 13:	m_fPositionZ--;		break;
				case 14:	m_fRandPosZMin--;	break;
				case 15:	m_fRandPosZMax--;	break;
				case 16:	m_fDirectionX--;	break;
				case 17:	m_fRandDirXMin--;	break;
				case 18:	m_fRandDirXMax--;	break;
				case 19:	m_fDirectionY--;	break;
				case 20:	m_fRandDirYMin--;	break;
				case 21:	m_fRandDirYMax--;	break;
				case 22:	m_fDirectionZ--;	break;
				case 23:	m_fRandDirZMin--;	break;
				case 24:	m_fRandDirZMax--;	break;
				}
			}
		}
	}
}

void cScenePaticleEdit::UIRender()
{
	m_pMainImamge->Render(x, y);

	char szTemp[1024];
	LPD3DXFONT pFont;
	pFont = FONTMANAGER->GetFont(cFontManager::TF_UI_NUMBER2);

	sprintf_s(szTemp, 1024, "%s", m_sName);
	pFont->DrawTextA(NULL,szTemp,strlen(szTemp),&rc[0],DT_LEFT | DT_VCENTER,D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%.1f", m_fTime);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[1], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	if(m_type == PTC_TYPE_LOOP)
		sprintf_s(szTemp, 1024, "Type_Loop");
	else if (m_type == PTC_TYPE_ONCE)
		sprintf_s(szTemp, 1024, "Type_Once");
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[2], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%.1f", m_fSpeed);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[3], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%.3f", m_fAcc);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[4], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fAccMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[5], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fAccMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[6], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fPositionX);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[7], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosXMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[8], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosXMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[9], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fPositionY);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[10], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosYMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[11], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosYMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[12], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fPositionZ);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[13], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosZMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[14], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandPosZMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[15], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fDirectionX);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[16], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirXMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[17], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirXMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[18], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fDirectionY);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[19], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirYMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[20], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirYMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[21], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%d", m_fDirectionZ);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[22], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirZMin);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[23], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(szTemp, 1024, "%d", m_fRandDirZMax);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[24], DT_RIGHT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	
	sprintf_s(szTemp, 1024, "%s", m_szFile);
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc[25], DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
}

void cScenePaticleEdit::LoadTexture()
{

}
