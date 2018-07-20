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

class cUIInfo;

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
	int m_vClickedIndex;
	int m_nWearingIndex;
	HDC hdc;

	SYNTHESIZE(int, m_nitemArrNum, IterArrNum);
	SYNTHESIZE(int, m_nUINum, UINum);
	SYNTHESIZE(int, m_nSlotArrNum, SlotArrNum);

	cItemInfo* m_pItemInfo;


public:

	void Setup();
	void Update();
	void Render();
	void Destroy();

	
	inline void GetMemoryLinkUI(cUIManager* UI) { _UI = UI; }
	void CreateItem(const char* itemName, const char* filePath, tagItemKind itemType, int itemAbility, int itemBuyPrice, int itemSalePrice, vItem& vPlaceItem);
	//아이템생성 리스트
	void CreateItemList();
	//아이템이 위치할 슬롯 생성
	void SetItemSlot(enumSlotType itemSlotType);
	//슬롯 위치 갱신
	void UIPosRenewal(const char* placeName);
	void ItemSlotPosRenewal(enumSlotType itemSlotType, D3DXVECTOR3 placePos);
	void MoveFromAToB(vItem& sendItem, vector<tagItemPos>& receivePlace);
	void ClickUseItemThisPlace(vItem& sendItem, const char* currentPlaceName);

	

	void ExceptionsWhileDragging();
	void SortInSlot();
	void ItemUpdate();
	void ItemRender();
	bool IsCollisionBetweenItemAndMouse();
	void ItemRenewalThisPlace(vItem& _vVectorName);
	void EquipmentWearBack(cItemInfo* _placeItem);


};

