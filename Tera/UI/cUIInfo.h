#pragma once

class cUIObject;
class cUIImageView;
class cUIButton;
class cUITextView;

class cUIInfo
{
private:
	// UI
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pUITexture;
	D3DXIMAGE_INFO		m_stImageInfo;

	SYNTHESIZE(cUIObject*, m_pUIRoot, UIRoot);
	SYNTHESIZE(cUIImageView*, m_pUIImage, UIImage);
	SYNTHESIZE(cUITextView*, m_pText, Text);

	SYNTHESIZE(cUIButton*, m_pUIButtonImage, UIButtonImage);

	//���� ���Ƿ� ���簪
	SYNTHESIZE(D3DXVECTOR3, m_pVec3Pos, Vec3Pos);
	SYNTHESIZE(ST_UI_SIZE, m_nReduceDragSize, ReduceDragSize);


	SYNTHESIZE(POINT, m_move, Move);
	
	SYNTHESIZE(const char*, m_Name, Name);
	SYNTHESIZE(const char*, m_parentName, ParentName);

	//�����϶�
	//SYNTHESIZE(int, m_nWhereToUseVariables, WhereToUseVariables);
	////����϶�
	//SYNTHESIZE(const char*, m_szWheretoUseCHAR, WheretoUseCHAR);

	//�����϶�
	SYNTHESIZE(int, m_nIdentify, identifyNUM);
	//����϶�
	SYNTHESIZE(const char*, m_szIdentify, IdentifyCHAR);


	POINT dragSize;
	POINT m_ptBeforeMouse;
	bool m_isCollision;


public:
	cUIInfo();
	virtual~cUIInfo();

	void Setup(tagTextPack* _tagTextPack, tagUIInfo* _UI = NULL);//tagUIInfo* _UI
	void Update();
	void Render();
	void ConnectNode(cUIObject* pParent);


};

