#include "stdafx.h"
#include "Manager\cItemManager.h"

void cItemManager::CreateItemList()
{
	//������ ����â
	CreateItem("ItemExplaneWindow", "Texture/UIIcon/ItemInfoWindow.png", NOTANITEM, NULL, NULL, m_vItemAssistant);
	CreateItem("Gold", "Texture/UIIcon/Gold.png", NOTANITEM, NULL, NULL, m_vItemAssistant, "ItemExplaneWindow");

#pragma region copyItem
	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", NOTANITEM, 50, 50, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", NOTANITEM, 100, 100, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", NOTANITEM, 150, 200, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", NOTANITEM, 50, 60, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", NOTANITEM, 100, 120, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", NOTANITEM, 150, 240, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", NOTANITEM, 0, 200, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", NOTANITEM, 0, 400, m_vItemImitation, "ItemExplaneWindow");


	CreateItem("���", "Texture/ItemIcon/Claymore.png", NOTANITEM, 15, 200, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", NOTANITEM, 150, 4000, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", NOTANITEM, 100, 3000, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�����", "Texture/ItemIcon/TwohandFish.png", NOTANITEM, 50, 2000, m_vItemImitation, "ItemExplaneWindow");
	//
	//������Ʈ
	CreateItem("���������ǿ�", "Texture/ItemIcon/BlackClothes.png", NOTANITEM, 75, 3600, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("���������ǽŹ�", "Texture/ItemIcon/BlackShoes.png", NOTANITEM, 25, 1400, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�����������尩", "Texture/ItemIcon/BlackGlove.png", NOTANITEM, 20, 1100, m_vItemImitation, "ItemExplaneWindow");

	//������Ʈ
	CreateItem("�����Ƹ�", "Texture/ItemIcon/LeatherClothes.png", NOTANITEM, 50, 2600, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("��������", "Texture/ItemIcon/LeatherShoes.png", NOTANITEM, 15, 1100, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�����۷���", "Texture/ItemIcon/LeatherGlove.png", NOTANITEM, 11, 900, m_vItemImitation, "ItemExplaneWindow");

	//�����÷���Ʈ
	CreateItem("�����÷��Ƹ�", "Texture/ItemIcon/PurpleClothes.png", NOTANITEM, 20, 1000, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�����÷�����", "Texture/ItemIcon/PurpleShoes.png", NOTANITEM, 5, 200, m_vItemImitation, "ItemExplaneWindow");
	CreateItem("�����÷��۷���", "Texture/ItemIcon/PurpleGlove.png", NOTANITEM, 3, 160, m_vItemImitation, "ItemExplaneWindow");
#pragma endregion

	

	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vShopItem);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vShopItem);
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vShopItem);
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vShopItem);
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vShopItem);
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vShopItem);
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200 , m_vShopItem);
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vShopItem);
	
	
	CreateItem("���", "Texture/ItemIcon/Claymore.png", WEAPON, 15, 200, m_vStatusItem);
	CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 4000, m_vInvenItem);
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 3000, m_vInvenItem);
	CreateItem("�����", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50,2000, m_vInvenItem);
	//
	//������Ʈ
	CreateItem("���������ǿ�", "Texture/ItemIcon/BlackClothes.png", ARMOR, 75, 3600, m_vInvenItem);
	CreateItem("���������ǽŹ�", "Texture/ItemIcon/BlackShoes.png", SHOES, 25 , 1400, m_vInvenItem);
	CreateItem("�����������尩", "Texture/ItemIcon/BlackGlove.png", GLOVES, 20, 1100, m_vInvenItem);
	
	//������Ʈ
	CreateItem("�����Ƹ�", "Texture/ItemIcon/LeatherClothes.png", ARMOR, 50, 2600, m_vInvenItem);
	CreateItem("��������", "Texture/ItemIcon/LeatherShoes.png", SHOES, 15, 1100, m_vInvenItem);
	CreateItem("�����۷���", "Texture/ItemIcon/LeatherGlove.png", GLOVES, 11, 900, m_vInvenItem);
	
	//��ī�̼�Ʈ
	CreateItem("�����÷��Ƹ�", "Texture/ItemIcon/PurpleClothes.png", ARMOR, 20, 1000, m_vInvenItem);
	CreateItem("�����÷�����", "Texture/ItemIcon/PurpleShoes.png", SHOES, 5, 200, m_vInvenItem);
	CreateItem("�����÷��۷���", "Texture/ItemIcon/PurpleGlove.png", GLOVES, 3, 160, m_vInvenItem);




	
	
	


}

