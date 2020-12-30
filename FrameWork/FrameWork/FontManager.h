#pragma once

#define g_pFontManager cFontManager::GetInstance()

#define FONT_LEFTTOP	(DT_LEFT | DT_TOP | DT_NOCLIP)
#define FONT_CENTER		(DT_CENTER | DT_VCENTER | DT_NOCLIP)
#define FONT_LCENTER	(DT_LEFT | DT_VCENTER | DT_NOCLIP)
#define FONT_RCENTER	(DT_RIGHT | DT_VCENTER | DT_NOCLIP)

#define FONT_WHITE	D3DCOLOR_XRGB(255, 255, 255)
#define FONT_BLACK	D3DCOLOR_XRGB(0, 0, 0)
#define FONT_RED	D3DCOLOR_XRGB(255, 0, 0)
#define FONT_GREEN	D3DCOLOR_XRGB(0, 255, 0)
#define FONT_BLUE	D3DCOLOR_XRGB(0, 0, 255)

enum eFontType
{
	FONT_DEFAULT,
	FONT_SYSTEM,

};

class cFontManager
{
private:
	Singletone(cFontManager);
	map<eFontType, LPD3DXFONT > m_mapFont;

public:
	void Destroy();

	LPD3DXFONT	GetFont(eFontType type);
	void DrawFont(eFontType type, string text, RECT drawArea, DWORD format, D3DCOLOR color);
	void DrawFont(eFontType type, string text, int AreaLeft, int AreaTop, int AreaRight, int AreaBottom, DWORD format, D3DCOLOR color);
};
