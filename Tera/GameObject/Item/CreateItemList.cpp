#include "stdafx.h"
#include "Manager\cItemManager.h"



void cItemManager::CreateItemList()
{
	//아이템생성//itemFilePath,             //itemName	 	//itemKind //abilityValue
	CreateItem("하급회복물약", "Texture/ItemIcon/HPSmall.png", POTION, 50, 250, 50, m_vShopItem);
	CreateItem("중급회복물약", "Texture/ItemIcon/HPMid.png", POTION, 100, 500, 100, m_vShopItem);
	CreateItem("상급회복물약", "Texture/ItemIcon/HPBig.png", POTION, 150, 1000, 200, m_vShopItem);
	CreateItem("하급마나물약", "Texture/ItemIcon/MPSmall.png", POTION, 50, 300, 60, m_vShopItem);
	CreateItem("중급마나물약", "Texture/ItemIcon/MPMid.png", POTION, 100, 600, 120, m_vShopItem);
	CreateItem("상급마나물약", "Texture/ItemIcon/MPBig.png", POTION, 150, 1200, 240, m_vShopItem);
	CreateItem("미스테리부적", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 1000, 200 , m_vShopItem);
	CreateItem("마을귀환서", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 2000, 400, m_vShopItem);
	
	
	
	CreateItem("아이스소드", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 20000, 4000, m_vInvenItem);
	CreateItem("스카이소드", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 15000, 3000, m_vInvenItem);
	CreateItem("고등어", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50, 10000, 2000, m_vInvenItem);
	//
	//블랙셋트
	CreateItem("검은마력의옷", "Texture/ItemIcon/BlackCloth.png", ARMOR, 75, 18000, 3600, m_vInvenItem);
	CreateItem("검은마력의신발", "Texture/ItemIcon/BlackBoots.png", SHOES, 25, 7000, 1400, m_vInvenItem);
	CreateItem("검은마력의장갑", "Texture/ItemIcon/BlackGlove.png", GLOVES, 20, 5500, 1100, m_vInvenItem);
	
	////레더셋트
	CreateItem("레더아머", "Texture/ItemIcon/LeatherArmor.png", ARMOR, 50, 13000, 2600, m_vInvenItem);
	CreateItem("레더슈즈", "Texture/ItemIcon/LeatherBoots.png", SHOES, 15, 5500, 1100, m_vInvenItem);
	CreateItem("레더글로브", "Texture/ItemIcon/LeatherGlove.png", GLOVES, 11, 4500, 900, m_vInvenItem);
	//
	////스카이셋트
	//CreateItem("스카이아머", "Texture/ItemIcon/SkyCloth.png", ARMOR, 20, 5000, 1000, m_vInvenItem);
	//CreateItem("스카이슈즈", "Texture/ItemIcon/SkyBoots.png", SHOES, 5, 1000, 200, m_vInvenItem);
	//CreateItem("스카이글로브", "Texture/ItemIcon/SkyGlove.png", GLOVES, 3, 800, 160, m_vInvenItem);

	//스카이셋트
	CreateItem("스카이아머", "Texture/ItemIcon/SkyCloth.png", ARMOR, 20, 5000, 1000, m_vStatusItem);
	CreateItem("스카이슈즈", "Texture/ItemIcon/SkyBoots.png", SHOES, 5, 1000, 200, m_vStatusItem);
	CreateItem("스카이글로브", "Texture/ItemIcon/SkyGlove.png", GLOVES, 3, 800, 160, m_vStatusItem);

	
	
	


}


