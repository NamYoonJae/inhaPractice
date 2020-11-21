#pragma once
#include "Observer.h"
#include "FontManager.h"

class cFont :
	public cObserver
{
	string m_Text;
	LPD3DXFONT m_pFont;

	RECT m_Rect;
	D3DCOLOR m_Color;
	DWORD m_Format;


public:
	cFont();
	~cFont();

	void Setup(string text, eFontType fontType);
	void Update();
	void Render();

};

