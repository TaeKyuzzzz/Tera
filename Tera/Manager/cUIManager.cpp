#include "stdafx.h"
#include "cUIManager.h"
#include "UI/cUIInfo.h"
#include "cItemManager.h"
#include "UI\cUIObject.h"
#include "UI\cUIButton.h"
#include "GameObject\Item\cItemInfo.h"


cUIManager::cUIManager()
	:m_nAlpha(200)
{
}


cUIManager::~cUIManager()
{
	//SAFE_DELETE(m_pUIInfo);
	//m_pUIInfo->
}

void cUIManager::Setup()
{
	CreateUIList();
	ConnectNode();


	
}

void cUIManager::Update()
{
	//closeIdel 뒤의 I = Inventory S = Status C = ConsumablesShop
	CloseUI("closeIdleI");
	CloseUI("closeIdleS");
	CloseUI("closeIdleC");

	CallKeyInput();


	if (m_isCallInven)		CallUIUpdate("Inventory");
	if (m_isCallStatus)		CallUIUpdate("Status");
	if (m_isCallShop)		CallUIUpdate("ConsumablesShop");

	//UIInfoTextPopUp("Inventory");
}

void cUIManager::Render()
{




	if (m_isCallInven)CallUIRender("Inventory");
	if (m_isCallStatus)CallUIRender("Status");
	if (m_isCallShop)CallUIRender("ConsumablesShop");




	UIInfoTextPopUp("Status");


}

void cUIManager::Destroy()
{
	SAFE_DELETE(m_pUIInfo);
}

void cUIManager::CreateUI(UIType _UIType, const char* UIName, const char* filePath, D3DXVECTOR3 vec3Pos, D3DXVECTOR2 vec2ReduceDragSize, const char* UIParentName)
{
	m_pUIInfo = new cUI;

	tagUIInfo _tagUIInfo;

	_tagUIInfo._UIType = _UIType;
	_tagUIInfo._UIName = UIName;
	_tagUIInfo._UIPath1 = filePath;
	_tagUIInfo._UIPos = vec3Pos;
	_tagUIInfo._UIParentName = UIParentName;
	_tagUIInfo._UIReduceDragSize = vec2ReduceDragSize;

	m_pUIInfo->Setup(&_tagUIInfo);
	m_vUI.push_back(m_pUIInfo);
}

void cUIManager::CreateUI(UIType _UIType, const char * UIName, const char * filePath1, const char * filePath2, const char * filePath3, D3DXVECTOR3 vec3Pos,  const char * UIParentName)
{

	m_pUIInfo = new cUI;

	tagUIInfo _tagUIInfo;

	_tagUIInfo._UIType = _UIType;
	_tagUIInfo._UIName = UIName;
	_tagUIInfo._UIPath1 = filePath1;
	_tagUIInfo._UIPath2 = filePath2;
	_tagUIInfo._UIPath3 = filePath3;
	_tagUIInfo._UIPos = vec3Pos;
	_tagUIInfo._UIParentName = UIParentName;


	m_pUIInfo->Setup(&_tagUIInfo);
	m_vUI.push_back(m_pUIInfo);
}


void cUIManager::ConnectNode()
{
	for (int i = 0; i < m_vUI.size(); i++)
	{
		for (int j = 0; j < m_vUI.size(); j++)
		{
			//부모이름과 같은 네임을 가진 녀석을 찾고
			//부모이름 가진녀석에게 루트를 설정해줌
			if (m_vUI[i]->GetParentName() == m_vUI[j]->GetName())
			{
				m_vUI[i]->ConnectNode(m_vUI[j]->GetUIRoot());
			}
		}
	}
}


void cUIManager::CallUIUpdate(const char* UIname)
{	
	for (int i = 0; i < m_vUI.size(); i++)
	{
		if (m_vUI[i]->GetName() == UIname)
		{
			m_vUI[i]->Update();
		}
	
	}
	
}

void cUIManager::CallUIRender(const char* UIname)
{
	for (int i = 0; i < m_vUI.size(); i++)
	{
		if (m_vUI[i]->GetName() == UIname)
		{
			m_vUI[i]->Render();
		}

	}	
}

void cUIManager::CallKeyInput()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
	{
		if (isOptionMode)
		{
			isOptionMode = false;
			CAMERAMANAGER->SetType(CAMERA_FREE);
			m_isCallInven = false;
			m_isCallShop = false;
			m_isCallStatus = false;
		}
		else
		{
			isOptionMode = true;
			CAMERAMANAGER->SetType(CAMERA_FIX);
		}
	}

	if (!m_isCallInven && KEYMANAGER->IsOnceKeyDown('I'))
	{
		m_isCallInven = true;
		isOptionMode = true;
		CAMERAMANAGER->SetType(CAMERA_FIX);
	}
	else if (m_isCallInven && KEYMANAGER->IsOnceKeyDown('I')) m_isCallInven = false;

	if (!m_isCallShop && KEYMANAGER->IsOnceKeyDown('Q'))
	{
		m_isCallShop = true;
		isOptionMode = true;
		CAMERAMANAGER->SetType(CAMERA_FIX);
	}
	else if (m_isCallShop && KEYMANAGER->IsOnceKeyDown('Q')) m_isCallShop = false;

	if (!m_isCallStatus && KEYMANAGER->IsOnceKeyDown('E'))
	{
		m_isCallStatus = true;
		isOptionMode = true;
		CAMERAMANAGER->SetType(CAMERA_FIX);
	}
	else if (m_isCallStatus && KEYMANAGER->IsOnceKeyDown('E')) m_isCallStatus = false;
}

void cUIManager::CloseUI(const char* szUIName)
{
	int Index = FindUIIndex(szUIName);

	RECT rc = m_vUI[Index]->GetUIButtonImage()->GetCollisionRect();

	if (PtInRect(&rc, ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			if(szUIName == "closeIdleI") m_isCallInven = false;
			else if (szUIName == "closeIdleS") m_isCallStatus = false;
			else if (szUIName == "closeIdleC") m_isCallShop = false;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			if (szUIName == "closeIdleI") m_isCallInven = true;
			else if (szUIName == "closeIdleS") m_isCallStatus = true;
			else if (szUIName == "closeIdleC") m_isCallShop = true;
		}
	}

	//if(i == UIIndex.Inventory) 	m_isCallInven = false;
	//else if (i = UIIndex.Status) m_isCallStatus = false;
	//else if (i == UIIndex.ConsumablesShop) m_isCallShop = false;
		

		

	
}

int cUIManager::FindUIIndex(const char* szFindIndex)
{
	

	for (int i = 0; i < m_vUI.size(); i++)
	{
		if (m_vUI[i]->GetName() == szFindIndex)
		{
			return i;
		}
	}
}

void cUIManager::UIInfoTextPopUp(const char* szFindIndex)
{
	char szTemp[1024];
	

	int FindIndex = FindUIIndex(szFindIndex);
	sprintf_s(szTemp, 1024, "x = %d \t y = %d", (int)m_vUI[FindIndex]->GetUIRoot()->GetMatWorld()._41 - ptMouse.x
		, (int)m_vUI[FindIndex]->GetUIRoot()->GetMatWorld()._42 - ptMouse.y);
	
	
	
	RECT rc2;
	SetRect(&rc2, 100, 100, 800, 200);
	
	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, { 30, 20 });
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc2,
		DT_LEFT | DT_TOP,
		D3DCOLOR_XRGB(255, 255, 0));
	pFont->Release();
}

