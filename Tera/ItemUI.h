#pragma once
//인덱스가 존재하지않음
#define NONEINDEX -1
#define ZEROVALUE 0



enum enTextType
{
	CONSTCHAR,
	VARIABLEVALUE
};


struct tagText
{
	enTextType  Type;
	const char* szTextName;
	int			nIdentyfyNum;
	const char* szParrentName;
};



enum UIType
{
	WINDOW,
	BUTTON
};



struct tagUIInfo
{
	UIType		 _UIType;
	const char*	 _UIName;
	const char*	 _UIParentName;
	D3DXVECTOR3  _UIPos;
	const char*	 _UIPath1;
	const char*	 _UIPath2;
	const char*	 _UIPath3;
	D3DXVECTOR2	 _UIReduceDragSize;	
};



//미리작성한 텍스트라는뜻
typedef vector<const char*> vTextCContents;
typedef vector<int>			vTextIContents;
typedef vector<D3DXVECTOR3> vTextPos;
typedef vector<D3DXVECTOR2> vTextSize;
typedef vector<D3DXVECTOR3> vTextColor;

struct tagTextPack
{
	enTextType		_textType;
	const char*    _textParentName;
	vTextCContents  _vTextCContents;
	vTextIContents  _vTextIContents;
	vTextPos	   _vTextPos;
	vTextSize	   _vTextSize;
	vTextColor	   _vTextColor;
};

enum tagWhereToUseVariables
{
	ICESWORD
};



enum tagItemKind
{
	HELMET,
	ARMOR,
	WEAPON,
	GLOVES,
	SHOES,
	POTION,
	ETCCONSUMABLES
};

struct tagItemInfo
{
	const char*	 _itemName;
	tagItemKind	 _itemKind;
	D3DXVECTOR3  _itemPos;
	const char*	 _itemPath;
	int			 _itemAbilityValue;
	int			 _itemSalePrice;
	int			 _itemBuyPrice;
	const char*	 _itemExplain;
};



//struct tagDragPointer
//{
//	RECT collisionRc;
//	bool isClick = false;
//	bool isCollision = false;
//	POINT g_beforeMousePT = {0,0};
//	POINT g_move = { 0,0 };
//	int sequence = 0;
//	POINT floatToInt;
//};

//POINT g_beforeMousePT = { 0,0 };
//POINT g_move = { 0,0 };








