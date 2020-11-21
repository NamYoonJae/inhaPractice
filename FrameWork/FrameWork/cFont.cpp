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

void cFont::Update()
{

}

void cFont::Render()
{
	m_pFont->DrawTextA(NULL, m_Text.c_str(), m_Text.length(), &m_Rect, m_Format, m_Color);

}

