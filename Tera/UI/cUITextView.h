#pragma once
#include "UI\cUIObject.h"

class cUITextView : public cUIObject
{
protected :
	cFontManager::eFontType		m_fontType;
	string						m_sText;
	D3DCOLOR					m_dwColor;
	
	// 정렬 방식
	enum TextSortType
	{
		TST_LEFT,
		TST_CENTER,
		TST_RIGHT
	};

public:
	cUITextView();
	virtual~cUITextView();

	virtual void Render(LPD3DXSPRITE pSprite);
};

