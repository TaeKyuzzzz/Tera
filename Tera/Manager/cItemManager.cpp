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
	//���Ը����
	SetItemSlot(INVENTORY);
	SetItemSlot(CONSUMABLESSHOP);
	SetItemSlot(STATUSSLOT);

	//�����۸�Ͽ� �ִ� ������ �����ϱ�
	CreateItemList();

	ConnectNodeCommand();

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

	//���� �� ����
	SortInSlot();


	//���� ��ҿ� �ִ� ������ ��� ������Ʈ
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
	

	//������ ����â
	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->Update();		
	}
	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->GetUIImage()->SetPosition(D3DXVECTOR3(ptMouse.x + 5, ptMouse.y + 33, 0));
	}





	ItemInfoCTextRenewal("����������");

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
	//	//������ ����â
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

		//������ ����â
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

	//�� ����
	//char szTemp[1024];	
	//sprintf_s(szTemp, 1024, "�κ������۰��� : %d, \n ���â�����۰��� : %d"
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
	//�ش� Ű����� �ؽ�Ʈ�� ���θ� ������ �ε�����ȣ�� ������
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

			//���� ���� ���͸� �����Ͱ����� �°� �������Ѵ�.
			//�� ���� ������ ���͵��߿� ù �ؽ�Ʈ�� �Էµ� ������ ��Ʈ sequence�� �༮�� ã��
			vInt.resize(m_vPreTextIDataPack[UIITextDataIndex(sequence)].size());

			//0���� �ĺ��ڶ� 1������ �ۼ��ϸ�ȴ�.

			// ��ȣ�� 1���϶� �κ��丮 ������ �ؽ�Ʈ
			if (sequence == 1)
			{
				vInt[1] = m_nGold;
				m_vText[i]->GetText()->SetTextIContents(vInt);
			}

			// ��ȣ�� 2�̻��϶� ���������� �ؽ�Ʈ
			else if(sequence == 2)
			{
				vInt[1] = FindAbilityValue();

				vInt[2] = FindSalePriceValue();

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			//�������ͽ� �ؽ�Ʈ
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
						vChar[1] = "��ɾ�����";
					}

					else if (m_vAllItem[i]->GetItemKind() == POTION)
					{
						vChar[1] = "ȸ����";
					}

					else if (m_vAllItem[i]->GetItemKind() == WEAPON)
					{
						vChar[1] = "���ݷ�";
					}

					else
					{
						vChar[1] = "����";
					}

					vChar[2] = "����";

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
		//�ε�������
		if (m_vAllItem[i]->GetUIRoot()->GetIsCollision())
		{
			//�ε��� �༮�� �����Ƽ���� �����Ѵ�.

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
				return "���԰���";
			}
			else return "�������԰�";
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
	//���ο� iteminfoŬ���� ����
	m_pItemInfo = new cItem;

	//iteminfo�� ������ ������ ����
	tagItemInfo _tagItemInfo;

	_tagItemInfo._itemPath = filePath;
	_tagItemInfo._itemPos = D3DXVECTOR3(0, 0, 0);
	_tagItemInfo._itemName = itemName;
	_tagItemInfo._itemKind = itemType;
	_tagItemInfo._itemAbilityValue = itemAbility;
	_tagItemInfo._itemBuyPrice = itemSalePrice * 5;
	_tagItemInfo._itemSalePrice = itemSalePrice;
	_tagItemInfo._itemParentName = szParrentName;
	
	//������������ ������ ����
	m_pItemInfo->Setup(NULL, &_tagItemInfo);

	//thisŬ������ ���Ϳ� �����ͷ� ����
	vPlaceItem.push_back(m_pItemInfo);

	//�������� ������ �ƴҶ� �����ۼ���â ������ �־��ش�.
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
							if (m_vInvenItem.size() > 39) continue;
							
							if (i % 8 == 0 && m_nGold > 250 )CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vInvenItem), CalculatorGold(-250);
							if (i % 8 == 1 && m_nGold > 500 )CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vInvenItem), CalculatorGold(-500);
							if (i % 8 == 2 && m_nGold > 1000 )CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vInvenItem), CalculatorGold(-1000);
							if (i % 8 == 3 && m_nGold > 300 )CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vInvenItem), CalculatorGold(-300);
							if (i % 8 == 4 && m_nGold > 600)CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vInvenItem), CalculatorGold(-600);
							if (i % 8 == 5 && m_nGold > 1200)CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vInvenItem), CalculatorGold(-1200);
							if (i % 8 == 6 && m_nGold > 1000)CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", POTION, 0, 200, m_vInvenItem), CalculatorGold(-1000);
							if (i % 8 == 7 && m_nGold > 2000)CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", POTION, 0, 400, m_vInvenItem), CalculatorGold(-2000);
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
								//�԰��ִ� �������� �ε����� �˾Ƴ��� �����ϴ� �Լ�
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
	//�ؽ�Ʈ�� ������ ����â�� ����
	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetParentName() == "ItemExplaneWindow")
		{
			m_vText[i]->ConnectNode(m_vItemAssistant[0]->GetUIRoot());
		}
	}


	//�ؽ�Ʈ�� ui�� ����
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

	//itemAssistant�� UI�� ����
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

void cItemManager::ItemRenewalThisPlace(vItem& _vVectorName)
{
	for (int i = 0; i < _vVectorName.size(); i++)
	{
		_vVectorName[i]->GetUIImage()->SetAlpha(200);
	}
}

void cItemManager::EquipmentWearBack(cItemInfo* _placeItem)
{
	//�������ͽ� ���Կ� �ִٴ°��� ����ϰ� �ִٴ� ��
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



