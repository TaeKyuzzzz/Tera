#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType type)
{
	if (m_mapFont.find(type) != m_mapFont.end())
		return m_mapFont[type];

	D3DXFONT_DESC fd;// 폰트의 속성을 담은 구조체
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (type == FT_DEFAULT)
	{
		fd.Height = 25;
		fd.Width = 13;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
	}
	else if (type == FT_QUEST)
	{
		fd.Height = 50;
		fd.Width = 20;
		fd.Weight = FW_BOLD;
		fd.Italic = true;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		//AddFontResource("파일경로");
	}
	else if (type == TF_UI_TEXT)
	{
		fd.Height = 15;
		fd.Width = 15;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
	}
	else if (type == TF_UI_NUMBER)
	{
		fd.Height = 15;
		fd.Width = 15;
		fd.Weight = FW_NORMAL;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
	}
	else if (type == TF_UI_NUMBER2)
	{
		fd.Height = 14;
		fd.Width = 7;
		fd.Weight = FW_NORMAL;
		fd.Italic = false;
		//fd.CharSet = DEFAULT_CHARSET;
		//fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		//fd.PitchAndFamily = FF_DONTCARE;
	}
	else if (type == TF_MAIN)
	{
		fd.Height = 33;
		fd.Width = 17;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		
		AddFontResourceExA("Font/BMJUA_ttf.ttf", FR_PRIVATE, 0);
		char str[] = "배달의민족 주아";
		wcsncpy_s(fd.FaceName, L"배달의민족 주아", sizeof(str));
	}

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[type]);

	return m_mapFont[type];
}

void cFontManager::Destroy()
{
	for (auto p : m_mapFont)
	{
		SAFE_RELEASE(p.second);
	}
}
