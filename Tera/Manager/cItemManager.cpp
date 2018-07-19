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
	//���Ը����
	SetItemSlot(INVENTORY);
	SetItemSlot(CONSUMABLESSHOP);
	SetItemSlot(STATUSSLOT);

	//�����۸�Ͽ� �ִ� ������ �����ϱ�
	CreateItemList();
	
	//for (int i = 0; i < 8; i++)
	//{
	//	m_vShopItem.push_back(m_vItem[0]);
	//	m_vShopServeItem.push_back(m_vShopItem[i]);
	//
	//	m_vItem.erase(m_vItem.begin());
	//}
	//
	//for (int i = 0; i < 12; i++)
	//{
	//	m_vInvenItem.push_back(m_vItem[0]);
	//	m_vItem.erase(m_vItem.begin());
	//}
	
	
	
	

	
}

void cItemManager::Update()
{
	//������ ������ �ִ� UI�� ��ġ�� �����Ͽ�
	//������ ��ġ�� ���Ž����ش�.
	UIPosRenewal("Inventory");
	ItemSlotPosRenewal(INVENTORY, m_vec3RenwalInvenPos);
	UIPosRenewal("ConsumablesShop");
	ItemSlotPosRenewal(CONSUMABLESSHOP, m_vec3RenwalShop);
	UIPosRenewal("Status");
	ItemSlotPosRenewal(STATUSSLOT, m_vec3RenwalStatus);

	//�巡���ϴ� ������ ���ܼ���
	ExceptionsWhileDragging();

	ItemRenewalThisPlace(m_vInvenItem);
	ItemRenewalThisPlace(m_vShopItem);
	ItemRenewalThisPlace(m_vStatusItem);


	//���� �� ����
	SortInSlot();




	//���� ��ҿ� �ִ� ������ ��� ������Ʈ
	ItemUpdate();



	MoveFromAToB(m_vInvenItem, m_vShopSlot);
	MoveFromAToB(m_vShopItem, m_vInvenSlot);
	MoveFromAToB(m_vInvenItem, m_vStatusSlot);

	
	ClickUseItemThisPlace(m_vInvenItem, "Inventory");
	ClickUseItemThisPlace(m_vStatusItem, "Status");
	ClickUseItemThisPlace(m_vShopItem, "ConsumablesShop");

	if (CollisionBetweenItemAndMouse(m_vInvenItem) || CollisionBetweenItemAndMouse(m_vShopItem) || CollisionBetweenItemAndMouse(m_vStatusItem))
		_UI->SetItemInfoOutPut(true);
	else _UI->SetItemInfoOutPut(false);
	
}

void cItemManager::Render()
{
	ItemRender();


	//for (int i = 0; i < m_vStatusSlot.size(); i++)
	//{
	//	Rectangle(hdc, m_vStatusSlot[i].rc.left, m_vStatusSlot[i].rc.top, m_vStatusSlot[i].rc.right, m_vStatusSlot[i].rc.bottom);
	//
	//	char szTemp[1024];
	//	//sprintf_s(szTemp, 1024, "x = %d \t y = %d", (int)m_vInvenItem[1]->GetUIRoot()->GetPosition().x, (int)m_vInvenItem[1]->GetUIRoot()->GetPosition().y);
	//	sprintf_s(szTemp, 1024, "%d", (int)i);
	//	RECT rc[4];
	//	SetRect(&rc[i], (int)m_vStatusSlot[i].vec3Pos.x
	//		, (int)m_vStatusSlot[i].vec3Pos.y
	//		, (int)m_vStatusSlot[i].vec3Pos.x + 400
	//		, (int)m_vStatusSlot[i].vec3Pos.y + 400);
	//
	//	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, { 30, 20 });
	//	pFont->DrawTextA(NULL,
	//		szTemp,
	//		strlen(szTemp),
	//		&rc[i],
	//		DT_LEFT | DT_TOP,
	//		D3DCOLOR_XRGB(255, 255, 0));
	//	pFont->Release();
	//
	//}

	
		char szTemp[1024];
		sprintf_s(szTemp, 1024, "Size = %d", m_vShopItem.size());


		RECT rc;
		SetRect(&rc,
			300
			, 300
			, 2000
			, 2000);

		LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, { 30, 20 });
		pFont->DrawTextA(NULL,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP,
			D3DCOLOR_XRGB(255, 255, 0));
		pFont->Release();
	
	
}







void cItemManager::CreateItem(const char* itemName, const char* filePath, tagItemKind itemType, int itemAbility, int itemBuyPrice, int itemSalePrice, vItem& vPlaceItem)
{
	//���ο� iteminfoŬ���� ����
	cItemInfo* _itemInfo = new cItem;

	//iteminfo�� ������ ������ ����
	tagItemInfo _tagItemInfo;

	_tagItemInfo._itemPath = filePath;
	_tagItemInfo._itemPos = m_vInvenSlot[nItemNum].vec3Pos;
	_tagItemInfo._itemName = itemName;
	_tagItemInfo._itemKind = itemType;
	_tagItemInfo._itemAbilityValue = itemAbility;
	_tagItemInfo._itemBuyPrice = itemBuyPrice;
	_tagItemInfo._itemSalePrice = itemSalePrice;
	//_tagItemInfo._itemExplain;

	//������������ ������ ����
	_itemInfo->Setup(&_tagItemInfo);
	//thisŬ������ ���Ϳ� �����ͷ� ����
	vPlaceItem.push_back(_itemInfo);

	nItemNum += 1;

}

void cItemManager::SetItemSlot(enumSlotType itemSlotType)
{	

	if (itemSlotType == STATUSSLOT)
	{
		tagItemPos _tagItemPos;

		_tagItemPos.SetSlotType(itemSlotType);

		m_vec3StatusPos.push_back(D3DXVECTOR3(125, 36, 0));
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
				//�����۾������� ��ġ ���� �ۼ��� �ʿ��� ����ü
				tagItemPos _tagItemPos;

				_tagItemPos.SetSlotType(itemSlotType);

				//�������� �������� ��Ʈ�� ��ġ�� �ۼ�
				_tagItemPos.vec2Vertex.x = 18 + 43 * y;
				_tagItemPos.vec2Vertex.y = 79 + 42 * x;

				//UI���� ������ ��ġ ������ UI������ ���� �������� �̸� �����صд�.
				_tagItemPos.vec2interval.x = 37;
				_tagItemPos.vec2interval.y = 37;

				//��ġ�Ұ�
				_tagItemPos.vec3Pos = D3DXVECTOR3(_tagItemPos.vec2Vertex.x, _tagItemPos.vec2Vertex.y, 0);


				SetRect(&_tagItemPos.rc
					, _tagItemPos.vec2Vertex.x
					, _tagItemPos.vec2Vertex.y
					, _tagItemPos.vec2Vertex.x + _tagItemPos.vec2interval.x
					, _tagItemPos.vec2Vertex.y + _tagItemPos.vec2interval.y);



				//�ش��ϴ� ���Ϳ� ��Ƶд�
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
			//���ؽ��� ����� z�� ���°�
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
					//���� ������
					if (receivePlace[i].GetSlotType() == CONSUMABLESSHOP)
					{					
						m_vShopItem.push_back(sendItem[m_vClickedIndex]);
						//������ ������
						sendItem.erase(sendItem.begin() + m_vClickedIndex);
					}

					//�κ��� ������
					else if (receivePlace[i].GetSlotType() == INVENTORY)
					{
						m_vInvenItem.push_back(sendItem[m_vClickedIndex]);
						sendItem.erase(sendItem.begin() + m_vClickedIndex);
					}

					//���â�� ������
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
	//���콺 ��Ŭ���� �ش� UI�� �浹�� �ϸ�
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

							
							if (i % 8 == 0 && _UI->GetGold() > 250 )CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", CONSUMABLES, 50, 250, 50, m_vInvenItem), _UI->CalculatorGold(-250);
							if (i % 8 == 1 && _UI->GetGold() > 500 )CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", CONSUMABLES, 100, 500, 100, m_vInvenItem), _UI->CalculatorGold(-500);
							if (i % 8 == 2 && _UI->GetGold() > 1000 )CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", CONSUMABLES, 150, 1000, 200, m_vInvenItem), _UI->CalculatorGold(-1000);
							if (i % 8 == 3 && _UI->GetGold() > 300 )CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", CONSUMABLES, 50, 300, 60, m_vInvenItem), _UI->CalculatorGold(-300);
							if (i % 8 == 4 && _UI->GetGold() > 600)CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", CONSUMABLES, 100, 600, 120, m_vInvenItem), _UI->CalculatorGold(-600);
							if (i % 8 == 5 && _UI->GetGold() > 1200)CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", CONSUMABLES, 150, 1200, 240, m_vInvenItem), _UI->CalculatorGold(-1200);
							if (i % 8 == 6 && _UI->GetGold() > 1000)CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", CONSUMABLES, 0, 1000, 200, m_vInvenItem), _UI->CalculatorGold(-1000);
							if (i % 8 == 7 && _UI->GetGold() > 2000)CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", CONSUMABLES, 0, 2000, 400, m_vInvenItem), _UI->CalculatorGold(-2000);
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
							if (_UI->GetIsCallShop())m_vShopItem.push_back(sendItem[i]);
							else m_vStatusItem.push_back(sendItem[i]);
						}

						if (currentPlaceName == "Status") m_vInvenItem.push_back(sendItem[i]);

						sendItem.erase(sendItem.begin() + i);
					}
				}

									
			}
		}

	}


}

void cItemManager::ExceptionsWhileDragging()
{
	//������ �������� �巡�׾� ����� ��Ȯ�� ������ġ�� ������Ű�� ���� false�μ���
	for (int i = 0; i < m_vItem.size(); i++)
	{
		m_vItem[i]->GetUIImage()->SetIsMove(false);
	}

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
				//Ŭ������ �༮�� clicking
				if (m_vInvenItem[i]->GetUIImage()->GetClickState() == CLICK)clickedIndex = i;

				else
				{
					m_vInvenItem[i]->GetUIImage()->SetClickState(NOTCLICKABLE);


					//UI���� �浹
					for (int j = 0; j < _UI->GetVUI().size(); j++)
					{


					}
				}

			}

			//Shop
			for (int i = 0; i < m_vShopItem.size(); i++)
			{
				//Ŭ������ �༮�� clicking
				if (m_vShopItem[i]->GetUIImage()->GetClickState() == CLICK)clickedIndex = i;

				else
				{
					m_vShopItem[i]->GetUIImage()->SetClickState(NOTCLICKABLE);


					//UI���� �浹
					for (int j = 0; j < _UI->GetVUI().size(); j++)
					{


					}
				}

			}

		}


		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			//Inven
			//Ű ������ Ű ���� ��� NON���� ����
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

		if (m_vStatusItem[i]->GetAbility()._tagItemKind == ARMOR)
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
	//�����۵� ������Ʈ
	for (int i = 0; i < m_vItem.size(); i++)
	{
		m_vItem[i]->Update();
	}


	//�� �Ǿ����� �κ��丮 ������ ������Ʈ
	if (_UI->GetIsCallInven())
	{
		for (int i = 0; i < m_vInvenItem.size(); i++)
		{
			m_vInvenItem[i]->Update();
			
		}
	}

	//���������� ������Ʈ
	if (_UI->GetIsCallShop())
	{
		for (int i = 0; i < m_vShopItem.size(); i++)
		{
			m_vShopItem[i]->Update();
		}
	}

	//�������ͽ� ������Ʈ
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
	for (int i = 0; i < m_vItem.size(); i++)
	{
		m_vItem[i]->Render();
	}
	if (_UI->GetIsCallInven())
	{
		//�κ��丮 ������ ����
		for (int i = 0; i < m_vInvenItem.size(); i++)
		{
			m_vInvenItem[i]->Render();
		}
	}

	//���� ������ ����
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

bool cItemManager::CollisionBetweenItemAndMouse(vItem& _vVectorName)
{

	for (int i = 0; i < _vVectorName.size(); i++)
	{
		if(_vVectorName[i]->GetUIRoot()->GetIsCollision())
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



//Ư�� UI��ġ�� �ٲ�� �� UI���� �������� �Űܰ���
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



