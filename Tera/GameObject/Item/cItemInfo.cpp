#include "stdafx.h"
#include "cItemInfo.h"
#include"UI\cUIObject.h"
#include"UI\cUIImageView.h"


cItemInfo::cItemInfo()
{
}


cItemInfo::~cItemInfo()
{
	SAFE_DELETE(m_pUIImage);
	m_pSprite->Release();
}

void cItemInfo::Setup(tagItemInfo* _item)
{
	m_pUIImage = new cUIImageView;
	m_pUIImage->SetTexture(_item->_itemPath);
	m_pUIImage->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_szName = _item->_itemName;



	m_stAbility.abilityValue = _item->_itemAbilityValue;
	m_stAbility._tagItemKind = _item->_itemKind;
	m_pUIRoot = m_pUIImage;
	
	// UI
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

}
void cItemInfo::Update()
{

	if (m_pUIRoot)	m_pUIRoot->Update();
	

	
	
}
void cItemInfo::Render()
{

	if (m_pUIRoot)m_pUIRoot->Render(m_pSprite);

}

void cItemInfo::TransPos(D3DXVECTOR3 vec3Pos)
{
	m_pUIImage->SetPosition(vec3Pos);
}

//void cItemInfo::ConnectNode(cUIObject * parrent)
//{
//	parrent->AddChild(m_pImage);
//}


