#include "stdafx.h"
#include "cFont.h"
#include "FontManager.h"


cFont::cFont()
	:m_Color(D3DCOLOR_ARGB(255, 255, 255, 255))
	,m_Format(DT_LEFT | DT_TOP | DT_NOCLIP)
	,m_pFont(NULL)
{

}


cFont::~cFont()
{
	SafeRelease(m_pFont);
}


void cFont::Setup(string text, eFontType fontType)
{
	m_Text = text;
	m_pFont = g_pFontManager->GetFont(fontType);
}

void cFont::Setup(string text, eFontType fontType, D3DXVECTOR3 position)
{
	// TODO position에 해당하는 위치에 렌더되게 생성
	
	m_Text = text;
	m_pFont = g_pFontManager->GetFont(fontType);
}

void cFont::Update()
{

}

// cPopUp을 상속받아 렌더하기때문에 objectManager에서 cPopUp::Render(D3DXMATRIXA16 * pmat)가 실행될 것으로 예상됨
void cFont::Render()
{

	m_pFont->DrawTextA(NULL, m_Text.c_str(), m_Text.length(), &m_Rect, m_Format, m_Color);
}



