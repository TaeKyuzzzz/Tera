#include "stdafx.h"
#include "cItemManager.h"
#include "GameObject/Item/cItem.h"
#include "UI\cUIObject.h"
#include "UI/cUIInfo.h"
#include "UI/cUIImageView.h"



cItemManager::cItemManager()
	:nItemNum(0)
	, isTemp(false)
	, m_vClickedIndex(0)
{

}


cItemManager::~cItemManager()
{
	
}

void cItemManager::Setup()
{

	hdc = GetDC(g_hWnd);
	//슬롯만들기
	SetItemSlot(INVENTORY);
	SetItemSlot(CONSUMABLESSHOP);
	SetItemSlot(STATUSSLOT);

	//아이템목록에 있는 아이템 생성하기
	CreateItemList();
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

	if (IsCollisionBetweenItemAndMouse())_UI->SetItemInfoOutPut(true);
	
	else _UI->SetItemInfoOutPut(false);
	
}

void cItemManager::Render()
{
	ItemRender();	

	//for (int i = 0; i < m_vStatusSlot.size(); i++)
	//{
	//	Rectangle(hdc, m_vStatusSlot[i].rc.left, m_vStatusSlot[i].rc.top, m_vStatusSlot[i].rc.right, m_vStatusSlot[i].rc.bottom);
	//}
}

void cItemManager::Destroy()
{
	SAFE_DELETE(m_pItemInfo);
}







void cItemManager::CreateItem(const char* itemName, const char* filePath, tagItemKind itemType, int itemAbility, int itemBuyPrice, int itemSalePrice, vItem& vPlaceItem)
{
	//새로운 iteminfo클래스 셋팅
	m_pItemInfo = new cItem;

	//iteminfo에 보내줄 내용의 형식
	tagItemInfo _tagItemInfo;

	_tagItemInfo._itemPath = filePath;
	_tagItemInfo._itemPos = D3DXVECTOR3(0,0,0);
	_tagItemInfo._itemName = itemName;
	_tagItemInfo._itemKind = itemType;
	_tagItemInfo._itemAbilityValue = itemAbility;
	_tagItemInfo._itemBuyPrice = itemBuyPrice;
	_tagItemInfo._itemSalePrice = itemSalePrice;
	//_tagItemInfo._itemExplain;

	//아이템인포에 정보를 전달
	m_pItemInfo->Setup(&_tagItemInfo);
	//this클래스의 벡터에 포인터로 저장
	vPlaceItem.push_back(m_pItemInfo);

	m_vAllItem.push_back(m_pItemInfo);


	nItemNum += 1;

}

void cItemManager::SetItemSlot(enumSlotType itemSlotType)
{	

	if (itemSlotType == STATUSSLOT)
	{
		tagItemPos _tagItemPos;

		_tagItemPos.SetSlotType(itemSlotType);

		m_vec3StatusPos.push_back(D3DXVECTOR3(63, 183, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(208, 86, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(44, 86, 0));
		m_vec3StatusPos.push_back(D3DXVECTOR3(188, 184, 0));
		//m_vec3StatusPos.push_back(D3DXVECTOR3())


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
							
							if (i % 8 == 0 && _UI->GetGold() > 250 )CreateItem("하급회복물약", "Texture/ItemIcon/HPSmall.png", POTION, 50, 250, 50, m_vInvenItem), _UI->CalculatorGold(-250);
							if (i % 8 == 1 && _UI->GetGold() > 500 )CreateItem("중급회복물약", "Texture/ItemIcon/HPMid.png", POTION, 100, 500, 100, m_vInvenItem), _UI->CalculatorGold(-500);
							if (i % 8 == 2 && _UI->GetGold() > 1000 )CreateItem("상급회복물약", "Texture/ItemIcon/HPBig.png", POTION, 150, 1000, 200, m_vInvenItem), _UI->CalculatorGold(-1000);
							if (i % 8 == 3 && _UI->GetGold() > 300 )CreateItem("하급마나물약", "Texture/ItemIcon/MPSmall.png", POTION, 50, 300, 60, m_vInvenItem), _UI->CalculatorGold(-300);
							if (i % 8 == 4 && _UI->GetGold() > 600)CreateItem("중급마나물약", "Texture/ItemIcon/MPMid.png", POTION, 100, 600, 120, m_vInvenItem), _UI->CalculatorGold(-600);
							if (i % 8 == 5 && _UI->GetGold() > 1200)CreateItem("상급마나물약", "Texture/ItemIcon/MPBig.png", POTION, 150, 1200, 240, m_vInvenItem), _UI->CalculatorGold(-1200);
							if (i % 8 == 6 && _UI->GetGold() > 1000)CreateItem("미스테리부적", "Texture/ItemIcon/MysteryPaper.png", POTION, 0, 1000, 200, m_vInvenItem), _UI->CalculatorGold(-1000);
							if (i % 8 == 7 && _UI->GetGold() > 2000)CreateItem("마을귀환서", "Texture/ItemIcon/CityRecall.png", POTION, 0, 2000, 400, m_vInvenItem), _UI->CalculatorGold(-2000);
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
								m_vInvenItem.erase(sendItem.begin() + i);
							}
						}

						if (currentPlaceName == "Status")
						{
							if (m_vStatusItem.size() > 3) continue;
							m_vInvenItem.push_back(sendItem[i]);
						}

						sendItem.erase(sendItem.begin() + i);
					}
				}

									
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
		if (m_vStatusItem[i]->GetAbility()._tagItemKind == SHOES)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[0].vec3Pos);
		
		else if (m_vStatusItem[i]->GetAbility()._tagItemKind == ARMOR)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[1].vec3Pos);

		else if (m_vStatusItem[i]->GetAbility()._tagItemKind == WEAPON)
			m_vStatusItem[i]->TransPos(m_vStatusSlot[2].vec3Pos);

		else if (m_vStatusItem[i]->GetAbility()._tagItemKind == GLOVES)
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

bool cItemManager::IsCollisionBetweenItemAndMouse()
{

	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		if(m_vAllItem[i]->GetUIRoot()->GetIsCollision())
		return true;
	}
	return false;
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

		if (m_vStatusItem[i]->GetAbility()._tagItemKind == _placeItem->GetAbility()._tagItemKind)

		{
			m_vInvenItem.push_back(m_vStatusItem[i]);

			m_vStatusItem.erase(m_vStatusItem.begin() + i);
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



