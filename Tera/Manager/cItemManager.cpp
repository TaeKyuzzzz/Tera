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
	UITextList();
	
	//���Ը����
	SetItemSlot(INVENTORYSLOT);
	SetItemSlot(CONSHOPSLOT);
	SetItemSlot(STATUSSLOT);
	//SetItemSlot(QUICKSLOT);

	//�����۸�Ͽ� �ִ� ������ �����ϱ�
	CreateItemList();

	

	ConnectNodeCommand();

	CreateImitationImage();

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

	//���־��� UI�� �浹��Ʈ�� ����صΰ� �ʿ��Ҷ����� ���¿뵵
	MainUIInfo();

	//�巡���ϴ� ������ ���ܼ���
	ExceptionsWhileDragging();

	//�����Ҷ� ���� �����۵��� ������ �ո�ŭ �������
	SalesItemCalculator();

	//������ ����â ������Ʈ
	ItemExplaneUpdate();

	//��Ŭ���� �������� ����
	ClickUseItem();

	//�巡�׾ص��
	DragAndDrop();

	//���� �� ����
	SortInSlot();

	//�������� ����Ʈ, ž ��ġ ����
	QuickSlotPosRenewal();

	//������ �������� �������� ����ٴϰ� �������� ������ ��ȣ�� ��� ����
	QuickSlotItemPosRenewal();
	
	//���� ��ҿ� �ִ� ������ ��� ������Ʈ
	ItemUpdate();

	QuickSlotSynchronize();

	for (int i = 0; i < m_vAllItem.size(); i++)
	{
		if (m_vAllItem[i]->GetItemKind() == HPOTION || m_vAllItem[i]->GetItemKind() == MPOTION)
		{
			if (m_vAllItem[i]->GetPotionCount() == 0)
			{
				m_vAllItem.erase(m_vAllItem.begin() + i);
			}
		}
	}

	//char�ؽ�Ʈ�� int�ؽ�Ʈ �ε�
	ItemInfoCTextRenewal("����������");
	for (int i = 1; i < 16; i++)
	{
		ItemInfoITextRenewal(i);
	}

	//QuickSlotSynchronize();
	

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

	
	if (m_vQuickItem.size() != 0)
	{
		//�� ����
		char szTemp[1024];
		//sprintf_s(szTemp, 1024,
		//	"�κ������۰��� : %d, \n ���â�����۰��� : %d, \n �������۰��� : %d, \n ������ �����ܰ��� : %d\n ��ǥ x,y %d \t %d"
		//	, m_vInvenItem.size(), m_vStatusItem.size(), m_vConShopItem.size(), m_vQuickItem.size(),
		//	(int)m_pVec3SlotPos[0].x, (int)m_pVec3SlotPos[0].y);
		sprintf_s(szTemp, 1024, "�������� �������� ���ǰ��� = %d", m_vQuickItem[0]->GetPotionCount());

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
			//�����̱⵵ �ϰ� TEXT�� �����ϴ� ��ȣ�̱⵵ ��
			//TEXT�ϳ��� ���������� ����ص� �����Ͷ� �ΰ��� ������ �� ����
			else if (sequence == 4)
			{
				vInt[1] = FindPotionCount(m_vInvenItem,"�ϱ�ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 5)
			{
				vInt[1] = FindPotionCount(m_vInvenItem, "�߱�ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 6)
			{
				vInt[1] = FindPotionCount(m_vInvenItem, "���ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 7)
			{
				vInt[1] = FindPotionCount(m_vInvenItem, "�ϱ޸�������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 8)
			{
				vInt[1] = FindPotionCount(m_vInvenItem, "�߱޸�������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 9)
			{
				vInt[1] = FindPotionCount(m_vInvenItem, "��޸�������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 10)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "�ϱ�ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 11)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "�߱�ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 12)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "���ȸ������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 13)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "�ϱ޸�������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 14)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "�߱޸�������");

				m_vText[i]->GetText()->SetTextIContents(vInt);
			}
			else if (sequence == 15)
			{
				vInt[1] = FindPotionCount(m_vQuickItem, "��޸�������");

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
				if (m_vAllItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
				{
					vChar[0] = m_vAllItem[i]->GetName();

					if (m_vAllItem[i]->GetItemKind() == ETCCONSUMABLES)
					{
						vChar[1] = "��ɾ�����";
					}

					else if (m_vAllItem[i]->GetItemKind() == HPOTION || m_vAllItem[i]->GetItemKind() == MPOTION)
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
		if (m_vAllItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
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


int cItemManager::FindSalePriceValue()
{
	for (int i = 0; i < m_vAllItem.size(); i++)
	{

		if (m_vAllItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
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
		if (m_vAllItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
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

	RECT explaneRc = m_vEtcIcon[0]->GetUIRoot()->GetCollisionRect();
	m_nExpWidth = explaneRc.right - explaneRc.left;
	m_nExpHeight = explaneRc.bottom - explaneRc.top;

	if(ptMouse.x + m_nExpWidth> WINSIZEX - 100) m_nExpWidth = ptMouse.x + m_nExpWidth - (WINSIZEX - 100);
	else  m_nExpWidth = 0;

	if (ptMouse.y + m_nExpHeight > WINSIZEY - 100) m_nExpHeight = ptMouse.y + m_nExpHeight - (WINSIZEY - 100);
	else  m_nExpHeight = 0;
	


	for (int i = 0; i < m_vItemImitation.size(); i++)
	{
		m_vItemImitation[i]->Update();	
		m_vItemImitation[i]->GetUIImage()->SetPosition(D3DXVECTOR3(ptMouse.x + 27 - m_nExpWidth, ptMouse.y + 35 - m_nExpHeight, 0));
	
	}

	//����â
	m_vEtcIcon[0]->Update();
	m_vEtcIcon[0]->GetUIRoot()->SetPosition(D3DXVECTOR3(ptMouse.x + 20 - m_nExpWidth, ptMouse.y + 20 - m_nExpHeight, 0));
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

		m_vtagItemInfo.push_back(_tagItemInfo);

		//�������Ϳ� ����
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
		
		//�ҼӾ��������κ��� szDestination���� ���
		SendItemAtoPlaceB(m_vInvenItem);
		SendItemAtoPlaceB(m_vConShopItem);
		SendItemAtoPlaceB(m_vStatusItem);
	
		QuickSlotFunc();
	}
}

void cItemManager::ClickUseItem()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{		
		if(_UI->GetIsCallInven() && ClickUseItemThisPlace(m_vInvenItem));
		else if(_UI->GetIsCallStatus() && ClickUseItemThisPlace(m_vStatusItem));
		else if(_UI->GetIsCallConShop() && ClickUseItemThisPlace(m_vConShopItem));		
	}
}

void cItemManager::MovementInQuickSlot()
{

	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		if (m_vQuickItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
		{
			for (int j = 0; j < _UI->GetVQuickSlotUI().size(); j++)
			{
				RECT QSUIRc = _UI->GetVQuickSlotUI()[j]->GetUIImage()->GetResizeRect();
				if (PtInRect(&QSUIRc, ptMouse))
				{
					m_vQuickItem[i]->SetQuickSlotNum(j);
					break;
				}
			}



		}
	}
	/*for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		if (m_vQuickItem[i]->GetUIRoot()->GetIsCollisionPT())
		{
			for (int j = 0; j < _UI->GetVQuickSlotUI().size(); j++)
			{
				RECT UIRc = _UI->GetVQuickSlotUI()[j]->GetUIImage()->GetResizeRect();
				if (PtInRect(&UIRc, ptMouse))
				{
					m_vQuickItem[i]->SetQuickSlotNum(j);
					break;
				}
			}
		}
	}*/


}

void cItemManager::QuickSlotFunc()
{
	QuickSlotRegist();
	if (!SwapInQuickSlot())
	{
		MovementInQuickSlot();
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

	//�ؽ�Ʈ�� �����۰��� ����
	for (int i = 0; i < m_vText.size() - 6; i++)
	{
		for (int j = 0; j < m_vInvenItem.size(); j++)
		{
			if (m_vText[i]->GetParentName() == m_vInvenItem[j]->GetName())
			{
				m_vText[i]->ConnectNode(m_vInvenItem[j]->GetUIRoot());

				m_vText[i]->SetParentName(NULL);
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
}

void cItemManager::ItemUpdate()
{
	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		m_vInvenItem[i]->Update();
	}
	
	for (int i = 0; i < m_vConShopItem.size(); i++)
	{
		m_vConShopItem[i]->Update();
	}	

	for (int i = 0; i < m_vStatusItem.size(); i++)
	{
		m_vStatusItem[i]->Update();
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

	if (_UI->GetIsCallQuickSlot())
	{
		for (int i = 0; i < m_vQuickItem.size(); i++)
		{
			m_vQuickItem[i]->Render();
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
			_UI->GetVUI()[saleBT]->GetUIButtonImage()->GetIsColDragRcAndPT())
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
		if (collisionNum % 8 == 0 && m_nGold > 250 && !FindSamePotion("�ϱ�ȸ������"))					
			CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", HPOTION, 50, 50, m_vInvenItem), CalculatorGold(-250);				
		if (collisionNum % 8 == 1 && m_nGold > 500 && !FindSamePotion("�߱�ȸ������"))
			CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", HPOTION, 100, 100, m_vInvenItem), CalculatorGold(-500);
		if (collisionNum % 8 == 2 && m_nGold > 1000 && !FindSamePotion("���ȸ������"))
			CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", HPOTION, 150, 200, m_vInvenItem), CalculatorGold(-1000);
		if (collisionNum % 8 == 3 && m_nGold > 300 && !FindSamePotion("�ϱ޸�������"))
			CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", MPOTION, 50, 60, m_vInvenItem), CalculatorGold(-300);
		if (collisionNum % 8 == 4 && m_nGold > 600 && !FindSamePotion("�߱޸�������"))
			CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", MPOTION, 100, 120, m_vInvenItem), CalculatorGold(-600);
		if (collisionNum % 8 == 5 && m_nGold > 1200 && !FindSamePotion("��޸�������"))
			CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", MPOTION, 150, 240, m_vInvenItem), CalculatorGold(-1200);
		if (collisionNum % 8 == 6 && m_nGold > 1000 && !FindSamePotion("�̽��׸�����"))
			CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200, m_vInvenItem), CalculatorGold(-1000);
		if (collisionNum % 8 == 7 && m_nGold > 2000 && !FindSamePotion("������ȯ��"))
			CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vInvenItem), CalculatorGold(-2000);

		InvenTextReconnection();
	}
}

void cItemManager::QuickSlotPosRenewal()
{
	for (int i = 0; i < _UI->GetVQuickSlotUI().size(); i++)
	{
		//UI�� ��ġ�� �޾ƿͼ�
		/*quickRc[i] = _UI->GetVQuickSlotUI()[i]->GetUIImage()->GetCollisionRect();*/

		quickRc[i] = _UI->GetVQuickSlotUI()[i]->GetUIImage()->GetResizeRect();
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

void cItemManager::MainUIInfo()
{
	int ShopIdx = _UI->FindUIRootIndex("ConShop");
	int StatusIdx = _UI->FindUIRootIndex("Status");
	int InventoryIdx = _UI->FindUIRootIndex("Inventory");

	tempRc;
	m_ShopRc = _UI->GetVUI()[ShopIdx]->GetUIRoot()->GetCollisionRect();
	m_InvenRc = _UI->GetVUI()[InventoryIdx]->GetUIRoot()->GetCollisionRect();
	m_StatusRc = _UI->GetVUI()[StatusIdx]->GetUIRoot()->GetCollisionRect();

	for (int i = 0; i < _UI->GetVQuickSlotUI().size(); i++)
	{
		m_QuickRc[i] = _UI->GetVQuickSlotUI()[i]->GetUIImage()->GetResizeRect();
	}
}

void cItemManager::PotionOverlap()
{
	//int potionCount = 0;
	//for (int i = 0; i < m_vInvenItem.size(); i++)
	//{
	//	//�����ϰ��
	//	if (m_vInvenItem[i]->GetItemKind() == POTION)
	//	{
	//		//���� ī��Ʈ�� 0�ΰ�쿡��
	//		if (m_vInvenItem[i]->GetPotionCount() == 0)
	//		{

	//			//1�� �������ش�.
	//			m_vInvenItem[i]->SetPotionCount(1);
	//			potionCount += 1;
	//		}
	//	}
	//}





}

bool cItemManager::FindSamePotion(const char* szPotionName)
{
	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		if (m_vInvenItem[i]->GetName() == szPotionName)
		{
			m_vInvenItem[i]->SetPotionCount(m_vInvenItem[i]->GetPotionCount() + 1);
			if(szPotionName == "�ϱ�ȸ������") CalculatorGold(-250);
			else if (szPotionName == "�߱�ȸ������") CalculatorGold(-500);
			else if (szPotionName == "���ȸ������") CalculatorGold(-1000);
			else if (szPotionName == "�ϱ޸�������") CalculatorGold(-300);
			else if (szPotionName == "�߱޸�������") CalculatorGold(-600);
			else if (szPotionName == "��޸�������") CalculatorGold(-1200);

			return true;
		}

	}
	return false;

}

void cItemManager::InvenTextReconnection()
{
	//�ؽ�Ʈ�� �����۰��� ����
	for (int i = 0; i < m_vText.size() - 6; i++)
	{
		for (int j = 0; j < m_vInvenItem.size(); j++)
		{
			if (m_vText[i]->GetParentName() == m_vInvenItem[j]->GetName())
			{
				m_vText[i]->ConnectNode(m_vInvenItem[j]->GetUIRoot());

				m_vText[i]->SetParentName(NULL);
			}
		}
	}
}

void cItemManager::QuickTextReconnection()
{


	for (int i = 10; i < m_vText.size(); i++)
	{
		for (int j = 0; j < m_vQuickItem.size(); j++)
		{
			if (m_vText[i]->GetParentName() == m_vQuickItem[j]->GetName())
			{
				m_vText[i]->ConnectNode(m_vQuickItem[j]->GetUIRoot());

				m_vText[i]->SetParentName(NULL);
			}
		}
	}

}

int cItemManager::SendItemAtoPlaceB(vector<cItemInfo*>& placeItem)
{
	if (placeItem == m_vConShopItem)
		if (!_UI->GetIsCallConShop())return 0;

	if (placeItem == m_vInvenItem)
		if (!_UI->GetIsCallInven())return 0;

	if (placeItem == m_vStatusItem)
		if (!_UI->GetIsCallStatus())return 0;

	vector<cItemInfo*>* vDestination[3];

	vDestination[0] = &m_vConShopItem;
	vDestination[1] = &m_vStatusItem;
	vDestination[2] = &m_vInvenItem;

	RECT UIRc[3];

	UIRc[0] = m_ShopRc;
	UIRc[1] = m_StatusRc;
	UIRc[2] = m_InvenRc;
	
	

	for (int i = 0; i < placeItem.size(); i++)
	{
		if (placeItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
		{
	/*		if (_strnicmp("con", szDestination, 3) == 0) vDestination = &m_vConShopItem;
			else if (_strnicmp("inv", szDestination, 3) == 0) vDestination = &m_vInvenItem;
			else if (_strnicmp("sta", szDestination, 3) == 0) vDestination = &m_vStatusItem;*/

			
			for(int j = 0; j < 3; j++)
			{ 
				if (placeItem == m_vInvenItem && j == 2)continue;
				else if (placeItem == m_vConShopItem && j == 0)continue;
				else if (placeItem == m_vStatusItem && j == 1)continue;


				RECT itemRc = placeItem[i]->GetUIRoot()->GetCollisionRect();

				RECT temp;
				//�������� colRect�� ������ itemRc�� ��Ʈ�� �浹�ϸ�
				if (IntersectRect(&temp, &UIRc[j], &itemRc))
				{
					if (placeItem == m_vStatusItem)ConditionalExcutionWearBack(placeItem[i]);
					else if (placeItem == m_vConShopItem && i < 8)
					{
						BuyConsumables(i);
						return 1;
					}

					if (vDestination[j] == &m_vConShopItem && (*vDestination)[j].size() >= 24)return 1;
					else if (vDestination[j] == &m_vInvenItem && (*vDestination)[j].size() >= 40) return 1;

					(*vDestination)[j].push_back(placeItem[i]);
					placeItem.erase(placeItem.begin() + i);
				}
			}
		}
	}
}

int cItemManager::SendItemAtoPlaceB(vector<cItemInfo*>& placeItem, eSlotType _eSlotType)
{
	RECT QSRc;


	for (int i = 0; i < placeItem.size(); i++)
	{
		if (placeItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
		{

			RECT itemRc = placeItem[i]->GetUIRoot()->GetCollisionRect();

			RECT temp;

			for (int j = 0; j < _UI->GetVQuickSlotUI().size(); j++)
			{
				QSRc = _UI->GetVQuickSlotUI()[j]->GetUIImage()->GetCollisionRect();
				if (IntersectRect(&temp, &QSRc, &itemRc))
				{

					cItemInfo* itemInfo = placeItem[i];
					
					m_vQuickItem.push_back(itemInfo);

					return 1;

				}
			}
			return 0;
		}
	}
}




POINT cItemManager::FindPlaceAndIndex(vector<cItemInfo*> vPlaceItem)
{
	for (int i = 0; i < vPlaceItem.size(); i++)
	{
		if (vPlaceItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
		{
			if (vPlaceItem == m_vInvenItem )return {INVENTORYSLOT, i };
			else if (vPlaceItem == m_vConShopItem)return {CONSHOPSLOT, i };
			else if (vPlaceItem == m_vStatusItem)return {STATUSSLOT, i };
			
		}		
	}
	return { 0,0 };
}

int cItemManager::FindPotionCount(vector<cItemInfo*> vPlaceItem, const char* szName)
{
	for (int i = 0; i < vPlaceItem.size(); i++)
	{		
		if (vPlaceItem[i]->GetName() == szName)
		{
			return vPlaceItem[i]->GetPotionCount();
		}		
	}	
}

void cItemManager::PotionCountTextThisName(const char * szPotionName)
{
	//m_nExcutionNum = POTIONCOUNT;

	CreateUIITextData
	(
		{ m_nExcutionNum , 999 },
		{ { 0,0,0 },{ 25,20,0 } },
		{ SMALL, SMALL },
		{ { 0,0,0 },{ 128,128,128 } }
	);
	tagText t7;
	t7.Type = VARIABLEVALUE;
	t7.nIdentyfyNum = m_nExcutionNum;
	t7.szParrentName = szPotionName;
	CreateText(t7);

	m_nExcutionNum += 1;

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
			if (_UI->GetIsCallConShop())
			{
				if (m_vConShopItem.size() >= 24) return false;
				m_vConShopItem.push_back(sendItem[index]);
			}
			//������ ����â����
			else
			{
				if (sendItem[index]->GetItemKind() == HPOTION || sendItem[index]->GetItemKind() == MPOTION) return false;
			
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

	if (isOptionMode)
	{
		for (int i = 0; i < m_vAllItem.size(); i++)
		{
			if (m_vAllItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
			{
				RECT itemRc = m_vAllItem[i]->GetUIRoot()->GetCollisionRect();

				for (int j = 0; j < _UI->GetVQuickSlotUI().size(); j++)
				{
					
					if ((_UI->GetIsCallConShop() && IntersectRect(&tempRc, &itemRc, &m_ShopRc)) ||
						(_UI->GetIsCallInven() && IntersectRect(&tempRc, &itemRc, &m_InvenRc)) ||
						(_UI->GetIsCallStatus() && IntersectRect(&tempRc, &itemRc, &m_StatusRc)) ||
						(_UI->GetIsCallQuickSlot() && IntersectRect(&tempRc, &itemRc, &m_QuickRc[j])))
					{
						isPlaceItemCollision = true;
						m_vEtcIcon[0]->Render();
						return;
					}
					else isPlaceItemCollision = false;

				}

			}
		}
		
	}	
}

void cItemManager::ImitationIconRender()
{
	if (isOptionMode)
	{
		for (int i = 0; i < m_vItemImitation.size(); i++)
		{
			for (int j = 0; j < m_vAllItem.size(); j++)
			{
				if (m_vAllItem[j]->GetUIRoot()->GetIsColDragRcAndPT())
				{
					if (isPlaceItemCollision)
					{
						if (m_vItemImitation[i]->GetName() == m_vAllItem[j]->GetName())
						{
							m_vItemImitation[i]->Render();
						}

					}
				}
			}
		}
	}
}

void cItemManager::CreateImitationImage()
{
	//������������ ������ ����
	for (int i = 0; i < m_vtagItemInfo.size(); i++)
	{
		m_pItemInfo = new cItem;
		m_pItemInfo->Setup(NULL, &m_vtagItemInfo[i]);
		m_vItemImitation.push_back(m_pItemInfo);
	}
}

int cItemManager::QuickSlotRegist()
{
	

	int itemIdx = INDEXNOTSET;
	int quickIdx = INDEXNOTSET;

	//���콺 ������ �����۰� ���콺�� �浹���̰�
	//�װ��� �� �����԰��� �浹���϶� ������ �ε����� ������ �ε����� �˾Ƴ�
	for (int i = 0; i < m_vInvenItem.size(); i++)
	{
		for (int j = 0; j < _UI->GetVQuickSlotUI().size(); j++)
		{
			if (m_vInvenItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
			{ 			
				if (PtInRect(&_UI->GetVQuickSlotUI()[j]->GetUIImage()->GetCollisionRect(), ptMouse))
				{
					for (int k = 0; k < m_vQuickItem.size(); k++)
					{
						if (m_vQuickItem[k]->GetQuickSlotNum() == j)
						{
							m_vQuickItem.erase(m_vQuickItem.begin() + k);
						}
					}


					itemIdx = i;
					quickIdx = j;
				}			
			}										
		}		
	}
	//�浹���� �ʾҴٸ� �ʱⰪ �״���̹Ƿ� ������
	if (itemIdx == INDEXNOTSET) return 0;

	//char str[20] = "C";


	
	//char str[2] = "C";
	
	//vector<tagItemInfo> vItemInfoTemp;
	//
	//vItemInfoTemp = m_vtagItemInfo;

	for (int k = 0; k < m_vtagItemInfo.size(); k++)
	{
	
		//vChar.push_back((char)str);
		
		if (m_vInvenItem[itemIdx]->GetQuickSlotNum() == INDEXNOTSET && m_vInvenItem[itemIdx]->GetName() == m_vtagItemInfo[k]._itemName)
		{
			m_pItemInfo = new cItem;

		//	char szTemp[20];

		//	sprintf_s(szTemp, 20, "%s%s", vItemInfoTemp[k]._itemName, m_szStr);


			//strcat((char*)m_vtagItemInfo[k]._itemName, vChar[k]);
		//	vItemInfoTemp[k]._itemName = szTemp;

			m_pItemInfo->Setup(NULL, &m_vtagItemInfo[k]);
			m_vAllItem.push_back(m_pItemInfo);
			m_vQuickItem.push_back(m_pItemInfo);
			m_vInvenItem[itemIdx]->SetQuickSlotNum(quickIdx);
			m_vQuickItem.back()->SetQuickSlotNum(quickIdx);
			QuickTextReconnection();
			//InvenTextReconnection();
			return 1;
		}
	}


}

bool cItemManager::SwapInQuickSlot()
{
	RECT itemA;
	RECT itemB;

	int QSNumA;
	int QSNumB;


	//�������� �������߿� ���õ� �༮�� A
	//�����۳��� �浹������
	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		for (int j = 0; j < m_vQuickItem.size(); j++)
		{
			if (j != i)
			{

				if (m_vQuickItem[j]->GetUIRoot()->GetIsColDragRcAndPT() &&
					m_vQuickItem[i]->GetUIRoot()->GetIsColDragRcAndPT())
				{
					QSNumA = m_vQuickItem[i]->GetQuickSlotNum();
					QSNumB = m_vQuickItem[j]->GetQuickSlotNum();

					m_vQuickItem[i]->SetQuickSlotNum(QSNumB);
					m_vQuickItem[j]->SetQuickSlotNum(QSNumA);

					return true;
				}

			}
		}
	}
	return false;
}

void cItemManager::QuickSlotSynchronize()
{
	for (int i = 0; i < m_vQuickItem.size(); i++)
	{
		for (int j = 0; j < m_vInvenItem.size(); j++)
		{
			if (m_vQuickItem[i]->GetItemKind() == HPOTION || m_vQuickItem[i]->GetItemKind() == MPOTION)
			{
				if (m_vQuickItem[i]->GetName() == m_vInvenItem[j]->GetName())
				{
					m_vQuickItem[i]->SetPotionCount(m_vInvenItem[j]->GetPotionCount());

					break;
				}
			}
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
			else if (placeName == "ConShop")m_vec3RenwalShop = receivePos;
			else if (placeName == "Status")m_vec3RenwalStatus = receivePos;
			
			

		}
	}
}



