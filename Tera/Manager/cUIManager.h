#pragma once

#define UIMANAGER cUIManager::GetInstance()
#include "UI\cUI.h"

struct stRootUIIndex
{
	int Inventory = 0;
	int ConsumablesShop = 0;
	int Status = 0;
};


class cUIInfo;
class cItemManager;
class cUIObject;
class cUIButton;
class cItemInfo;
class cUIImageView;

class cUIManager
{
private:
	typedef vector<cUIInfo*> vUI;

private:
	SINGLETONE(cUIManager);

	SYNTHESIZE(vUI, m_vUI, VUI);

	SYNTHESIZE(vUI, m_vQuickSlot, VQuickSlot);

	SYNTHESIZE(D3DXVECTOR3, m_vInventoryPos, InventoryPos);
	SYNTHESIZE(D3DXVECTOR3, m_vShopPos, ShopPos);
	SYNTHESIZE(int, m_nAlpha, Alpha);

	SYNTHESIZE(bool, m_isCallInven, IsCallInven);
	SYNTHESIZE(bool, m_isCallShop, IsCallShop);
	SYNTHESIZE(bool, m_isCallStatus, IsCallStatus);


	HDC hdc;

	cUIInfo* m_pUIInfo;
	cItemManager* _IM;

	int Index = 0;



public:

	void Setup();
	void Update();
	void Render();
	void Destroy();
	
	
	inline void GetMemoryLinkItem(cItemManager* IM) { _IM = IM; }

	void CreateUI(UIType _UIType, const char* UIName, const char* filePath, D3DXVECTOR3 vec3Pos
		, D3DXVECTOR2 vec2ReduceDragSize = { 1,1 }, const char* UIParentName = NULL);

	void CreateUI(UIType _UIType, const char* UIName, const char* filePath1, const char* filePath2
		, const char* filePath3, D3DXVECTOR3 vec3Pos, const char* UIParentName = NULL);



	void CreateUIList();
	void ConnectNode();
	void CallUIUpdate(const char* UIname);
	void CallUIRender(const char* UIname);
	void CallKeyInput();


	void CloseUI(const char* szUIName);


	void QuickSlotFunc();


	int FindUIRootIndex(const char* szFindIndex);
	

	void UIInfoTextPopUp(int oneValue, const char* szNecessaryPlace = NULL);
	



	//void FindAbilityValue();

};

