#include "stdafx.h"
#include "basic.h"
#include "FontManager.h"


cFontManager::cFontManager()
{

}

cFontManager::~cFontManager()
{

}

LPD3DXFONT cFontManager::GetFont(eFontType type)
{
	if (m_mapFont.find(type) != m_mapFont.end())
	{
		return m_mapFont[type];
	}

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	
	if (type == FONT_DEFAULT)
	{
		fd.Width = 12;
		fd.Height = 25;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		wcscpy_s(fd.FaceName, L"±¼¸²Ã¼");
	}
	else if (type == FONT_SYSTEM)
	{
		fd.Width = 25;
		fd.Height = 50;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		AddFontResourceA("data/Font/umberto.ttf");
		wcscpy_s(fd.FaceName, L"umberto");
	}
	else
	{
		return nullptr;
	}

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[type]);
	return m_mapFont[type];
}

void cFontManager::DrawFont(eFontType type, string text, RECT drawArea, DWORD format, D3DCOLOR color)
{
	LPD3DXFONT pFont = GetFont(type);
	pFont->DrawTextA(NULL, text.c_str(), text.length(), &drawArea, format, color);
}

void cFontManager::DrawFont(eFontType type, string text, int AreaLeft, int AreaTop, int AreaRight, int AreaBottom, DWORD format, D3DCOLOR color)
{
	RECT Area;
	SetRect(&Area, AreaLeft, AreaTop, AreaRight, AreaBottom);
	DrawFont(type, text, Area, format, color);
}

void cFontManager::Destroy()
{
	for (auto font : m_mapFont)
	{
		SafeRelease(font.second);
	}

	m_mapFont.clear();
}
