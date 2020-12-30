#include "stdafx.h"
#include "Font.h"
#include "FontManager.h"


cFont::cFont()
	: m_Color(D3DCOLOR_ARGB(255, 255, 255, 255))
	, m_Format(DT_LEFT | DT_TOP | DT_NOCLIP)
	, m_pFont(NULL)
	, m_dwElapsedTime(0)
	, m_dwDurationTime(5000)
{
	m_Fixed = true;
}


cFont::~cFont()
{
	SafeRelease(m_pFont);
}


void cFont::Setup(string text, eFontType fontType)
{
	m_dwElapsedTime = GetTickCount();
	m_Text = text;
	m_pFont = g_pFontManager->GetFont(fontType);
}

void cFont::Setup(string text, eFontType fontType, D3DXVECTOR3 position, bool Fixed)
{
	// TODO position에 해당하는 위치에 렌더되게 생성
	m_Fixed = Fixed;
	m_Text = text;
	m_pFont = g_pFontManager->GetFont(fontType);

	m_dwElapsedTime = GetTickCount();

	SetRect(&m_Rect, 
		(int)position.x, (int)position.y, 
		(int)position.x + 800, (int)position.y + 600);
	//SetRect(&m_Rect, position.x, position.y, position.x + 600, position.y + 300);
}

void cFont::Update()
{
	if (!m_Fixed)
	{
		if (GetTickCount() - m_dwElapsedTime >= m_dwDurationTime)
		{
			m_isDelete = true;
		}
	}
}

// cPopUp을 상속받아 렌더하기때문에 objectManager에서 cPopup::Render(D3DXMATRIXA16 * pmat)가 실행될 것으로 예상됨
void cFont::Render(D3DXMATRIXA16* pmat)
{
	m_pFont->DrawTextA(NULL, m_Text.c_str(), m_Text.length(), &m_Rect, FONT_LEFTTOP, FONT_GREEN);
}


//g_pFontManager->DrawFont(FONT_SYSTEM, Text, 0, 0, 100, 50, FONT_LEFTTOP, FONT_GREEN);
//
//void cFontManager::DrawFont(eFontType type, string text, RECT drawArea, DWORD format, D3DCOLOR color)
//{
//	LPD3DXFONT pFont = GetFont(type);
//	pFont->DrawTextA(NULL, text.c_str(), text.length(), &drawArea, format, color);
//}
//
//void cFontManager::DrawFont(eFontType type, string text, int AreaLeft, int AreaTop, int AreaRight, int AreaBottom, DWORD format, D3DCOLOR color)
//{
//	RECT Area;
//	SetRect(&Area, AreaLeft, AreaTop, AreaRight, AreaBottom);
//	DrawFont(type, text, Area, format, color);
//}


