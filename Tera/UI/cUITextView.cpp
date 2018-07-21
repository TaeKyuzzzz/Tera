#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
{
}


cUITextView::~cUITextView()
{
	//SAFE_DELETE(m_pRect);
}

void cUITextView::SetText(tagTextPack* _tagTextPack)
{
	_enTextType = _tagTextPack->_textType;

	if (_tagTextPack->_textType == CONSTCHAR)
	{
		//���ڿ��� ����
		m_vTextNumMax = _tagTextPack->_vTextCContents.size();
		//�� �����
		m_vTextCContents = _tagTextPack->_vTextCContents;
	}

	else if (_tagTextPack->_textType == VARIABLEVALUE)
	{
		//���ڿ��� ����
		m_vTextNumMax = _tagTextPack->_vTextIContents.size();
		//�� �����
		m_vTextIContents = _tagTextPack->_vTextIContents;
	}

	//���� �����ġ����
	m_vTextPos = _tagTextPack->_vTextPos;
	
	m_vTextSize = _tagTextPack->_vTextSize;
	m_vTextColor = _tagTextPack->_vTextColor;


}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{


	char szTemp[1024];

	m_pRect = new RECT[m_vTextNumMax];



	for (int i = 0; i < m_vTextNumMax; i++)
	{
		//�����϶��� ù��°�� Ű���� �����ϱ⶧���� �ǳʶڴ�.
		if (_enTextType == VARIABLEVALUE && i == 0)continue;
		if (_enTextType == VARIABLEVALUE && m_vTextIContents[i] == 0) continue;

		m_pFont = FONTMANAGER->GetFont(cFontManager::FT_GA, m_vTextSize[i]);


		//�����϶� CContents�� �����϶� IContents�� �־����� ��������.
		if (_enTextType == CONSTCHAR)sprintf_s(szTemp, "%s", m_vTextCContents[i]);

		if (_enTextType == VARIABLEVALUE)sprintf_s(szTemp, "%d", m_vTextIContents[i]);

		SetRect(&m_pRect[i], m_matWorld._41 + m_vTextPos[i].x
			, m_matWorld._42 + m_vTextPos[i].y
			, m_matWorld._41 + m_vTextPos[i].x + 400
			, m_matWorld._42 + m_vTextPos[i].y + 800);

		m_pFont->DrawTextA
			(
			  NULL, szTemp, strlen(szTemp), &m_pRect[i]
			, DT_LEFT | DT_TOP | DT_NOCLIP
			, D3DCOLOR_XRGB((int)m_vTextColor[i].x, (int)m_vTextColor[i].y, (int)m_vTextColor[i].z)
			);
		m_pFont->Release();
	}


}


