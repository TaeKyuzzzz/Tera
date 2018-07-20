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
class cUITextView;
class cUIButton;
class cItemInfo;

class cUIManager
{
private:
	typedef vector<cUIInfo*> vUI;

private:
	SINGLETONE(cUIManager);

	SYNTHESIZE(vUI, m_vUI, VUI);
	SYNTHESIZE(vUI, m_vText, VText);

	SYNTHESIZE(D3DXVECTOR3, m_vInventoryPos, InventoryPos);
	SYNTHESIZE(D3DXVECTOR3, m_vShopPos, ShopPos);
	SYNTHESIZE(int, m_nAlpha, Alpha);

	SYNTHESIZE(bool, m_isCallInven, IsCallInven);
	SYNTHESIZE(bool, m_isCallShop, IsCallShop);
	SYNTHESIZE(bool, m_isCallStatus, IsCallStatus);
	SYNTHESIZE(bool, m_isItemInfoOutPut, ItemInfoOutPut);

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
	
	SYNTHESIZE(int, m_nGold, Gold);

	map<const char*, const char*> textExplane;

	cItemManager* _IM;
	
	cUIInfo* m_pUIInfo;

	int inven, shop, status;


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

	void CreateText(tagText _tagText);

	void CreateUIList();
	void ConnectNode();
	void CallUIUpdate(const char* UIname);
	void CallUIRender(const char* UIname);
	void CallKeyInput();

	void CreateUICTextData(vTextCContents _vTextCContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor);
	void CreateUIITextData(vTextIContents _vTextIContents, vTextPos _vTextPos, vTextSize _vTextSize, vTextColor _vTextColor);
	int UICTextDataIndex(const char* titleName);
	int UIITextDataIndex(int variableName);

	void CloseUI(const char* szUIName);

	//추가하는곳 UITextData.cpp에 작성했음
	void UITextList();
	void ItemInfoITextRenewal(int sequence);
	void ItemInfoCTextRenewal(const char* szFindText);

	int FindUIIndex(const char* szFindIndex);
	void UIInfoTextPopUp(const char* szFindIndex = NULL);
	
	int FindAbilityValue();

	void CalculatorGold(int Price) { m_nGold += Price; }
	void TextExplane();

	const char* FindExplane();

	//void FindAbilityValue();

};

