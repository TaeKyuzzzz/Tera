#pragma once

#define SLOTTYPEMAX 4

enum eSlotType
{
	INVENTORYSLOT = 1,
	CONSHOPSLOT,
	STATUSSLOT,
	QUICKSLOT

};

#define ITEMMANAGER	cItemManager::GetInstance()

class cItemInfo;
class cItem;
class cUIObject;
class cUIImageView;
class cUIManager;
class cUIButton;
class cUIInfo;
class cUITextView;

#define INVENTORYNUMMAX 40



class cItemManager
{
private:
	typedef vector<cItemInfo*> vItem;
	typedef vector<cItemInfo> vItem2;



	struct tagItemPos
	{

		RECT rc;
		D3DXVECTOR3 vec3Pos;
		D3DXVECTOR2 vec2Vertex;
		D3DXVECTOR2 vec2interval;
		SYNTHESIZE(eSlotType, tagM_SlotType, SlotType);
		
	};

private:
	SINGLETONE(cItemManager);

	SYNTHESIZE(vItem, m_vInvenItem, InvenItem);
	SYNTHESIZE(vItem, m_vConShopItem, ConShopItem);
	SYNTHESIZE(vItem, m_vStatusItem, StatusItem);
	SYNTHESIZE(vItem, m_vQuickItem, QuickItem);

	SYNTHESIZE(vItem, m_vAllItem, AllItem);
	SYNTHESIZE(vItem, m_vEtcIcon, EtcIcon);
	SYNTHESIZE(vItem, m_vItemImitation, ItemImitation);
	


	SYNTHESIZE(vector<tagItemPos>, m_vInvenSlot, VInvenSlot);
	SYNTHESIZE(vector<tagItemPos>, m_vShopSlot, VShopSlot);	
	SYNTHESIZE(vector<tagItemPos>, m_vStatusSlot, VStatusSlot);
	SYNTHESIZE(vector<tagItemPos>, m_vQuickSlot, QuickSlot);

	SYNTHESIZE(vector<D3DXVECTOR3>, m_vec3StatusPos, Vec3StatusPos);

	LPD3DXSPRITE		m_pSprite;

	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalInvenPos, Vec3InvenPos);
	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalShop, Vec3Shop);
	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalStatus, Vec3Status);



	int nItemNum;
	int m_nInvenItemIndex;
	cUIManager*			_UI;
	bool isTemp;
	bool isPlaceItemCollision;
	int m_vClickedIndex;
	int m_nWearingIndex;
	HDC hdc;
	RECT tempRc;
	RECT quickRc[16];
	int m_nItemNum[16];
	int m_nSlotNum[16];

	D3DXVECTOR3 m_pVec3SlotPos[16];

	SYNTHESIZE(int, m_nitemArrNum, IterArrNum);
	SYNTHESIZE(int, m_nUINum, UINum);
	SYNTHESIZE(int, m_nSlotArrNum, SlotArrNum);

	SYNTHESIZE(int, m_nAttackValue, AttackValue);
	SYNTHESIZE(int, m_nDefenceValue, DefenceValue);

	cItemInfo* m_pItemInfo;

	//�ϴ� ��� ���⿡ �� ĳ���� Ŭ���������������
	SYNTHESIZE(int, m_nGold, Gold);


#pragma region �ؽ�Ʈ���ú���

	SYNTHESIZE(vItem, m_vText, VText);

	//�۾������� ���� ��Ű��
	SYNTHESIZE(vector<vTextCContents>, m_vPreTextCDataPack, PreTextCDataPack);
	SYNTHESIZE(vector<vTextPos>, m_vPreTextCPosPack, PreTextCPosPack);
	SYNTHESIZE(vector<vTextSize>, m_vPreTextCSizePack, PreTextCSizePack);
	SYNTHESIZE(vector<vTextColor>, m_vPreTextCColorPack, PreTextCColorPack);

	SYNTHESIZE(vector<vTextIContents>, m_vPreTextIDataPack, PreTextIDataPack);
	SYNTHESIZE(vector<vTextPos>, m_vPreTextIPosPack, PreTextIPosPack);
	SYNTHESIZE(vector<vTextSize>, m_vPreTextISizePack, PreTextISizePack);
	SYNTHESIZE(vector<vTextColor>, m_vPreTextIColorPack, PreTextIColorPack);

	SYNTHESIZE(vTextCContents, m_vPreCText, PreCText);
	SYNTHESIZE(vTextIContents, m_vPreIText, PreIText);

	SYNTHESIZE(vTextPos, m_vTextPos, TextPos);

	map<const char*, const char*> textExplane;
	cItemInfo* m_pItemTextInfo;
	SYNTHESIZE(bool, m_isItemExplaneOutPut, ItemExplaneOutPut);

#pragma endregion

	


public:

	void Setup();
	void Update();
	void Render();
	void Destroy();

	
	void CalculatorGold(int Price) { m_nGold += Price; }

#pragma region �ؽ�Ʈ�����Լ�


	void CreateText(tagText _tagText);
	void CreateUICTextData(vTextCContents _vTextCContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor);
	void CreateUIITextData(vTextIContents _vTextIContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor);
	int UICTextDataIndex(const char* titleName);
	int UIITextDataIndex(int variableName);
	void ItemInfoITextRenewal(int sequence);
	void ItemInfoCTextRenewal(const char* szFindText);
	void UITextList();
	void TextExplane();
	int FindAbilityValue();
	int FindItemExplaneWndIndex(const char* szItemExplaneName);
	int FindSalePriceValue();
	const char* FindItemPos();
	void ItemExplaneUpdate();
	void ItemExplaneRender();
	void ImitationIconRender();


#pragma endregion


	

	inline void GetMemoryLinkUI(cUIManager* UI) { _UI = UI; }
	void CreateItem(const char* itemName, const char* filePath, tagItemKindAndETC itemType, int itemAbility, int itemSalePrice, vItem& vPlaceItem, const char* szParrentName = NULL);
	//�����ۻ��� ����Ʈ
	void CreateItemList();
	//�������� ��ġ�� ���� ����
	void SetItemSlot(eSlotType itemSlotType);
	//���� ��ġ ����
	void UIPosRenewal(const char* placeName);
	void ItemSlotPosRenewal(eSlotType itemSlotType, D3DXVECTOR3 placePos);	
	void ClickUseItemThisPlace(vItem& sendItem, const char* currentPlaceName);
	void ConnectNodeCommand();
	void ExceptionsWhileDragging();
	void SortInSlot();
	void ItemUpdate();
	void ItemRender();
	void ItemRenewalThisPlace(vItem& _vVectorName);
	void EquipmentWearBack(cItemInfo* _placeItem);
	void SalesItemCalculator();
	void BuyConsumables(int collisionNum);
	void SetSkillSlot();
	void QuickSlotItemPosRenewal();
	void DragAndDrop();
	void SendItemAtoPlaceB(vector<cItemInfo*>& placeItem, const char* szPlaceName);



};

