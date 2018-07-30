#include "stdafx.h"
#include "Manager/cUIManager.h"

void cUIManager::CreateUIList()
{


	//인벤토리
	CreateUI(WINDOW, "Inventory", "Texture/UIIcon/Inven.png", D3DXVECTOR3(1100, 100, 0), D3DXVECTOR2(0.8,0.1));
	CreateUI(BUTTON, "closeI", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vInventoryPos.x + 340, m_vInventoryPos.y + 5, 0), "Inventory");
	CreateUI(WINDOW, "Pocket", "Texture/UIIcon/InvenPocket2.png", D3DXVECTOR3(m_vInventoryPos.x - 20, m_vInventoryPos.y - 10, 0), { -1,-1 }, "Inventory");
	CreateUI(WINDOW, "Gold", "Texture/UIIcon/Gold.png", D3DXVECTOR3(155, 333, 0), { -1, -1 }, "Inventory");
	
	//상점
	CreateUI(WINDOW, "ConShop", "Texture/UIIcon/Shop.png", D3DXVECTOR3(600, 200, 0), D3DXVECTOR2(0.8, 0.1));
	CreateUI(WINDOW, "ConsumablesIcon", "Texture/UIIcon/ConsumablesShopIcon.png", D3DXVECTOR3(m_vShopPos.x - 20, m_vShopPos.y - 20, 0), { -1,-1 }, "ConShop");
	CreateUI(BUTTON, "closeC", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vShopPos.x + 340, m_vShopPos.y + 5, 0), "ConShop");
	CreateUI(BUTTON, "SaleBT", "Texture/UIIcon/TotalSalesAmountIdle.png", "Texture/UIIcon/TotalSalesAmountOver.png"
		, "Texture/UIIcon/TotalSalesAmountDown.png", D3DXVECTOR3(m_vShopPos.x + 300, m_vShopPos.y + 255, 0), "ConShop");

	//장비창
	CreateUI(WINDOW, "Status", "Texture/UIIcon/EquipmentWindow.png", D3DXVECTOR3(200, 200, 0), D3DXVECTOR2(0.8, 0.1));
	CreateUI(BUTTON, "closeS", "Texture/UIIcon/closeIdle.png", "Texture/UIIcon/closeOver.png", "Texture/UIIcon/closeDown.png",
		D3DXVECTOR3(m_vShopPos.x + 255, m_vShopPos.y + 3, 0), "Status");
	CreateUI(WINDOW, "EquipmentPort", "Texture/UIIcon/EquipmentPort.png", D3DXVECTOR3(-50, -50, 0), { -1,-1 }, "Status");




	CreateUI(WINDOW, "QSDRAGZONE", "Texture/UIIcon/DragZone.png", D3DXVECTOR3(340, 730, 0), { 1,1 });
	CreateUI(BUTTON, "QSSKILLLOCK", "Texture/UIIcon/SkillLock.png", "Texture/UIIcon/SkillLockUp.png", "Texture/UIIcon/SkillKey.png"
		, D3DXVECTOR3(-17, 17, 0), "QSDRAGZONE");



	for (int i = 0; i < 16; i++)
	{
		szDragZone[i] = "QSDragZone";
		szSkillSlot[i] = "QSSkillSlot";

		_itoa(i, szNum, 10);

		szDragZone[i] += szNum;
		szSkillSlot[i] += szNum;

		szDragZoneC = szDragZone[i].c_str();
		szSkillSlotC = szSkillSlot[i].c_str();

		CreateUI(WINDOW, szDragZoneC, "Texture/UIIcon/DragZone.png", D3DXVECTOR3((i+1) * 50 - 11, -3, 0), { 1,1 }, "QSDRAGZONE");
		CreateUI(WINDOW, szSkillSlotC, "Texture/UIIcon/SkillSlot.png", D3DXVECTOR3(-8, 20, 0), { -1,-1 }, szDragZoneC);
		CreateUI(BUTTON, "QSKeyChangeBT", "Texture/UIIcon/KeyChangeIdle.png", "Texture/UIIcon/KeyChangeOver.png",
			"Texture/UIIcon/KeyChangeOver.png", D3DXVECTOR3(22, 0, 0), szDragZoneC);

	}




	//CreateUI(WINDOW, "SkillWnd", "Texture/UIIcon/SkillWnd.png", D3DXVECTOR3(100, 100, 0), D3DXVECTOR2(0.8, 0.1));
	


	


}


