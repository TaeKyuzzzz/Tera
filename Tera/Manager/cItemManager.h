#pragma once

enum enumSlotType
{
	INVENTORY,
	CONSUMABLESSHOP,
	STATUSSLOT

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
		SYNTHESIZE(enumSlotType, tagM_SlotType, SlotType);
		
	};

private:
	SINGLETONE(cItemManager);

	SYNTHESIZE(vItem, m_vInvenItem, InvenItem);
	SYNTHESIZE(vItem, m_vShopItem, ShopItem);
	SYNTHESIZE(vItem, m_vStatusItem, StatusItem);
	SYNTHESIZE(vItem, m_vAllItem, AllItem);
	SYNTHESIZE(vItem, m_vItemExplaneWindow, ItemExplaneWindow)


	SYNTHESIZE(vector<tagItemPos>, m_vInvenSlot, VInvenSlot);
	SYNTHESIZE(vector<tagItemPos>, m_vShopSlot, VShopSlot);	
	SYNTHESIZE(vector<tagItemPos>, m_vStatusSlot, VStatusSlot);


	SYNTHESIZE(vector<D3DXVECTOR3>, m_vec3StatusPos, Vec3StatusPos);

	LPD3DXSPRITE		m_pSprite;

	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalInvenPos, Vec3InvenPos);
	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalShop, Vec3Shop);
	SYNTHESIZE(D3DXVECTOR3, m_vec3RenwalStatus, Vec3Status);



	int nItemNum;
	int m_nInvenItemIndex;
	cUIManager*			_UI;
	bool isTemp;
	bool isItemCollision;
	int m_vClickedIndex;
	int m_nWearingIndex;
	HDC hdc;

	SYNTHESIZE(int, m_nitemArrNum, IterArrNum);
	SYNTHESIZE(int, m_nUINum, UINum);
	SYNTHESIZE(int, m_nSlotArrNum, SlotArrNum);

	cItemInfo* m_pItemInfo;

	//일단 골드 여기에 둠 캐릭터 클래스만들기전까지
	SYNTHESIZE(int, m_nGold, Gold);


#pragma region 텍스트관련변수

	SYNTHESIZE(vItem, m_vText, VText);

	//글씨설정할 정보 패키지
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

#pragma region 텍스트관련함수


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
	void ItemExplaneWindowRender(vItem vPlaceItem);

#pragma endregion


	

	inline void GetMemoryLinkUI(cUIManager* UI) { _UI = UI; }
	void CreateItem(const char* itemName, const char* filePath, tagItemKindAndETC itemType, int itemAbility, int itemSalePrice, vItem& vPlaceItem);
	//아이템생성 리스트
	void CreateItemList();
	//아이템이 위치할 슬롯 생성
	void SetItemSlot(enumSlotType itemSlotType);
	//슬롯 위치 갱신
	void UIPosRenewal(const char* placeName);
	void ItemSlotPosRenewal(enumSlotType itemSlotType, D3DXVECTOR3 placePos);
	void MoveFromAToB(vItem& sendItem, vector<tagItemPos>& receivePlace);
	void ClickUseItemThisPlace(vItem& sendItem, const char* currentPlaceName);
	void ConnectNodeCommand();
	

	void ExceptionsWhileDragging();
	void SortInSlot();
	void ItemUpdate();
	void ItemRender();
	void ItemRenewalThisPlace(vItem& _vVectorName);
	void EquipmentWearBack(cItemInfo* _placeItem);
	void SalesItemCalculator();


};

