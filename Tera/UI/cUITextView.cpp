#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
{
}


cUITextView::~cUITextView()
{
}

void cUITextView::SetText(tagTextPack* _tagTextPack)
{
	_enTextType = _tagTextPack->_textType;

	if (_tagTextPack->_textType == CONSTCHAR)
	{
		//문자열의 갯수
		m_vTextNumMax = _tagTextPack->_vTextCContents.size();
		//각 내용들
		m_vTextCContents = _tagTextPack->_vTextCContents;
	}

	else if (_tagTextPack->_textType == VARIABLEVALUE)
	{
		//문자열의 갯수
		m_vTextNumMax = _tagTextPack->_vTextIContents.size();
		//각 내용들
		m_vTextIContents = _tagTextPack->_vTextIContents;
	}

	//각각 어디위치할지
	m_vTextPos = _tagTextPack->_vTextPos;
	
	m_vTextSize = _tagTextPack->_vTextSize;
	m_vTextColor = _tagTextPack->_vTextColor;


}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{


	char szTemp[1024];

	RECT* rc = new RECT[m_vTextNumMax];



	//int startIndex;
	//if (_tagTextType == CONSTCHAR)startIndex = 0;
	//if (_tagTextType == VARIABLEVALUE)startIndex = 1;

	for (int i = 0; i < m_vTextNumMax; i++)
	{
		if (_enTextType == VARIABLEVALUE && i == 0)continue;

		m_pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, m_vTextSize[i]);
		if (_enTextType == CONSTCHAR)sprintf_s(szTemp, "%s", m_vTextCContents[i]);
		if (_enTextType == VARIABLEVALUE)sprintf_s(szTemp, "%d", m_vTextIContents[i]);

		SetRect(&rc[i], m_matWorld._41 + m_vTextPos[i].x
			, m_matWorld._42 + m_vTextPos[i].y
			, m_matWorld._41 + m_vTextPos[i].x + 400
			, m_matWorld._42 + m_vTextPos[i].y + 800);
		m_pFont->DrawTextA
			(
			  NULL, szTemp, strlen(szTemp), &rc[i]
			, DT_LEFT | DT_TOP | DT_NOCLIP
			, D3DCOLOR_XRGB((int)m_vTextColor[i].x, (int)m_vTextColor[i].y, (int)m_vTextColor[i].z)
			);
		m_pFont->Release();
	}


}


