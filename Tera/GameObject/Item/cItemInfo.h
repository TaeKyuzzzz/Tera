#pragma once

struct tagItemAbilityType
{
	int abilityValue;

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
	SYNTHESIZE(tagItemAbilityType, m_szAbility, Ability);


public:
	cItemInfo();
	~cItemInfo();

	void Setup(tagItemInfo* _item);
	void Update();
	void Render();

	void TransPos(D3DXVECTOR3 vec3Pos);
	//void ConnectNode(cUIObject* parrent);
};

