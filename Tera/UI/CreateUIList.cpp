#include "stdafx.h"
#include "Manager/cUIManager.h"

void cUIManager::CreateUIList()
{


	//인벤토리
	CreateUI(WINDOW, "Inventory", "Texture/UIIcon/Inven.png", D3DXVECTOR3(1100, 100, 0), D3DXVECTOR2(0.8,0.1));
	CreateUI(BUTTON, "closeIdleI", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vInventoryPos.x + 340, m_vInventoryPos.y + 5, 0), "Inventory");
	CreateUI(WINDOW, "Pocket", "Texture/UIIcon/InvenPocket2.png", D3DXVECTOR3(m_vInventoryPos.x - 20, m_vInventoryPos.y - 10, 0), { -1,-1 }, "Inventory");
	CreateUI(WINDOW, "Gold", "Texture/UIIcon/Gold.png", D3DXVECTOR3(155, 333, 0), { -1, -1 }, "Inventory");
	
	//상점
	CreateUI(WINDOW, "ConsumablesShop", "Texture/UIIcon/Shop.png", D3DXVECTOR3(600, 200, 0), D3DXVECTOR2(0.8, 0.1));
	CreateUI(WINDOW, "ConsumablesIcon", "Texture/UIIcon/ConsumablesShopIcon.png", D3DXVECTOR3(m_vShopPos.x - 20, m_vShopPos.y - 20, 0), { -1,-1 }, "ConsumablesShop");
	CreateUI(BUTTON, "closeIdleC", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vShopPos.x + 340, m_vShopPos.y + 5, 0), "ConsumablesShop");
	CreateUI(BUTTON, "SaleBT", "Texture/UIIcon/TotalSalesAmountIdle.png", "Texture/UIIcon/Texture/UIIcon/TotalSalesAmountOver.png"
		, "Texture/UIIcon/Texture/UIIcon/TotalSalesAmountDown.png", D3DXVECTOR3(m_vShopPos.x + 300, m_vShopPos.y + 255, 0), "ConsumablesShop");

	//장비창
	CreateUI(WINDOW, "Status", "Texture/UIIcon/EquipmentWindow.png", D3DXVECTOR3(200, 200, 0), D3DXVECTOR2(0.8, 0.1));
	CreateUI(BUTTON, "closeIdleS", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vShopPos.x + 255, m_vShopPos.y + 3, 0), "Status");
	CreateUI(WINDOW, "EquipmentPort", "Texture/UIIcon/EquipmentPort.png", D3DXVECTOR3(-50, -50, 0), { -1,-1 }, "Status");

	CreateUI(WINDOW, "ItemInfoWindow", "Texture/UIIcon/ItemInfoWindow.png", D3DXVECTOR3(800, 800, 0));

}


