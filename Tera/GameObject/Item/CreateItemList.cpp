#include "stdafx.h"
#include "Manager\cItemManager.h"

void cItemManager::CreateItemList()
{
	//아이템 설명창
	CreateItem("ItemExplaneWindow", "Texture/UIIcon/ItemInfoWindow.png", NOTANITEM, NULL, NULL, m_vEtcIcon);
	CreateItem("Gold", "Texture/UIIcon/Gold.png", NOTANITEM, NULL, NULL, m_vEtcIcon, "ItemExplaneWindow");
	CreateItem("SwordDance", "Texture/ItemIcon/SwordDance.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("HitDown", "Texture/ItemIcon/HitDown.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("SideSlash", "Texture/ItemIcon/SideSlash.png", SKILLICON, NULL, NULL, m_vEtcIcon);
	CreateItem("Piercing", "Texture/ItemIcon/Piercing.png", SKILLICON, NULL, NULL, m_vEtcIcon);

#pragma region copyItem
	CreateItem("하급회복물약", "Texture/ItemIcon/HPSmall.png", NOTANITEM, 50, 50, m_vItemImitation);
	CreateItem("중급회복물약", "Texture/ItemIcon/HPMid.png", NOTANITEM, 100, 100, m_vItemImitation);
	CreateItem("상급회복물약", "Texture/ItemIcon/HPBig.png", NOTANITEM, 150, 200, m_vItemImitation);
	CreateItem("하급마나물약", "Texture/ItemIcon/MPSmall.png", NOTANITEM, 50, 60, m_vItemImitation);
	CreateItem("중급마나물약", "Texture/ItemIcon/MPMid.png", NOTANITEM, 100, 120, m_vItemImitation);
	CreateItem("상급마나물약", "Texture/ItemIcon/MPBig.png", NOTANITEM, 150, 240, m_vItemImitation);
	CreateItem("미스테리부적", "Texture/ItemIcon/MysteryPaper.png", NOTANITEM, 0, 200, m_vItemImitation);
	CreateItem("마을귀환서", "Texture/ItemIcon/CityRecall.png", NOTANITEM, 0, 400, m_vItemImitation);


	CreateItem("대검", "Texture/ItemIcon/Claymore.png", NOTANITEM, 15, 200, m_vItemImitation);
	CreateItem("아이스소드", "Texture/ItemIcon/TwohandIce.png", NOTANITEM, 150, 4000, m_vItemImitation);
	CreateItem("스카이소드", "Texture/ItemIcon/TwohandSky.png", NOTANITEM, 100, 3000, m_vItemImitation);
	CreateItem("고등어", "Texture/ItemIcon/TwohandFish.png", NOTANITEM, 50, 2000, m_vItemImitation);
	//
	//블랙셋트
	CreateItem("검은마력의옷", "Texture/ItemIcon/BlackClothes.png", NOTANITEM, 75, 3600, m_vItemImitation);
	CreateItem("검은마력의신발", "Texture/ItemIcon/BlackShoes.png", NOTANITEM, 25, 1400, m_vItemImitation);
	CreateItem("검은마력의장갑", "Texture/ItemIcon/BlackGlove.png", NOTANITEM, 20, 1100, m_vItemImitation);

	//레더셋트
	CreateItem("레더아머", "Texture/ItemIcon/LeatherClothes.png", NOTANITEM, 50, 2600, m_vItemImitation);
	CreateItem("레더슈즈", "Texture/ItemIcon/LeatherShoes.png", NOTANITEM, 15, 1100, m_vItemImitation);
	CreateItem("레더글러브", "Texture/ItemIcon/LeatherGlove.png", NOTANITEM, 11, 900, m_vItemImitation);

	//퍼플플랫셋트
	CreateItem("퍼플플랫아머", "Texture/ItemIcon/PurpleClothes.png", NOTANITEM, 20, 1000, m_vItemImitation);
	CreateItem("퍼플플랫슈즈", "Texture/ItemIcon/PurpleShoes.png", NOTANITEM, 5, 200, m_vItemImitation);
	CreateItem("퍼플플랫글러브", "Texture/ItemIcon/PurpleGlove.png", NOTANITEM, 3, 160, m_vItemImitation);
#pragma endregion

	

	CreateItem("하급회복물약", "Texture/ItemIcon/HPSmall.png", POTION, 50, 50, m_vConShopItem);
	CreateItem("중급회복물약", "Texture/ItemIcon/HPMid.png", POTION, 100, 100, m_vConShopItem);
	CreateItem("상급회복물약", "Texture/ItemIcon/HPBig.png", POTION, 150, 200, m_vConShopItem);
	CreateItem("하급마나물약", "Texture/ItemIcon/MPSmall.png", POTION, 50, 60, m_vConShopItem);
	CreateItem("중급마나물약", "Texture/ItemIcon/MPMid.png", POTION, 100, 120, m_vConShopItem);
	CreateItem("상급마나물약", "Texture/ItemIcon/MPBig.png", POTION, 150, 240, m_vConShopItem);
	CreateItem("미스테리부적", "Texture/ItemIcon/MysteryPaper.png", ETCCONSUMABLES, 0, 200 , m_vConShopItem);
	CreateItem("마을귀환서", "Texture/ItemIcon/CityRecall.png", ETCCONSUMABLES, 0, 400, m_vConShopItem);
	
	
	CreateItem("대검", "Texture/ItemIcon/Claymore.png", WEAPON, 15, 200, m_vStatusItem);
	CreateItem("아이스소드", "Texture/ItemIcon/TwohandIce.png", WEAPON, 150, 4000, m_vConShopItem);
	CreateItem("스카이소드", "Texture/ItemIcon/TwohandSky.png", WEAPON, 100, 3000, m_vInvenItem);
	CreateItem("고등어", "Texture/ItemIcon/TwohandFish.png", WEAPON, 50,2000, m_vInvenItem);
	//
	//블랙셋트
	CreateItem("검은마력의옷", "Texture/ItemIcon/BlackClothes.png", ARMOR, 75, 3600, m_vConShopItem);
	CreateItem("검은마력의신발", "Texture/ItemIcon/BlackShoes.png", SHOES, 25 , 1400, m_vInvenItem);
	CreateItem("검은마력의장갑", "Texture/ItemIcon/BlackGlove.png", GLOVES, 20, 1100, m_vInvenItem);
	
	//레더셋트
	CreateItem("레더아머", "Texture/ItemIcon/LeatherClothes.png", ARMOR, 50, 2600, m_vInvenItem);
	CreateItem("레더슈즈", "Texture/ItemIcon/LeatherShoes.png", SHOES, 15, 1100, m_vInvenItem);
	CreateItem("레더글러브", "Texture/ItemIcon/LeatherGlove.png", GLOVES, 11, 900, m_vInvenItem);
	
	//스카이셋트
	CreateItem("퍼플플랫아머", "Texture/ItemIcon/PurpleClothes.png", ARMOR, 20, 1000, m_vInvenItem);
	CreateItem("퍼플플랫슈즈", "Texture/ItemIcon/PurpleShoes.png", SHOES, 5, 200, m_vInvenItem);
	CreateItem("퍼플플랫글러브", "Texture/ItemIcon/PurpleGlove.png", GLOVES, 3, 160, m_vInvenItem);




	
	
	


}


