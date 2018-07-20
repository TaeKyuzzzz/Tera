#include "stdafx.h"
#include "cUIManager.h"
#include "UI/cUIInfo.h"
#include "cItemManager.h"
#include "UI\cUIObject.h"
#include "UI\cUITextView.h"
#include "UI\cUIButton.h"
#include "GameObject\Item\cItemInfo.h"


cUIManager::cUIManager()
	:m_nAlpha(200)
	, m_nGold(100000)
{
}


cUIManager::~cUIManager()
{

}

void cUIManager::Setup()
{
	UITextList();
	CreateUIList();
	ConnectNode();

	inven = 0, shop = 0, status = 0;
	
}

void cUIManager::Update()
{


	//closeIdel 뒤의 I = Inventory S = Status C = ConsumablesShop
	CloseUI("closeIdleI");
	CloseUI("closeIdleS");
	CloseUI("closeIdleC");



	ItemInfoCTextRenewal("이름");

	CallKeyInput();


	if (m_isCallInven)		CallUIUpdate("Inventory");
	if (m_isCallStatus)		CallUIUpdate("Status");
	if (m_isCallShop)		CallUIUpdate("ConsumablesShop");


	//아이템 정보창
	m_vUI[FindUIIndex("ItemInfoWindow")]->Update();
	if (m_isItemInfoOutPut) m_vUI[FindUIIndex("ItemInfoWindow")]->GetUIRoot()->SetPosition(D3DXVECTOR3(ptMouse.x, ptMouse.y, 0));

	for (int i = 1; i < 3; i++)
	{
		ItemInfoITextRenewal(i);
	}

	//UIInfoTextPopUp("Inventory");
}

void cUIManager::Render()
{




	if (m_isCallInven)CallUIRender("Inventory");
	if (m_isCallStatus)CallUIRender("Status");
	if (m_isCallShop)CallUIRender("ConsumablesShop");


	if (m_isItemInfoOutPut)m_vUI[FindUIIndex("ItemInfoWindow")]->Render();

	for (int i = 0; i < m_vText.size(); i++)
	{
		m_vText[i]->Render();
	}

	UIInfoTextPopUp();


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

	m_pUIInfo->Setup(NULL, &_tagUIInfo);
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


	m_pUIInfo->Setup(NULL, &_tagUIInfo);
	m_vUI.push_back(m_pUIInfo);
}

void cUIManager::CreateText(tagText _tagText)
{
	int TextDataIndex;
	//해당 키워드로 텍스트팩 내부를 뒤져서 인덱스번호를 리턴함
	if(_tagText.Type == CONSTCHAR) TextDataIndex = UICTextDataIndex(_tagText.szTextName);
	if (_tagText.Type == VARIABLEVALUE)TextDataIndex = UIITextDataIndex(_tagText.nIdentyfyNum);
	

	m_pUIInfo = new cUI;

	tagTextPack _tagTextPack;

	if (_tagText.Type == CONSTCHAR)
	{
		_tagTextPack._textType = _tagText.Type;
		_tagTextPack._textParentName = _tagText.szParrentName;
		_tagTextPack._vTextCContents = m_vPreTextCDataPack[TextDataIndex];
		_tagTextPack._vTextPos = m_vPreTextCPosPack[TextDataIndex];
		_tagTextPack._vTextSize = m_vPreTextCSizePack[TextDataIndex];
		_tagTextPack._vTextColor = m_vPreTextCColorPack[TextDataIndex];
	}

	if (_tagText.Type == VARIABLEVALUE)
	{
		_tagTextPack._textType = _tagText.Type;
		_tagTextPack._textParentName = _tagText.szParrentName;
		_tagTextPack._vTextIContents = m_vPreTextIDataPack[TextDataIndex];
		_tagTextPack._vTextPos = m_vPreTextIPosPack[TextDataIndex];
		_tagTextPack._vTextSize = m_vPreTextISizePack[TextDataIndex];
		_tagTextPack._vTextColor = m_vPreTextIColorPack[TextDataIndex];
	}



	m_pUIInfo->Setup(&_tagTextPack);
	m_vText.push_back(m_pUIInfo);

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

	for (int i = 0; i < m_vText.size(); i++)
	{
		for (int j = 0; j < m_vUI.size(); j++)
		{
			if (m_vText[i]->GetParentName() == m_vUI[j]->GetName())
			{
				m_vText[i]->ConnectNode(m_vUI[j]->GetUIRoot());
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
	if (!m_isCallInven && KEYMANAGER->IsOnceKeyDown('I')) m_isCallInven = true;
	else if (m_isCallInven && KEYMANAGER->IsOnceKeyDown('I')) m_isCallInven = false;

	if (!m_isCallShop && KEYMANAGER->IsOnceKeyDown('S')) m_isCallShop = true;
	else if (m_isCallShop && KEYMANAGER->IsOnceKeyDown('S')) m_isCallShop = false;

	if (!m_isCallStatus && KEYMANAGER->IsOnceKeyDown('E')) m_isCallStatus = true;
	else if (m_isCallStatus && KEYMANAGER->IsOnceKeyDown('E')) m_isCallStatus = false;
}

void cUIManager::CreateUICTextData(vTextCContents _vTextCContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor)
{
	m_vPreTextCDataPack.push_back(_vTextCContents);
	m_vPreTextCPosPack.push_back(_vTextPos);
	m_vPreTextCSizePack.push_back(_vTextSize);
	m_vPreTextCColorPack.push_back(_vTextColor);
}

void cUIManager::CreateUIITextData(vTextIContents _vTextIContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor)
{
	m_vPreTextIDataPack.push_back(_vTextIContents);
	m_vPreTextIPosPack.push_back(_vTextPos);
	m_vPreTextISizePack.push_back(_vTextSize);
	m_vPreTextIColorPack.push_back(_vTextColor);
}

int cUIManager::UICTextDataIndex(const char* titleName)
{
	
	int indexSave;
	for (int i = 0; i < m_vPreTextCDataPack.size(); )
	{
		if (GetPreTextCDataPack()[i].operator[](0) == titleName)
		{
			indexSave = i;
			return indexSave;
		}
		else 
		{ 
			i++; 
		}
	}

}

int cUIManager::UIITextDataIndex(int variableName)
{
	int indexSave;
	for (int i = 0; i < m_vPreTextIDataPack.size(); )
	{
		if (GetPreTextIDataPack()[i].operator[](0) == variableName)
		{
			indexSave = i;
			return indexSave;
		}
		else
		{
			i++;
		}
	}
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

	if (szFindIndex != NULL)
	{
		int FindIndex = FindUIIndex(szFindIndex);
		sprintf_s(szTemp, 1024, "x = %d \t y = %d", (int)m_vUI[FindIndex]->GetUIRoot()->GetMatWorld()._41 - ptMouse.x
			, (int)m_vUI[FindIndex]->GetUIRoot()->GetMatWorld()._42 - ptMouse.y);
	}

	else sprintf_s(szTemp, 1024, "inven = %d \t\t\t status = %d \t\t\t shop = %d ", inven, status, shop);
	
	

	



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



int cUIManager::FindAbilityValue()
{
	for (int i = 0; i < _IM->GetAllItem().size(); i++)
	{
		//부딪혔을때
		if (_IM->GetAllItem()[i]->GetUIRoot()->GetIsCollision())
		{
			//부딪힌 녀석의 어빌리티값을 리턴한다.

			return _IM->GetAllItem()[i]->GetAbility().abilityValue;
		}
	}
}


//인트형 텍스트 정보중에서
void cUIManager::ItemInfoITextRenewal(int sequence)
{



	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetidentifyNUM() == sequence)
		{

			vector<int> vInt;

			//새로 만든 벡터를 데이터갯수에 맞게 재조정한다.
			//팩 벡터 내부의 백터들중에 첫 텍스트에 입력된 정보가 인트 sequence인 녀석을 찾음
			vInt.resize(m_vPreTextIDataPack[UIITextDataIndex(sequence)].size());

			//0번은 식별자라 1번부터 작성하면된다.

			// 번호가 1번일때
			if (sequence == 1)
			{
				vInt[1] = m_nGold;
				m_vText[i]->GetText()->SetTextIContents(vInt);
			}

			// 번호가 2이상일때
			else
			{
				vInt[1] = FindAbilityValue();
					
				m_vText[i]->GetText()->SetTextIContents(vInt);
			}

		

		}
	}
}

void cUIManager::ItemInfoCTextRenewal(const char* szFindText)
{
	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetIdentifyCHAR() == szFindText)
		{
			vector<const char*> vChar;

			vChar.resize(m_vPreTextCDataPack[UICTextDataIndex(szFindText)].size());

			

			for (int i = 0; i < _IM->GetAllItem().size(); i++)
			{
				if (_IM->GetAllItem()[i]->GetUIRoot()->GetIsCollision())
				{			

					//_IM->GetAllItem()[i]->GetUIRoot()

					vChar[0] = _IM->GetAllItem()[i]->GetName();

					if (_IM->GetAllItem()[i]->GetAbility()._tagItemKind == ETCCONSUMABLES)
					{
						vChar[1] = "기능아이템";
					}

					else if (_IM->GetAllItem()[i]->GetAbility()._tagItemKind == POTION)
					{
						vChar[1] = "회복력";
					}

					else if (_IM->GetAllItem()[i]->GetAbility()._tagItemKind == WEAPON)
					{
						vChar[1] = "공격력";
					}

					else
					{
						vChar[1] = "방어력";
					}

					vChar[2] = "설명";

					vChar[3] = textExplane.find(_IM->GetAllItem()[i]->GetName())->second;

					break;
				}			


				
			}


			m_vText[i]->GetText()->SetTextCContents(vChar);
			
		}
	}
}

