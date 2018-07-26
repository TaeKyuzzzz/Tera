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
	
}

void cItemManager::Setup()
{
	hdc = GetDC(g_hWnd);

	UITextList();
	
	//���Ը����
	SetItemSlot(INVENTORYSLOT);
	SetItemSlot(CONSHOPSLOT);
	SetItemSlot(STATUSSLOT);
	//SetItemSlot(QUICKSLOT);

	//�����۸�Ͽ� �ִ� ������ �����ϱ�
	CreateItemList();

	ConnectNodeCommand();

}

void cItemManager::Update()
{



	//������ ������ �ִ� UI�� ��ġ�� �����Ͽ�
	//������ ��ġ�� ���Ž����ش�.
	UIPosRenewal("Inventory");
	ItemSlotPosRenewal(INVENTORYSLOT, m_vec3RenwalInvenPos);
	UIPosRenewal("ConShop");
	ItemSlotPosRenewal(CONSHOPSLOT, m_vec3RenwalShop);
	UIPosRenewal("Status");
	ItemSlotPosRenewal(STATUSSLOT, m_vec3RenwalStatus);


	
	//�巡���ϴ� ������ ���ܼ���
	ExceptionsWhileDragging();

	

	/*ClickUseItemThisPlace(m_vInvenItem, "Inventory");
	ClickUseItemThisPlace(m_vStatusItem, "Status");
	ClickUseItemThisPlace(m_vConShopItem, "ConShop");*/



	SalesItemCalculator();

	//������ ����â ������Ʈ
	ItemExplaneUpdate();

	ClickUseItem();

	DragAndDrop();
	
	SetSkillSlot();

	//���� �� ����
	SortInSlot();


	QuickSlotItemPosRenewal();
	
	//���� ��ҿ� �ִ� ������ ��� ������Ʈ
	ItemUpdate();

	//MoveFromAToB3();
	
	//char�ؽ�Ʈ�� int�ؽ�Ʈ �ε�
	ItemInfoCTextRenewal("����������");
	for (int i = 1; i < 4; i++)
	{
		ItemInfoITextRenewal(i);
	}


}

void cItemManager::Render()
{
	ItemRender();	

	ItemExplaneRender();	

	ImitationIconRender();

	for (int i = 0; i < m_vText.size(); i++)
	{
		m_vText[i]->Render();
	}

	
	//RECT rc = _UI->GetVUI()[0]->GetUIRoot()->GetCollisionRect();

	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	


	//�� ����
	char szTemp[1024];	
	sprintf_s(szTemp, 1024, 
		"�κ������۰��� : %d, \n ���â�����۰��� : %d, \n �������۰��� : %d, \n ������ �����ܰ��� : %d"/*, \n ��ǥ x,y %d \t %d"*/
		, m_vInvenItem.size(), m_vStatusItem.size(), m_vConShopItem.size(), m_vQuickItem.size()/*, 
		(int)m_vInvenItem[0]->GetUIRoot()->GetPosition().x, (int)m_vInvenItem[0]->GetUIRoot()->GetPosition().y*/);
	RECT rc2;
	SetRect(&rc2, 100, 200, 800, 400);
	LPD3DXFONT pFont = FONTMANAGER->GetFont(cFontManager::FT_GA_BIG);
	pFont->DrawTextA(NULL,
		szTemp,
		strlen(szTemp),
		&rc2,
		DT_LEFT | DT_TOP,
		D3DCOLOR_XRGB(255, 255, 0));


	
}

void cItemManager::Destroy()
{
	SAFE_DELETE(m_pItemTextInfo);

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
				if (m_vAllItem[i]->GetUIRoot()->GetIsCollisionPT())
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

					vChar[4] = FindItemPos();
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
		if (m_vAllItem[i]->GetUIRoot()->GetIsCollisionPT())
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
//		if(vPlaceItem == m_vConShopItem) return vPlaceItem[i]->GetBuyPrice();
//		else return vPlaceItem[i]->GetSalePrice();
//	}
//	 
//}

int cItemManager::FindSalePriceValue()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{

		if (m_vAllItem[i]->GetUIRoot()->GetIsCollisionPT())
		{

			int shopIDX = _UI->FindUIRootIndex("ConShop");
			RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();
			RECT shopUIRc = _UI->GetVUI()[shopIDX]->GetUIRoot()->GetCollisionRect();
			RECT tempRc;

			RECT shopUIRcResize;
			SetRect(&shopUIRcResize,
				shopUIRc.left,
				shopUIRc.top,
				shopUIRc.right,
				shopUIRc.bottom * 3 / 4);

			if (IntersectRect(&tempRc, &itemRc, &shopUIRcResize))
			{
				return m_vAllItem[i]->GetBuyPrice();
			}
			else return m_vAllItem[i]->GetSalePrice();
		}
	}

}

const char * cItemManager::FindItemPos()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		if (m_vAllItem[i]->GetUIRoot()->GetIsCollisionPT())
		{

			int shopIDX = _UI->FindUIRootIndex("ConShop");
			RECT shopUIRc = _UI->GetVUI()[shopIDX]->GetUIRoot()->GetCollisionRect();

			RECT shopUIRcResize;
			SetRect(&shopUIRcResize,
				shopUIRc.left,
				shopUIRc.top,
				shopUIRc.right,
				shopUIRc.bottom * 3 / 4);
			
			RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();
			
			RECT tempRc;
			

			if (_UI->GetIsCallConShop() && IntersectRect(&tempRc, &itemRc, &shopUIRcResize))
			{
				return "���԰���";
			}
			else return "�������԰�";
		}
	}
	
}

void cItemManager::ItemExplaneUpdate()
{


	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->Update();	
		m_vItemImitation[i]->GetUIImage()->SetPosition(D3DXVECTOR3(ptMouse.x + 27, ptMouse.y + 35, 0));
	
	}

	//����â
	m_vEtcIcon[0]->Update();
	m_vEtcIcon[0]->GetUIRoot()->SetPosition(D3DXVECTOR3(ptMouse.x + 20, ptMouse.y + 20, 0));
	m_vEtcIcon[1]->GetUIImage()->SetPosition(D3DXVECTOR3(110, 200, 0));
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

	//�������� ������ �ƴҶ� �������Ϳ� ���� �ʴ´�.
	if (itemType != NOTANITEM) 
	{

		m_vAllItem.push_back(m_pItemInfo);

		nItemNum += 1;

	}


}

void cItemManager::SetItemSlot(eSlotType itemSlotType)
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

	//else if (itemSlotType == QUICKSLOT)
	//{
	//	tagItemPos _tagItemPos;


	//}

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
				if (itemSlotType == INVENTORYSLOT)
				{
					if (x < 5)
					{
						y += 1;
						m_vInvenSlot.push_back(_tagItemPos);
					}
					else break;

				}
				else if (itemSlotType == CONSHOPSLOT)
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


void cItemManager::ItemSlotPosRenewal(eSlotType itemSlotType, D3DXVECTOR3 placePos)
{
	if (itemSlotType == INVENTORYSLOT)
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

	else if (itemSlotType == CONSHOPSLOT)
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

void cItemManager::DragAndDrop()
{
	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{
		//Ű�����ÿ� ���콺�� �������� �浹���϶�
		//�ٸ����� ��������

		SendItemAtoPlaceB(m_vInvenItem, "con");
		SendItemAtoPlaceB(m_vInvenItem, "sta");
		SendItemAtoPlaceB(m_vConShopItem, "inv");
		SendItemAtoPlaceB(m_vConShopItem, "sta");
		SendItemAtoPlaceB(m_vStatusItem, "inv");
		SendItemAtoPlaceB(m_vStatusItem, "con");

	}



}

void cItemManager::ClickUseItem()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{		
		if(ClickUseItemThisPlace(m_vInvenItem));
		else if(ClickUseItemThisPlace(m_vStatusItem));
		else if(ClickUseItemThisPlace(m_vConShopItem));		
	}
}

void cItemManager::ConnectNodeCommand()
{
	//�ؽ�Ʈ�� ������ ����â�� ����
	for (int i = 0; i < m_vText.size(); i++)
	{
		if (m_vText[i]->GetParentName() == "ItemExplaneWindow")
		{
			m_vText[i]->ConnectNode(m_vEtcIcon[0]->GetUIRoot());
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

	//itemAssistant������ ����
	for (int i = 0; i < m_vEtcIcon.size(); i++)
	{
		for (int j = 0; j < m_vEtcIcon.size(); j++)
		{
			if (m_vEtcIcon[i]->GetParentName() == m_vEtcIcon[j]->GetName())
			{
				m_vEtcIcon[i]->ConnectNode(m_vEtcIcon[j]->GetUIRoot());
			}
		}
	}

	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		for (int j = 0; j < m_vEtcIcon.size(); j++)
		{
			if (m_vItemImitation[i]->GetParentName() == m_vEtcIcon[j]->GetName())
			{
				m_vItemImitation[i]->ConnectNode(m_vEtcIcon[j]->GetUIRoot());
			}
		}
	}


}

void cItemManager::ExceptionsWhileDragging()
{



	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		for (int j = 0; j < m_vAllItem.size(); j++)
		{
			m_vAllItem[i]->GetUIRoot()->SetIsMove(false);

			if (m_vAllItem[i]->GetUIRoot()->GetClickState() == CLICK)
			{
				if(i != j)m_vAllItem[j]->GetUIRoot()->SetClickState(UNMOVABLE);
			}
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < m_vAllItem.size(); i++)
		{
			m_vAllItem[i]->GetUIRoot()->SetClickState(NON);
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

	for (int i = 0; i < m_vConShopItem.size(); i++)
	{
		m_vConShopItem[i]->TransPos(m_vShopSlot[i].vec3Pos);
	}

	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		m_vInvenItem[i]->TransPos(m_vInvenSlot[i].vec3Pos);
	}

	//for (int i = 0; i < m_vQuickItem.size(); i++)
	//{
	//	m_vQuickItem[i]->TransPos(m_pVec3SlotPos[i]);
	//}



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
	if (_UI->GetIsCallConShop())
	{
		for (int i = 0; i < m_vConShopItem.size(); i++)
		{
			m_vConShopItem[i]->Update();
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

	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		m_vQuickItem[i]->Update();
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
	if (_UI->GetIsCallConShop())
	{
		for (int i = 0; i < m_vConShopItem.size(); i++)
		{
			m_vConShopItem[i]->Render();
		}
	}

	if (_UI->GetIsCallStatus())
	{
		for (int i = 0; i < m_vStatusItem.size(); i++)
		{
			m_vStatusItem[i]->Render();
		}
	}

	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		m_vQuickItem[i]->Render();
	}
}

void cItemManager::ItemRenewalThisPlace(vItem& _vVectorName)
{
	for (int i = 0; i < _vVectorName.size(); i++)
	{
		_vVectorName[i]->GetUIImage()->SetAlpha(200);
	}
}

void cItemManager::ConditionalExcutionWearBack(cItemInfo* _newWear)
{
	//�������ͽ� ���Կ� �ִٴ°��� ����ϰ� �ִٴ� ��
	for (int i = 0; i < m_vStatusItem.size(); i++)
	{

		if (m_vStatusItem[i]->GetItemKind() == _newWear->GetItemKind())

		{
			m_vInvenItem.push_back(m_vStatusItem[i]);

			m_vStatusItem.erase(m_vStatusItem.begin() + i);
		}
		
	}
}

void cItemManager::SalesItemCalculator()
{
	int saleBT = _UI->FindUIRootIndex("SaleBT");
	

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		if (_UI->GetIsCallConShop() && 
			_UI->GetVUI()[saleBT]->GetUIButtonImage()->GetIsCollisionPT())
		{
			int saleSlot = 8;

			int countItem = m_vConShopItem.size();

			for (int i = saleSlot; i < countItem; i++)
			{
				CalculatorGold(m_vConShopItem[i]->GetSalePrice());				
			}
			m_vConShopItem.erase(m_vConShopItem.begin() + 8, m_vConShopItem.end());
		}
	}
}

void cItemManager::BuyConsumables(int collisionNum)
{
	if (m_vInvenItem.size() <= 39)
	{
		if (collisionNum % 8 == 0 && m_nGold > 250)CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vInvenItem), CalculatorGold(-250);
		if (collisionNum % 8 == 1 && m_nGold > 500)CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vInvenItem), CalculatorGold(-500);
		if (collisionNum % 8 == 2 && m_nGold > 1000)CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vInvenItem), CalculatorGold(-1000);
		if (collisionNum % 8 == 3 && m_nGold > 300)CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vInvenItem), CalculatorGold(-300);
		if (collisionNum % 8 == 4 && m_nGold > 600)CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vInvenItem), CalculatorGold(-600);
		if (collisionNum % 8 == 5 && m_nGold > 1200)CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vInvenItem), CalculatorGold(-1200);
		if (collisionNum % 8 == 6 && m_nGold > 1000)CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200, m_vInvenItem), CalculatorGold(-1000);
		if (collisionNum % 8 == 7 && m_nGold > 2000)CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vInvenItem), CalculatorGold(-2000);
	}
}

void cItemManager::SetSkillSlot()
{
	for (int i = 0; i < _UI->GetVQuickSlotUI().size(); i++)
	{
		//UI�� ��ġ�� �޾ƿͼ�
		quickRc[i] = _UI->GetVQuickSlotUI()[i]->GetUIImage()->GetCollisionRect();

		//��� ���ŵǴ� ��ġ
		//16
		m_pVec3SlotPos[i].x = quickRc[i].left;
		m_pVec3SlotPos[i].y = quickRc[i].top;
		m_pVec3SlotPos[i].z = 0;
	}



}

void cItemManager::QuickSlotItemPosRenewal()
{
	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		m_vQuickItem[i]->TransPos(m_pVec3SlotPos[m_vQuickItem[i]->GetQuickSlotNum()]);
	}
}

void cItemManager::SendItemAtoPlaceB(vector<cItemInfo*>& placeItem, const char* szPlaceName)
{
	int UIIdx = _UI->FindUIRootIndex(szPlaceName);

	vector<cItemInfo*>* vDestination = NULL;

	

	RECT UIRc = _UI->GetVUI()[UIIdx]->GetUIRoot()->GetCollisionRect();

	for (int i = 0; i < placeItem.size(); i++)
	{
		if (placeItem[i]->GetUIRoot()->GetIsCollisionPT())
		{
			if (_strnicmp("con", szPlaceName, 3) == 0) vDestination = &m_vConShopItem;
			else if (_strnicmp("inv", szPlaceName, 3) == 0) vDestination = &m_vInvenItem;
			else if (_strnicmp("sta", szPlaceName, 3) == 0) vDestination = &m_vStatusItem;

			

			RECT itemRc = placeItem[i]->GetUIRoot()->GetCollisionRect();

			RECT temp;
			if (IntersectRect(&temp, &UIRc, &itemRc))
			{
				if(placeItem == m_vStatusItem) ConditionalExcutionWearBack(placeItem[i]);

				(*vDestination).push_back(placeItem[i]);
				placeItem.erase(placeItem.begin() + i);
			}
		}
	}
}

POINT cItemManager::FindPlaceAndIndex(vector<cItemInfo*> vPlaceItem)
{
	for (int i = 0; i < vPlaceItem.size(); i++)
	{
		if (vPlaceItem[i]->GetUIRoot()->GetIsCollisionPT())
		{
			if (vPlaceItem == m_vInvenItem )return {INVENTORYSLOT, i };
			else if (vPlaceItem == m_vConShopItem)return {CONSHOPSLOT, i };
			else if (vPlaceItem == m_vStatusItem)return {STATUSSLOT, i };
			
		}		
	}
	return { 0,0 };
}

bool cItemManager::ClickUseItemThisPlace(vector<cItemInfo*>& sendItem)
{
	if (FindPlaceAndIndex(sendItem).x != 0)
	{
		int index;

		//�� �Լ����� �� �ε���
		index = FindPlaceAndIndex(sendItem).y;
	
		
		//�κ��� �������ΰ��
		if (sendItem == m_vInvenItem)
		{	//������ ���̸� ��������
			if (_UI->GetIsCallConShop())	m_vConShopItem.push_back(sendItem[index]);
			//������ ����â����
			else
			{
			
				ConditionalExcutionWearBack(sendItem[index]);
				m_vStatusItem.push_back(sendItem[index]);
				
			}
			//������ ����
			sendItem.erase(sendItem.begin() + index);
		}
		else if (sendItem == m_vConShopItem)
		{
			if (index < 8)
			{
				BuyConsumables(index);
			}
			else
			{
				m_vInvenItem.push_back(sendItem[index]);
				sendItem.erase(sendItem.begin() + index);
			}
		}
		else if (sendItem == m_vStatusItem)
		{
			if (sendItem[index]->GetItemKind() == WEAPON) return false;
			
			m_vInvenItem.push_back(sendItem[index]);
			sendItem.erase(sendItem.begin() + index);
		}

		return true;
	}
	else return false;



}


void cItemManager::ItemExplaneRender()
{

	int ShopIdx = _UI->FindUIRootIndex("ConShop");
	int StatusIdx = _UI->FindUIRootIndex("Status");
	int InventoryIdx = _UI->FindUIRootIndex("Inventory");

	
	RECT tempRc;
	RECT shopRc = _UI->GetVUI()[ShopIdx]->GetUIRoot()->GetCollisionRect();
	RECT invenRc = _UI->GetVUI()[InventoryIdx]->GetUIRoot()->GetCollisionRect();
	RECT statusRc = _UI->GetVUI()[StatusIdx]->GetUIRoot()->GetCollisionRect();

	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		if (m_vAllItem[i]->GetUIRoot()->GetIsCollisionPT())
		{
			RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();

			if ((_UI->GetIsCallConShop() && IntersectRect(&tempRc, &itemRc, &shopRc))||
				(_UI->GetIsCallInven() && IntersectRect(&tempRc, &itemRc, &invenRc))||
				(_UI->GetIsCallStatus() && IntersectRect(&tempRc, &itemRc, &statusRc)))
			{
				isPlaceItemCollision = true;
				m_vEtcIcon[0]->Render();
			}
			else isPlaceItemCollision = false;
	
		}
		
	}	
}

void cItemManager::ImitationIconRender()
{
	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		for (int j = 0; j < m_vAllItem.size(); j++)
		{
			if (m_vAllItem[j]->GetUIRoot()->GetIsCollisionPT())
			{
				if (isPlaceItemCollision)
				{
					if (m_vItemImitation[i]->GetName() == m_vAllItem[j]->GetName())
					{
						m_vItemImitation[i]->Render();
					}
					//else m_vItemImitation[i]->GetUIRoot()->SetAlpha(0);
				}
			}
		}
	}

	//for (int i = 0; i < m_vItemImitation.size(); i++)
	//{
	//	for (int j = 0; j < m_vAllItem.size(); j++)
	//	{

	//		if (isPlaceItemCollision)
	//		{
	//			if (m_vItemImitation[i]->GetName() == m_vAllItem[j]->GetName())
	//			{
	//				//m_vItemImitation[i]->Render();
	//			}
	//		}

	//	}
	//}

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
			else if (placeName == "ConShop")m_vec3RenwalShop = receivePos;
			else if (placeName == "Status")m_vec3RenwalStatus = receivePos;
			
			

		}
	}
}



