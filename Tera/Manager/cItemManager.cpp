#include "stdafx.h"
#include "cItemManager.h"
#include "GameObject/Item/cItem.h"
#include "UI\cUIObject.h"
#include "UI/cUIInfo.h"
#include "UI/cUIImageView.h"
#include "UI/cUIButton.h"
#include "UI\cUITextView.h"



cItemManager::cItemManager()
	:nItemNum(0)
	, isTemp(false)
	, m_vClickedIndex(0)
	, m_nGold(10000)
{
	
}


cItemManager::~cItemManager()
{
	//SAFE_DELETE(m_pItemInfo);
}

void cItemManager::Setup()
{
	UITextList();
	
	hdc = GetDC(g_hWnd);
	//슬롯만들기
	SetItemSlot(INVENTORY);
	SetItemSlot(CONSUMABLESSHOP);
	SetItemSlot(STATUSSLOT);

	//아이템목록에 있는 아이템 생성하기
	CreateItemList();

	ConnectNodeCommand();

}

void cItemManager::Update()
{


	//슬롯을 가지고 있는 UI의 위치를 갱신하여
	//슬롯의 위치도 갱신시켜준다.
	UIPosRenewal("Inventory");
	ItemSlotPosRenewal(INVENTORY, m_vec3RenwalInvenPos);
	UIPosRenewal("ConsumablesShop");
	ItemSlotPosRenewal(CONSUMABLESSHOP, m_vec3RenwalShop);
	UIPosRenewal("Status");
	ItemSlotPosRenewal(STATUSSLOT, m_vec3RenwalStatus);

	//드래그하는 동안의 예외설정
	ExceptionsWhileDragging();

	//슬롯 내 정렬
	SortInSlot();


	//각자 장소에 있는 아이템 모두 업데이트
	ItemUpdate();

	//MoveFromAToB(m_vInvenItem, m_vShopSlot);
	//MoveFromAToB(m_vShopItem, m_vInvenSlot);
	//MoveFromAToB(m_vInvenItem, m_vStatusSlot);

	
	ClickUseItemThisPlace(m_vInvenItem, "Inventory");
	ClickUseItemThisPlace(m_vStatusItem, "Status");
	ClickUseItemThisPlace(m_vShopItem, "ConsumablesShop");

	SalesItemCalculator();


	m_vItemAssistant[0]->Update();
	m_vItemAssistant[0]->GetUIRoot()->SetPosition(D3DXVECTOR3(ptMouse.x, ptMouse.y + 20, 0));
	m_vItemAssistant[1]->GetUIImage()->SetPosition(D3DXVECTOR3(110, 200, 0));
	

	//아이템 정보창
	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->Update();		
	}
	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->GetUIImage()->SetPosition(D3DXVECTOR3(ptMouse.x + 5, ptMouse.y + 33, 0));
	}





	ItemInfoCTextRenewal("아이템정보");

	for (int i = 1; i < 4; i++)
	{
		ItemInfoITextRenewal(i);
	}


}

void cItemManager::Render()
{
	ItemRender();	

	ItemExplaneRendingCondition(m_vInvenItem);
	ItemExplaneRendingCondition(m_vStatusItem);
	ItemExplaneRendingCondition(m_vShopItem);

	//if (isPlaceItemCollision)
	//{
	//	//아이템 정보창
	//	for (int i = 0; i < m_vItemImitation.size(); i++)
	//	{
	//		if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
	//		{
	//			m_vItemImitation[i]->Render();
	//		}
	//	}
	//}

	if (isPlaceItemCollision)
	{

		//아이템 정보창
		for (int i = 0; i < m_vItemImitation.size(); i++)
		{
			for (int j = 0; j < m_vAllItem.size(); j++)
			{
				if (m_vAllItem[j]->GetUIRoot()->GetIsCollision())
				{
					if (m_vItemImitation[i]->GetName() == m_vAllItem[j]->GetName())
						m_vItemImitation[i]->Render();
				}
			}
		}
		
	}




	for (int i = 0; i < m_vText.size(); i++)
	{
		m_vText[i]->Render();
	}

	//값 찍어보기
	//char szTemp[1024];	
	//sprintf_s(szTemp, 1024, "인벤아이템갯수 : %d, \n 장비창아이템갯수 : %d"
	//	, m_vInvenItem.size(), m_vStatusItem.size());
	//RECT rc2;
	//SetRect(&rc2, 100, 200, 800, 400);
	//LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, { 30, 20 });
	//pFont->DrawTextA(NULL,
	//	szTemp,
	//	strlen(szTemp),
	//	&rc2,
	//	DT_LEFT | DT_TOP,
	//	D3DCOLOR_XRGB(255, 255, 0));
	//pFont->Release();


}

void cItemManager::Destroy()
{
	SAFE_DELETE(m_pItemInfo);
	//safe
	//for (auto p : m_vAllItem)
	//{
	//	SAFE_DELETE(p);
	//}

}

void cItemManager::CreateText(tagText _tagText)
{
	int TextDataIndex;
	//해당 키워드로 텍스트팩 내부를 뒤져서 인덱스번호를 리턴함
	if (_tagText.Type == CONSTCHAR) TextDataIndex = UICTextDataIndex(_tagText.szTextName);
	if (_tagText.Type == VARIABLEVALUE)TextDataIndex = UIITextDataIndex(_tagText.nIdentyfyNum);


	m_pItemTextInfo = new cItem;

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



	m_pItemTextInfo->Setup(&_tagTextPack);
	m_vText.push_back(m_pItemTextInfo);

}

void cItemManager::CreateUICTextData(vTextCContents _vTextCContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor)
{
	m_vPreTextCDataPack.push_back(_vTextCContents);
	m_vPreTextCPosPack.push_back(_vTextPos);
	m_vPreTextCSizePack.push_back(_vTextSize);
	m_vPreTextCColorPack.push_back(_vTextColor);
}

void cItemManager::CreateUIITextData(vTextIContents _vTextIContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor)
{
	m_vPreTextIDataPack.push_back(_vTextIContents);
	m_vPreTextIPosPack.push_back(_vTextPos);
	m_vPreTextISizePack.push_back(_vTextSize);
	m_vPreTextIColorPack.push_back(_vTextColor);
}

int cItemManager::UICTextDataIndex(const char * titleName)
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

int cItemManager::UIITextDataIndex(int variableName)
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

void cItemManager::ItemInfoITextRenewal(int sequence)
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

			// 번호가 1번일때 인벤토리 소지금 텍스트
			if (sequence == 1)
			{
				vInt[1] = m_nGold;
				m_vText[i]->GetText()->SetTextIContents(vInt);
			}

			// 번호가 2이상일때 아이템툴팁 텍스트
			else if(sequence == 2)
			{
				vInt[1] = FindAbilityValue();

				vInt[2] = FindSalePriceValue();

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			//스테이터스 텍스트
			else if (sequence == 3)
			{
				vInt[1] = m_nAttackValue;

				vInt[2] = m_nDefenceValue;

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}



		}
	}
}

void cItemManager::ItemInfoCTextRenewal(const char * szFindText)
{
	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetIdentifyCHAR() == szFindText)
		{
			vector<const char*> vChar;

			vChar.resize(m_vPreTextCDataPack[UICTextDataIndex(szFindText)].size());



			for (int i = 0; i < m_vAllItem.size(); i++)
			{
				if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
				{

					//m_vAllItem[i]->GetUIRoot()

					vChar[0] = m_vAllItem[i]->GetName();

					if (m_vAllItem[i]->GetItemKind() == ETCCONSUMABLES)
					{
						vChar[1] = "기능아이템";
					}

					else if (m_vAllItem[i]->GetItemKind() == POTION)
					{
						vChar[1] = "회복력";
					}

					else if (m_vAllItem[i]->GetItemKind() == WEAPON)
					{
						vChar[1] = "공격력";
					}

					else
					{
						vChar[1] = "방어력";
					}

					vChar[2] = "설명";

					vChar[3] = textExplane.find(m_vAllItem[i]->GetName())->second;

					vChar[4] = FindItemKind();
				}



			}


			m_vText[i]->GetText()->SetTextCContents(vChar);

		}
	}
}

int cItemManager::FindAbilityValue()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		//부딪혔을때
		if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
		{
			//부딪힌 녀석의 어빌리티값을 리턴한다.

			return m_vAllItem[i]->GetAbilityValue();
		}
	}
}

int cItemManager::FindItemExplaneWndIndex(const char* szItemExplaneName)
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		if (m_vAllItem[i]->GetName() == szItemExplaneName)
		{
			return i;
		}
	}
}

//int cItemManager::FindSalePriceValue(vItem vPlaceItem)
//{
//	for (int i = 0; i < vPlaceItem.size(); i++)
//	{
//		if(vPlaceItem == m_vShopItem) return vPlaceItem[i]->GetBuyPrice();
//		else return vPlaceItem[i]->GetSalePrice();
//	}
//	 
//}

int cItemManager::FindSalePriceValue()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{

		if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
		{

			int shopIDX = _UI->FindUIIndex("ConsumablesShop");
			RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();
			RECT shopUIRc = _UI->GetVUI()[shopIDX]->GetUIRoot()->GetCollisionRect();
			RECT tempRc;

			if (IntersectRect(&tempRc, &itemRc, &shopUIRc))
			{
				return m_vAllItem[i]->GetBuyPrice();
			}
			else return m_vAllItem[i]->GetSalePrice();
		}
	}

}

const char * cItemManager::FindItemKind()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{

		if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
		{

			int shopIDX = _UI->FindUIIndex("ConsumablesShop");
			RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();
			RECT shopUIRc = _UI->GetVUI()[shopIDX]->GetUIRoot()->GetCollisionRect();
			RECT tempRc;

			if (IntersectRect(&tempRc, &itemRc, &shopUIRc))
			{
				return "구입가격";
			}
			else return "상점매입가";
		}
	}
	
}

void cItemManager::ItemExplaneWindowRender(vItem vPlaceItem)
{
	for (int i = 0; i < vPlaceItem.size(); i++)
	{
		if (vPlaceItem[i]->GetUIRoot()->GetIsCollision())
		{
			if (vPlaceItem == m_vStatusItem && _UI->GetIsCallStatus())	
			if (vPlaceItem == m_vInvenItem && _UI->GetIsCallInven())	
			if (vPlaceItem == m_vShopItem && _UI->GetIsCallShop())		
				
			m_vItemAssistant[0]->Render();
		
		}
	}
}

void cItemManager::CreateItem(const char* itemName, const char* filePath, tagItemKindAndETC itemType, int itemAbility, int itemSalePrice, vItem& vPlaceItem, const char* szParrentName)
{
	//새로운 iteminfo클래스 셋팅
	m_pItemInfo = new cItem;

	//iteminfo에 보내줄 내용의 형식
	tagItemInfo _tagItemInfo;

	_tagItemInfo._itemPath = filePath;
	_tagItemInfo._itemPos = D3DXVECTOR3(0, 0, 0);
	_tagItemInfo._itemName = itemName;
	_tagItemInfo._itemKind = itemType;
	_tagItemInfo._itemAbilityValue = itemAbility;
	_tagItemInfo._itemBuyPrice = itemSalePrice * 5;
	_tagItemInfo._itemSalePrice = itemSalePrice;
	_tagItemInfo._itemParentName = szParrentName;
	
	//아이템인포에 정보를 전달
	m_pItemInfo->Setup(NULL, &_tagItemInfo);

	//this클래스의 벡터에 포인터로 저장
	vPlaceItem.push_back(m_pItemInfo);

	//아이템의 종류가 아닐땐 아이템설명창 정보에 넣어준다.
	if (itemType != NOTANITEM) 
	{

		m_vAllItem.push_back(m_pItemInfo);

		nItemNum += 1;

	}


}

void cItemManager::SetItemSlot(enumSlotType itemSlotType)
{	

	if (itemSlotType == STATUSSLOT)
	{
		tagItemPos _tagItemPos;

		_tagItemPos.SetSlotType(itemSlotType);

		m_vec3StatusPos.push_back(D3DXVECTOR3(63, 184, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(208, 86, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(44, 86, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(188, 184, 0));


		for (int i = 0; i < 4; i++)
		{
			_tagItemPos.vec3Pos = m_vec3StatusPos[i];
			SetRect(&_tagItemPos.rc, m_vec3StatusPos[i].x, m_vec3StatusPos[i].y

				, m_vec3StatusPos[i].x + 37, m_vec3StatusPos[i].y + 37);

			m_vStatusSlot.push_back(_tagItemPos);
		}
	}

	else
	{

		for (int x = 0; x < 7; x++)
		{
			for (int y = 0; y < 8;)
			{
				//아이템아이콘이 위치 정보 작성에 필요한 구조체
				tagItemPos _tagItemPos;

				_tagItemPos.SetSlotType(itemSlotType);

				//꼭짓점을 기준으로 렉트와 위치를 작성
				_tagItemPos.vec2Vertex.x = 18 + 43 * y;
				_tagItemPos.vec2Vertex.y = 79 + 42 * x;

				//UI에서 아이템 배치 간격을 UI에서의 슬롯 간격으로 미리 설정해둔다.
				_tagItemPos.vec2interval.x = 37;
				_tagItemPos.vec2interval.y = 37;

				//위치할곳
				_tagItemPos.vec3Pos = D3DXVECTOR3(_tagItemPos.vec2Vertex.x, _tagItemPos.vec2Vertex.y, 0);


				SetRect(&_tagItemPos.rc
					, _tagItemPos.vec2Vertex.x
					, _tagItemPos.vec2Vertex.y
					, _tagItemPos.vec2Vertex.x + _tagItemPos.vec2interval.x
					, _tagItemPos.vec2Vertex.y + _tagItemPos.vec2interval.y);



				//해당하는 벡터에 담아둔다
				if (itemSlotType == INVENTORY)
				{
					if (x < 5)
					{
						y += 1;
						m_vInvenSlot.push_back(_tagItemPos);
					}
					else break;

				}
				else if (itemSlotType == CONSUMABLESSHOP)
				{
					if (x < 4)
					{
						y += 4;
						m_vShopSlot.push_back(_tagItemPos);
					}
					//else if( x >= 4 && x <= 5) continue;

					else if (x > 4)
					{
						y += 1;
						m_vShopSlot.push_back(_tagItemPos);
					}
					else break;
				}

			}
		}

	}
}


void cItemManager::ItemSlotPosRenewal(enumSlotType itemSlotType, D3DXVECTOR3 placePos)
{
	if (itemSlotType == INVENTORY)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 8; y++)
			{

				m_vInvenSlot[8 * x + y].vec2Vertex.x = placePos.x + 18 + 43 * y;

				m_vInvenSlot[8 * x + y].vec2Vertex.y = placePos.y + 79 + 42 * x;

				m_vInvenSlot[8 * x + y].vec3Pos = D3DXVECTOR3(m_vInvenSlot[8 * x + y].vec2Vertex.x, m_vInvenSlot[8 * x + y].vec2Vertex.y, 0);

				SetRect(&m_vInvenSlot[8 * x + y].rc
					, m_vInvenSlot[8 * x + y].vec2Vertex.x
					, m_vInvenSlot[8 * x + y].vec2Vertex.y
					, m_vInvenSlot[8 * x + y].vec2Vertex.x + m_vInvenSlot[8 * x + y].vec2interval.x
					, m_vInvenSlot[8 * x + y].vec2Vertex.y + m_vInvenSlot[8 * x + y].vec2interval.y);

				
			}
		}
	}

	else if (itemSlotType == CONSUMABLESSHOP)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 2; y++)
			{

				m_vShopSlot[2 * x + y].vec2Vertex.x = placePos.x + 18 + 43 * y * 4;

				m_vShopSlot[2 * x + y].vec2Vertex.y = placePos.y + 79 + 42 * x;

				m_vShopSlot[2 * x + y].vec3Pos = D3DXVECTOR3(m_vShopSlot[2 * x + y].vec2Vertex.x, m_vShopSlot[2 * x + y].vec2Vertex.y, 0);

				SetRect(&m_vShopSlot[2 * x + y].rc
					, m_vShopSlot[2 * x + y].vec2Vertex.x
					, m_vShopSlot[2 * x + y].vec2Vertex.y
					, m_vShopSlot[2 * x + y].vec2Vertex.x + m_vShopSlot[2 * x + y].vec2interval.x
					, m_vShopSlot[2 * x + y].vec2Vertex.y + m_vShopSlot[2 * x + y].vec2interval.y);


			}
		}
		for (int x = 5; x < 7; x++)
		{
			for (int y = 0; y < 8; y++)
			{


				//m_vShopSlot[8 * x + y + 8].vec3Pos = D3DXVECTOR3(100, 100, 0);


				m_vShopSlot[8 * x + y - 32].vec2Vertex.x = placePos.x + 18 + 43 * y;
				m_vShopSlot[8 * x + y - 32].vec2Vertex.y = placePos.y + 79 + 42 * x;
				m_vShopSlot[8 * x + y - 32].vec3Pos = 
					D3DXVECTOR3(m_vShopSlot[8 * x + y - 32].vec2Vertex.x
							  , m_vShopSlot[8 * x + y - 32].vec2Vertex.y
							  , 0);

				SetRect(&m_vShopSlot[8 * x + y - 32].rc
					, m_vShopSlot[8 * x + y - 32].vec2Vertex.x
					, m_vShopSlot[8 * x + y - 32].vec2Vertex.y
					, m_vShopSlot[8 * x + y - 32].vec2Vertex.x + m_vShopSlot[8 * x + y - 32].vec2interval.x
					, m_vShopSlot[8 * x + y - 32].vec2Vertex.y + m_vShopSlot[8 * x + y - 32].vec2interval.y);

			}
		}
	}
	else if (itemSlotType == STATUSSLOT)
	{
		for (int i = 0; i < 4; i++)
		{
			//버텍스는 포즈에서 z만 없는거
			m_vStatusSlot[i].vec3Pos = m_vec3StatusPos[i] + placePos;

			SetRect(&m_vStatusSlot[i].rc,
				m_vStatusSlot[i].vec3Pos.x,
				m_vStatusSlot[i].vec3Pos.y,
				m_vStatusSlot[i].vec3Pos.x + 37,
				m_vStatusSlot[i].vec3Pos.y + 37);
		}
		
	}
}

void cItemManager::MoveFromAToB(vItem& sendItem, vector<tagItemPos>& receivePlace)
{
	
	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{

		for (int i = 0; i < sendItem.size(); i++)
		{
			if (sendItem[i]->GetUIRoot()->GetClickState() == CLICK)
			{
				m_vClickedIndex = i;
			}
			//else if(sendItem[i]->GetUIRoot()->GetClickState() == NON)
			//{
			//	m_vClickedIndex = NONEINDEX;
			//}
		}
	}


	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < receivePlace.size(); i++)
		{
			if (PtInRect(&receivePlace[i].rc, ptMouse))
			{
				//if (m_vClickedIndex != NONEINDEX)
				//{
					//샵에 보낼때
					if (receivePlace[i].GetSlotType() == CONSUMABLESSHOP)
					{					
						m_vShopItem.push_back(sendItem[m_vClickedIndex]);
						//보낸거 지워줌
						sendItem.erase(sendItem.begin() + m_vClickedIndex);
					}

					//인벤에 받을때
					else if (receivePlace[i].GetSlotType() == INVENTORY)
					{
						m_vInvenItem.push_back(sendItem[m_vClickedIndex]);
						sendItem.erase(sendItem.begin() + m_vClickedIndex);
					}

					//장비창에 받을때
					else if (receivePlace[i].GetSlotType() == STATUSSLOT)
					{
						m_vStatusItem.push_back(sendItem[m_vClickedIndex]);
						sendItem.erase(sendItem.begin() + m_vClickedIndex);
					}
				//}
				

			}
		}
	}

}

void cItemManager::ClickUseItemThisPlace(vItem& sendItem, const char* currentPlaceName)
{

	
	int currentPlaceIndex = 0;
	int shopIndex = 0;
	for (int i = 0; i < _UI->GetVUI().size(); i++)
	{
		if (_UI->GetVUI()[i]->GetName() == currentPlaceName)
		{
			currentPlaceIndex = i;
			break;
		}
	}
	//마우스 우클릭시 해당 UI와 충돌을 하면
	RECT rc1 = _UI->GetVUI()[currentPlaceIndex]->GetUIRoot()->GetCollisionRect();
	 

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&rc1, ptMouse))
		{
			for (int i = 0; i < sendItem.size(); i++)
			{
				RECT rc2 = sendItem[i]->GetUIRoot()->GetCollisionRect();
				if (PtInRect(&rc2, ptMouse))
				{				
					if (currentPlaceName == "ConsumablesShop")
					{
						
						if (i < 8)
						{
							if (m_vInvenItem.size() > 39) continue;
							
							if (i % 8 == 0 && m_nGold > 250 )CreateItem("하급회복물약", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vInvenItem), CalculatorGold(-250);
							if (i % 8 == 1 && m_nGold > 500 )CreateItem("중급회복물약", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vInvenItem), CalculatorGold(-500);
							if (i % 8 == 2 && m_nGold > 1000 )CreateItem("상급회복물약", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vInvenItem), CalculatorGold(-1000);
							if (i % 8 == 3 && m_nGold > 300 )CreateItem("하급마나물약", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vInvenItem), CalculatorGold(-300);
							if (i % 8 == 4 && m_nGold > 600)CreateItem("중급마나물약", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vInvenItem), CalculatorGold(-600);
							if (i % 8 == 5 && m_nGold > 1200)CreateItem("상급마나물약", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vInvenItem), CalculatorGold(-1200);
							if (i % 8 == 6 && m_nGold > 1000)CreateItem("미스테리부적", "Texture/ItemIcon/MysteryPaper.png", POTION, 0, 200, m_vInvenItem), CalculatorGold(-1000);
							if (i % 8 == 7 && m_nGold > 2000)CreateItem("마을귀환서", "Texture/ItemIcon/CityRecall.png", POTION, 0, 400, m_vInvenItem), CalculatorGold(-2000);
						}
						else
						{
							m_vInvenItem.push_back(sendItem[i]);
							sendItem.erase(sendItem.begin() + i);
						}
					}
					else
					{
						if (currentPlaceName == "Inventory")
						{
							if (_UI->GetIsCallShop())
							{
								if (m_vShopItem.size() > 23) continue;
								m_vShopItem.push_back(sendItem[i]);
							}
							else
							{							
								//입고있던 아이템의 인덱스를 알아내서 삭제하는 함수
								EquipmentWearBack(sendItem[i]);												
								m_vStatusItem.push_back(sendItem[i]);
								//m_vInvenItem.erase(sendItem.begin() + i);
							}
						}

						if (currentPlaceName == "Status")
						{
							if (m_vInvenItem.size() > 39	||
								sendItem[i]->GetItemKind() == WEAPON) continue;

						
							m_vInvenItem.push_back(sendItem[i]);
						}

						sendItem.erase(sendItem.begin() + i);
					}
				}

									
			}
		}

	}


}

void cItemManager::ConnectNodeCommand()
{
	//텍스트와 아이템 설명창의 연결
	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetParentName() == "ItemExplaneWindow")
		{
			m_vText[i]->ConnectNode(m_vItemAssistant[0]->GetUIRoot());
		}
	}


	//텍스트와 ui의 연결
	for (int i = 0; i < m_vText.size(); i++)
	{
		for (int j = 0; j < _UI->GetVUI().size(); j++)
		{
			if (m_vText[i]->GetParentName() == _UI->GetVUI()[j]->GetName())
			{
				m_vText[i]->ConnectNode(_UI->GetVUI()[j]->GetUIRoot());
			}
		}
	}

	//itemAssistant와 UI의 연결
	for (int i = 0; i < m_vItemAssistant.size(); i++)
	{
		for (int j = 0; j < m_vItemAssistant.size(); j++)
		{
			if (m_vItemAssistant[i]->GetParentName() == m_vItemAssistant[j]->GetName())
			{
				m_vItemAssistant[i]->ConnectNode(m_vItemAssistant[j]->GetUIRoot());
			}
		}
	}


}

void cItemManager::ExceptionsWhileDragging()
{

	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		m_vInvenItem[i]->GetUIImage()->SetIsMove(false);
	}

	for (int i = 0; i < m_vShopItem.size(); i++)
	{
		m_vShopItem[i]->GetUIImage()->SetIsMove(false);
	}

	for (int i = 0; i < m_vStatusItem.size(); i++)
	{
		m_vStatusItem[i]->GetUIImage()->SetIsMove(false);
	}

	int clickedIndex = INDEXOUTOFRANGE;

		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
		{

			//Inven
			for (int i = 0; i < m_vInvenItem.size(); i++)
			{
				//클릭중인 녀석만 clicking
				if (m_vInvenItem[i]->GetUIImage()->GetClickState() == CLICK)clickedIndex = i;

				else
				{
					m_vInvenItem[i]->GetUIImage()->SetClickState(NOTCLICKABLE);


					//UI와의 충돌
					for (int j = 0; j < _UI->GetVUI().size(); j++)
					{


					}
				}

			}

			//Shop
			for (int i = 0; i < m_vShopItem.size(); i++)
			{
				//클릭중인 녀석만 clicking
				if (m_vShopItem[i]->GetUIImage()->GetClickState() == CLICK)clickedIndex = i;

				else
				{
					m_vShopItem[i]->GetUIImage()->SetClickState(NOTCLICKABLE);


					//UI와의 충돌
					for (int j = 0; j < _UI->GetVUI().size(); j++)
					{


					}
				}

			}

		}


		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			//Inven
			//키 해제시 키 상태 모두 NON으로 셋팅
			for (int i = 0; i < m_vInvenItem.size(); i++)
			{
				m_vInvenItem[i]->GetUIImage()->SetClickState(NON);
			}
			//Shop
			for (int i = 0; i < m_vShopItem.size(); i++)
			{
				m_vShopItem[i]->GetUIImage()->SetClickState(NON);			
		}
	}		
}

void cItemManager::SortInSlot()
{
	for (int i = 0; i < m_vStatusItem.size(); i++)
	{
		if (m_vStatusItem[i]->GetItemKind() == SHOES)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[0].vec3Pos);
		
		else if (m_vStatusItem[i]->GetItemKind() == ARMOR)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[1].vec3Pos);

		else if (m_vStatusItem[i]->GetItemKind() == WEAPON)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[2].vec3Pos);

		else if (m_vStatusItem[i]->GetItemKind() == GLOVES)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[3].vec3Pos);

	}

	for (int i = 0; i < m_vShopItem.size(); i++)
	{
		m_vShopItem[i]->TransPos(m_vShopSlot[i].vec3Pos);
	}

	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		m_vInvenItem[i]->TransPos(m_vInvenSlot[i].vec3Pos);
	}



}

void cItemManager::ItemUpdate()
{



	//콜 되었을때 인벤토리 아이템 업데이트
	if (_UI->GetIsCallInven())
	{
		for (int i = 0; i < m_vInvenItem.size(); i++)
		{
			m_vInvenItem[i]->Update();
			
		}
	}

	//상점아이템 업데이트
	if (_UI->GetIsCallShop())
	{
		for (int i = 0; i < m_vShopItem.size(); i++)
		{
			m_vShopItem[i]->Update();
		}
	}

	//스테이터스 업데이트
	if (_UI->GetIsCallStatus())
	{
		for (int i = 0; i < m_vStatusItem.size(); i++)
		{
			m_vStatusItem[i]->Update();
		}
	}



}

void cItemManager::ItemRender()
{

	if (_UI->GetIsCallInven())
	{
		//인벤토리 아이템 렌더
		for (int i = 0; i < m_vInvenItem.size(); i++)
		{
			m_vInvenItem[i]->Render();
		}
	}

	//상점 아이템 렌더
	if (_UI->GetIsCallShop())
	{
		for (int i = 0; i < m_vShopItem.size(); i++)
		{
			m_vShopItem[i]->Render();
		}
	}

	if (_UI->GetIsCallStatus())
	{
		for (int i = 0; i < m_vStatusItem.size(); i++)
		{
			m_vStatusItem[i]->Render();
		}
	}
}

void cItemManager::ItemRenewalThisPlace(vItem& _vVectorName)
{
	for (int i = 0; i < _vVectorName.size(); i++)
	{
		_vVectorName[i]->GetUIImage()->SetAlpha(200);
	}
}

void cItemManager::EquipmentWearBack(cItemInfo* _placeItem)
{
	//스테이터스 슬롯에 있다는것은 장비하고 있다는 뜻
	for (int i = 0; i < m_vStatusItem.size(); i++)
	{

		if (m_vStatusItem[i]->GetItemKind() == _placeItem->GetItemKind())

		{
			m_vInvenItem.push_back(m_vStatusItem[i]);

			m_vStatusItem.erase(m_vStatusItem.begin() + i);
		}
		
	}
}

void cItemManager::SalesItemCalculator()
{
	int saleBT = _UI->FindUIIndex("SaleBT");
	

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		if (_UI->GetIsCallShop() && 
			_UI->GetVUI()[saleBT]->GetUIButtonImage()->GetIsCollision())
		{
			int saleSlot = 8;

			for (int i = saleSlot; i < m_vShopItem.size(); i++)
			{
				CalculatorGold(m_vShopItem[i]->GetSalePrice());
				m_vShopItem.erase(m_vShopItem.begin() + 8, m_vShopItem.end());
			}
		}
	}
}

void cItemManager::ItemExplaneRendingCondition(vItem vPlaceItem)
{
	for (int i = 0; i < vPlaceItem.size(); i++)
	{
		if (vPlaceItem[i]->GetUIRoot()->GetIsCollision())
		{
			if (vPlaceItem == m_vInvenItem && _UI->GetIsCallInven() ||
				vPlaceItem == m_vStatusItem && _UI->GetIsCallStatus() ||
				vPlaceItem == m_vShopItem && _UI->GetIsCallShop())
			{
				isPlaceItemCollision = true;
				m_vItemAssistant[0]->Render();
			}
			else isPlaceItemCollision = false;
		}
	}
}



//특정 UI위치가 바뀌면 그 UI내의 아이템이 옮겨간다
void cItemManager::UIPosRenewal(const char* placeName)
{
	for (int i = 0; i < _UI->GetVUI().size(); i++)
	{
		if (_UI->GetVUI()[i]->GetName() == placeName)
		{
			D3DXVECTOR3 receivePos;
			receivePos.x = _UI->GetVUI()[i]->GetUIRoot()->GetMatWorld()._41;
			receivePos.y = _UI->GetVUI()[i]->GetUIRoot()->GetMatWorld()._42;
			receivePos.z = 0;

			if(placeName == "Inventory")m_vec3RenwalInvenPos = receivePos;
			else if (placeName == "ConsumablesShop")m_vec3RenwalShop = receivePos;
			else if (placeName == "Status")m_vec3RenwalStatus = receivePos;
			
			

		}
	}
}



