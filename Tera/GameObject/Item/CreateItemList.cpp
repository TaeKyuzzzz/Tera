#include "stdafx.h"
#include "Manager\cItemManager.h"

void cItemManager::CreateItemList()
{
	//������ ����â
	CreateItem("ItemExplaneWindow", "Texture/UIIcon/ItemInfoWindow.png", NOTANITEM, NULL, NULL, m_vEtcIcon);
	CreateItem("Gold", "Texture/UIIcon/Gold.png", NOTANITEM, NULL, NULL, m_vEtcIcon, "ItemExplaneWindow");
	CreateItem("�ٶ�������", "Texture/ItemIcon/SwordDance.png", SKILLICON, 250, 20000, m_vQuickItem);
	CreateItem("����ġ��", "Texture/ItemIcon/HitDown.png", SKILLICON, 200, 10000, m_vQuickItem);
	CreateItem("��������", "Texture/ItemIcon/SideSlash.png", SKILLICON, 225, 15000, m_vQuickItem);
	CreateItem("���", "Texture/ItemIcon/Piercing.png", SKILLICON, 175, 5000, m_vQuickItem);

	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", HPOTION, 50, 50, m_vConShopItem);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", HPOTION, 100, 100, m_vConShopItem);
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", HPOTION, 150, 200, m_vConShopItem);
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", MPOTION, 50, 60, m_vConShopItem);
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", MPOTION, 100, 120, m_vConShopItem);
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", MPOTION, 150, 240, m_vConShopItem);
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200 , m_vConShopItem);
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vConShopItem);
	
	
	CreateItem("���", "Texture/ItemIcon/Claymore.png", WEAPON, 15, 200, m_vStatusItem);
	//CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 4000, m_vInvenItem);
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 3000, m_vInvenItem);
	CreateItem("��ġ", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50,2000, m_vInvenItem);
	//
	////����Ʈ
	//CreateItem("���������ǿ�", "Texture/ItemIcon/BlackClothes.png", ARMOR, 75, 3600, m_vInvenItem);
	//CreateItem("���������ǽŹ�", "Texture/ItemIcon/BlackShoes.png", SHOES, 25 , 1400, m_vInvenItem);
	//CreateItem("�����������尩", "Texture/ItemIcon/BlackGlove.png", GLOVES, 20, 1100, m_vInvenItem);
	
	//������Ʈ
	CreateItem("�����Ƹ�", "Texture/ItemIcon/LeatherClothes.png", ARMOR, 50, 2600, m_vInvenItem);
	CreateItem("��������", "Texture/ItemIcon/LeatherShoes.png", SHOES, 15, 1100, m_vInvenItem);
	CreateItem("�����۷���", "Texture/ItemIcon/LeatherGlove.png", GLOVES, 11, 900, m_vInvenItem);
	
	//��ī�̼�Ʈ
	CreateItem("�����÷��Ƹ�", "Texture/ItemIcon/PurpleClothes.png", ARMOR, 20, 1000, m_vInvenItem);
	CreateItem("�����÷�����", "Texture/ItemIcon/PurpleShoes.png", SHOES, 5, 200, m_vInvenItem);
	CreateItem("�����÷��۷���", "Texture/ItemIcon/PurpleGlove.png", GLOVES, 3, 160, m_vInvenItem);

	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", HPOTION, 50, 50, m_vInvenItem);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", HPOTION, 100, 100, m_vInvenItem);



}


