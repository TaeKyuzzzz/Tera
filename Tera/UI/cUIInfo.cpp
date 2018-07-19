#include "stdafx.h"
#include "cUIInfo.h"
#include"UI\cUIImageView.h"
#include"UI\cUIObject.h"
#include"UI\cUIButton.h"
#include"UI\cUITextView.h"


cUIInfo::cUIInfo()
	:m_pUIRoot(NULL)
	, m_isCollision(false)
	, m_ptBeforeMouse{0,0}
{
}


cUIInfo::~cUIInfo()
{
}

void cUIInfo::Setup(tagTextPack* _tagTextPack, tagUIInfo* _UI)
{
	if (_tagTextPack != NULL)
	{
		m_pText = new cUITextView;
		m_pText->SetText(_tagTextPack);
		if(_tagTextPack->_textType == VARIABLEVALUE)m_nIdentify = _tagTextPack->_vTextIContents[0];
		if (_tagTextPack->_textType == CONSTCHAR)m_szIdentify = _tagTextPack->_vTextCContents[0];
	
	}

	else if (_UI->_UIType == WINDOW)
	{
		m_pUIImage = new cUIImageView;
		m_pUIImage->SetTexture(_UI->_UIPath1);
		m_pUIImage->SetPosition(_UI->_UIPos);
		m_pUIImage->SetReduceDragRange(_UI->_UIReduceDragSize);	

	}
	else if (_UI->_UIType == BUTTON)
	{
		m_pUIButtonImage = new cUIButton;
		//m_pUIButtonImage->SetCallPlace(_UI->_UIName);
		m_pUIButtonImage->SetTexture(_UI->_UIPath1, _UI->_UIPath2, _UI->_UIPath3);
		m_pUIButtonImage->SetPosition(_UI->_UIPos);	
	}

	if (_UI)
	{
		m_Name = _UI->_UIName;

		//부모이름을 안가지고 있을때(루트로쓸 노드) 루트로등록
		if (!_UI->_UIParentName)
		{
			if (_UI->_UIType == WINDOW)m_pUIRoot = m_pUIImage;
			else if (_UI->_UIType == BUTTON) m_pUIRoot = m_pUIButtonImage;
		}

		//부모이름을 가지고 있을때 (해당부모의) 자식으로 등록할 이름을 부여
		else if (_UI->_UIParentName)
		{
			m_parentName = _UI->_UIParentName;
		}
	}

	if(_tagTextPack)
	{ 
		m_parentName = _tagTextPack->_textParentName;
	}

	// UI
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

}

void cUIInfo::Update()
{
	if (m_pUIRoot)m_pUIRoot->Update();

}

void cUIInfo::Render()
{
	if(m_pUIRoot)m_pUIRoot->Render(m_pSprite);
}

void cUIInfo::ConnectNode(cUIObject* pParent)
{
if(m_pUIImage)pParent->AddChild(m_pUIImage);
else if(m_pUIButtonImage)pParent->AddChild(m_pUIButtonImage);
else if(m_pText)pParent->AddChild(m_pText);

}
