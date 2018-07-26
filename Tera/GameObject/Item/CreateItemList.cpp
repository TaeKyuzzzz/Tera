#include "stdafx.h"
#include "Manager\cItemManager.h"

void cItemManager::CreateItemList()
{
	//������ ����â
	CreateItem("ItemExplaneWindow", "Texture/UIIcon/ItemInfoWindow.png", NOTANITEM, NULL, NULL, m_vEtcIcon);
	CreateItem("Gold", "Texture/UIIcon/Gold.png", NOTANITEM, NULL, NULL, m_vEtcIcon, "ItemExplaneWindow");
	CreateItem("SwordDance", "Texture/ItemIcon/SwordDance.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("HitDown", "Texture/ItemIcon/HitDown.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("SideSlash", "Texture/ItemIcon/SideSlash.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("Piercing", "Texture/ItemIcon/Piercing.png", SKILLICON, NULL, NULL, m_vEtcIcon);

#pragma region copyItem
	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", NOTANITEM, 50, 50, m_vItemImitation);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", NOTANITEM, 100, 100, m_vItemImitation);
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", NOTANITEM, 150, 200, m_vItemImitation);
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", NOTANITEM, 50, 60, m_vItemImitation);
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", NOTANITEM, 100, 120, m_vItemImitation);
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", NOTANITEM, 150, 240, m_vItemImitation);
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", NOTANITEM, 0, 200, m_vItemImitation);
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", NOTANITEM, 0, 400, m_vItemImitation);


	CreateItem("���", "Texture/ItemIcon/Claymore.png", NOTANITEM, 15, 200, m_vItemImitation);
	CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", NOTANITEM, 150, 4000, m_vItemImitation);
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", NOTANITEM, 100, 3000, m_vItemImitation);
	CreateItem("����", "Texture/ItemIcon/TwohandFish.png", NOTANITEM, 50, 2000, m_vItemImitation);
	//
	//����Ʈ
	CreateItem("���������ǿ�", "Texture/ItemIcon/BlackClothes.png", NOTANITEM, 75, 3600, m_vItemImitation);
	CreateItem("���������ǽŹ�", "Texture/ItemIcon/BlackShoes.png", NOTANITEM, 25, 1400, m_vItemImitation);
	CreateItem("�����������尩", "Texture/ItemIcon/BlackGlove.png", NOTANITEM, 20, 1100, m_vItemImitation);

	//������Ʈ
	CreateItem("�����Ƹ�", "Texture/ItemIcon/LeatherClothes.png", NOTANITEM, 50, 2600, m_vItemImitation);
	CreateItem("��������", "Texture/ItemIcon/LeatherShoes.png", NOTANITEM, 15, 1100, m_vItemImitation);
	CreateItem("�����۷���", "Texture/ItemIcon/LeatherGlove.png", NOTANITEM, 11, 900, m_vItemImitation);

	//�����÷���Ʈ
	CreateItem("�����÷��Ƹ�", "Texture/ItemIcon/PurpleClothes.png", NOTANITEM, 20, 1000, m_vItemImitation);
	CreateItem("�����÷�����", "Texture/ItemIcon/PurpleShoes.png", NOTANITEM, 5, 200, m_vItemImitation);
	CreateItem("�����÷��۷���", "Texture/ItemIcon/PurpleGlove.png", NOTANITEM, 3, 160, m_vItemImitation);
#pragma endregion

	

	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vConShopItem);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vConShopItem);
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vConShopItem);
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vConShopItem);
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vConShopItem);
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vConShopItem);
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200 , m_vConShopItem);
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vConShopItem);
	
	
	CreateItem("���", "Texture/ItemIcon/Claymore.png", WEAPON, 15, 200, m_vStatusItem);
	CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 4000, m_vConShopItem);
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 3000, m_vInvenItem);
	CreateItem("����", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50,2000, m_vInvenItem);
	//
	//����Ʈ
	CreateItem("���������ǿ�", "Texture/ItemIcon/BlackClothes.png", ARMOR, 75, 3600, m_vConShopItem);
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


