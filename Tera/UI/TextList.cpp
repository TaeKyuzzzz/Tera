#include "stdafx.h"
#include "Manager\cUIManager.h"
#include "UI/cUIInfo.h"
#include "Manager\cItemManager.h"
#include "UI\cUIObject.h"
#include "UI\cUITextView.h"
#include "UI\cUIButton.h"
#include "GameObject\Item\cItemInfo.h"


void cUIManager::UITextList()
{

	//내용(1), 위치(3), 글씨크기(2), 컬러(3)
#pragma region 소모품상점
	CreateUICTextData
	(
		{ "소모품상점", "정산하기", "회복물약", "중급회복물약", "상급회복물약", "마나물약", "중급마나물약", "상급마나물약" }
		, { { 200,10,0 },{ 310, 256, 0 },{ 65, 93, 0 },{ 240, 93, 0 },{ 65, 132, 0 },{ 241, 129, 0 },{ 65,172,0 },{ 241,172,0 } }
		, { { 25, 15 },{ 15, 5 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 } }
		, { { 211, 254, 255 },{ 211, 254, 255 },{ 200, 50, 55 },{ 200, 50, 55 },{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 } }
	);
	tagText t1;
	t1.Type = CONSTCHAR;
	t1.szTextName = "소모품상점";
	t1.szParrentName = "ConsumablesShop";
	CreateText(t1);

#pragma endregion


#pragma region 인벤토리
	CreateUIITextData
	(
		//인벤토리
		{ 1, m_nGold }
		, { { 50,10,0 },{ 200,334,0 } }
		, { { 25,15 } ,{ 15,8 } }
		, { { 128,128,128 },{ 255,255,255 } }
	);

	tagText t4;
	t4.Type = VARIABLEVALUE;
	t4.nIdentyfyNum = 1;
	t4.szParrentName = "Inventory";
	CreateText(t4);
#pragma endregion



#pragma region 아이템툴팁
	CreateUICTextData
	(
		{ "이름","능력", "설명" }
		, { { 50,10,0 },{ 50,40,0 },{ 10,70,0 } }
		, { { 25,15 },{ 25,15 },{ 25,15 } }
		, { { 128,128,128 },{ 200,200,200 },{ 128,128,128 } }
	);

	tagText t2;
	t2.Type = CONSTCHAR;
	t2.szTextName = "이름";
	t2.szParrentName = "ItemInfoWindow";
	CreateText(t2);


	CreateUIITextData
	(
		{ 2, 999}
		, { { 800, 100, 0 },{ 200, 30, 0 },{ 200, 30, 0 } }
		, { { 50, 15 },{ 50, 15 },{ 50, 15 } }
		, { { 230, 230, 230 },{ 230, 50, 230 },{ 230, 50, 230 } }
	);

	tagText t3;
	t3.Type = VARIABLEVALUE;
	t3.nIdentyfyNum = 2;
	t3.szParrentName = "ItemInfoWindow";
	CreateText(t3);

#pragma endregion







	

	





	


	
	
}










