#pragma once

struct tagItemAbilityType
{
	int abilityValue = 0;

	tagItemKind _tagItemKind;
	

};

class cUIObject;
class cUIImageView;


class cItemInfo
{
private:
		
	// UI
	LPD3DXSPRITE		m_pSprite;			// 아이템 2d 아이콘
	LPDIRECT3DTEXTURE9	m_pUITexture;		// 
	D3DXIMAGE_INFO		m_stImageInfo;		// 

	cUIImageView* m_pImage;

	

	SYNTHESIZE(cUIObject*, m_pUIRoot, UIRoot);
	SYNTHESIZE(cUIImageView*, m_pUIImage, UIImage);
	SYNTHESIZE(POINT, m_ptDragSize, DragSize);
	SYNTHESIZE(int, m_nCurrentSlotNum, CurrentSlotNum);
	SYNTHESIZE(tagItemAbilityType, m_stAbility, Ability);
	SYNTHESIZE(const char*, m_szName, Name);
	SYNTHESIZE(const char*, m_szAbilityKind, AbilityKind);
	SYNTHESIZE(const char*, m_szExplain, Explain);
	SYNTHESIZE(int, m_nSalePrice, SalePrice);

public:
	cItemInfo();
	virtual~cItemInfo();

	void Setup(tagItemInfo* _item);
	void Update();
	void Render();


	void TransPos(D3DXVECTOR3 vec3Pos);
	//void ConnectNode(cUIObject* parrent);
};

