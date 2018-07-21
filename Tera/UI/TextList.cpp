#include "stdafx.h"
#include "Manager\cItemManager.h"

enum eITextTitle
{
	GOLD = 1,
	ITEMVALUE
};


void cItemManager::UITextList()
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
		{ GOLD, m_nGold }
		, { { 50,10,0 },{ 200,334,0 } }
		, { { 25,15 } ,{ 15,8 } }
		, { { 128,128,128 },{ 255,255,255 } }
	);

	tagText t4;
	t4.Type = VARIABLEVALUE;
	t4.nIdentyfyNum = GOLD;
	t4.szParrentName = "Inventory";
	CreateText(t4);
#pragma endregion



#pragma region 아이템툴팁
	CreateUICTextData
	(
		{ "이름","능력", "설명:", "설명의내용"}
		, { { 50,10,0 },{ 50,40,0 },{ 10,90,0 }, {30, 120, 0} }
		, { { 25,15 },{ 25,15 },{ 25,15 }, {25, 15} }
		, { { 135,132,255 },{ 200,200,200 },{ 128,128,128 }, {128,128,128}}
	);

	tagText t2;
	t2.Type = CONSTCHAR;
	t2.szTextName = "이름";
	t2.szParrentName = "ItemExplaneWindow";
	CreateText(t2);


	CreateUIITextData
	(
		{ ITEMVALUE, ZEROVALUE}
		, { { 800, 100, 0 },{ 155, 38, 0 }}
		, { { 50, 15 },{ 30, 15 } }
		, { { 230, 230, 230 },{ 230, 50, 230 } }
	);

	tagText t3;
	t3.Type = VARIABLEVALUE;
	t3.nIdentyfyNum = ITEMVALUE;
	t3.szParrentName = "ItemExplaneWindow";
	CreateText(t3);
#pragma endregion

	TextExplane();
}

void cItemManager::TextExplane()
{



	textExplane["하급회복물약"] = "소량의 HP를 \n 회복시킨다";
	textExplane["중급회복물약"] = "적정량의 HP를\n 회복시킨다";
	textExplane["상급회복물약"] = "대량의 HP를\n 회복시킨다";
	textExplane["하급마나물약"] = "소량의 MP를\n 회복시킨다";
	textExplane["중급마나물약"] = "적정량의 MP를\n 회복시킨다";
	textExplane["상급마나물약"] = "대량의 MP를\n 회복시킨다";
	textExplane["미스테리부적"] = "사용시 신비한\n 일이 일어난다";
	textExplane["마을귀환서"] = "가까운 마을로\n 귀환한다";
	textExplane["대검"] = "커다란 검, \n굉장히 무겁다.";
	textExplane["고등어"] = "칼날로 된 고등어,\n 먹을 수 없다";
	textExplane["아이스소드"] = "얼음을 형상화해 \n 만든 검";
	textExplane["스카이소드"] = "하늘의 모습을\n 담아만든 검";
	textExplane["검은마력의옷"] = "고대 마력의 비밀\n을 담은 옷";
	textExplane["검은마력의신발"] = "고대 마력의 비밀\n을 담은 신발";
	textExplane["검은마력의장갑"] = "고대 마력의 비밀\n을 담은 장갑";
	textExplane["레더아머"] = "가죽을 덧대어\n 만든 갑옷";
	textExplane["레더슈즈"] = "가죽을 덧대어를\n 만든 신발";
	textExplane["레더글로브"] = "가죽을 덧대어\n 만든 장갑";
	textExplane["스카이아머"] = "하늘의 모습을\n 담아 만든 옷";
	textExplane["스카이슈즈"] = "하늘의 모습을\n 담아 만든 신발";
	textExplane["스카이글로브"] = "하늘의 모습을\n 담아 만든 장갑";
	

	 


}









