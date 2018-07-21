#include "stdafx.h"
#include "Manager\cItemManager.h"



void cItemManager::CreateItemList()
{
	//�����ۻ���//itemFilePath,             //itemName	 	//itemKind //abilityValue
	CreateItem("�ϱ�ȸ������", "Texture/ItemIcon/HPSmall.png", POTION, 50, 250, 50, m_vShopItem);
	CreateItem("�߱�ȸ������", "Texture/ItemIcon/HPMid.png", POTION, 100, 500, 100, m_vShopItem);
	CreateItem("���ȸ������", "Texture/ItemIcon/HPBig.png", POTION, 150, 1000, 200, m_vShopItem);
	CreateItem("�ϱ޸�������", "Texture/ItemIcon/MPSmall.png", POTION, 50, 300, 60, m_vShopItem);
	CreateItem("�߱޸�������", "Texture/ItemIcon/MPMid.png", POTION, 100, 600, 120, m_vShopItem);
	CreateItem("��޸�������", "Texture/ItemIcon/MPBig.png", POTION, 150, 1200, 240, m_vShopItem);
	CreateItem("�̽��׸�����", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 1000, 200 , m_vShopItem);
	CreateItem("������ȯ��", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 2000, 400, m_vShopItem);
	
	
	
	CreateItem("���̽��ҵ�", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 20000, 4000, m_vInvenItem);
	CreateItem("��ī�̼ҵ�", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 15000, 3000, m_vInvenItem);
	CreateItem("����", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50, 10000, 2000, m_vInvenItem);
	//
	//����Ʈ
	CreateItem("���������ǿ�", "Texture/ItemIcon/BlackCloth.png", ARMOR, 75, 18000, 3600, m_vInvenItem);
	CreateItem("���������ǽŹ�", "Texture/ItemIcon/BlackBoots.png", SHOES, 25, 7000, 1400, m_vInvenItem);
	CreateItem("�����������尩", "Texture/ItemIcon/BlackGlove.png", GLOVES, 20, 5500, 1100, m_vInvenItem);
	
	////������Ʈ
	CreateItem("�����Ƹ�", "Texture/ItemIcon/LeatherArmor.png", ARMOR, 50, 13000, 2600, m_vInvenItem);
	CreateItem("��������", "Texture/ItemIcon/LeatherBoots.png", SHOES, 15, 5500, 1100, m_vInvenItem);
	CreateItem("�����۷κ�", "Texture/ItemIcon/LeatherGlove.png", GLOVES, 11, 4500, 900, m_vInvenItem);
	//
	////��ī�̼�Ʈ
	//CreateItem("��ī�̾Ƹ�", "Texture/ItemIcon/SkyCloth.png", ARMOR, 20, 5000, 1000, m_vInvenItem);
	//CreateItem("��ī�̽���", "Texture/ItemIcon/SkyBoots.png", SHOES, 5, 1000, 200, m_vInvenItem);
	//CreateItem("��ī�̱۷κ�", "Texture/ItemIcon/SkyGlove.png", GLOVES, 3, 800, 160, m_vInvenItem);

	//��ī�̼�Ʈ
	CreateItem("��ī�̾Ƹ�", "Texture/ItemIcon/SkyCloth.png", ARMOR, 20, 5000, 1000, m_vStatusItem);
	CreateItem("��ī�̽���", "Texture/ItemIcon/SkyBoots.png", SHOES, 5, 1000, 200, m_vStatusItem);
	CreateItem("��ī�̱۷κ�", "Texture/ItemIcon/SkyGlove.png", GLOVES, 3, 800, 160, m_vStatusItem);

	
	
	


}


