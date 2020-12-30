#pragma once
#include "Observer.h"

enum eFontType;

class cFont :
	public cPopup
	//public cObserver
{
	string m_Text;
	LPD3DXFONT m_pFont;

	RECT m_Rect;
	D3DCOLOR m_Color;
	DWORD m_Format;

	DWORD m_dwElapsedTime;
	DWORD m_dwDurationTime;
	
public:
	cFont();
	~cFont();

	void Setup(string text, eFontType fontType);
	void Setup(string text, eFontType fontType, D3DXVECTOR3 position, bool Fixed = true);
	void Update();
	void Render(D3DXMATRIXA16* pmat);

};

