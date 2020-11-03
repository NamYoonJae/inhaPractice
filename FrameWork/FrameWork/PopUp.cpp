#include "stdafx.h"
#include "PopUp.h"


PopUp::PopUp()
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pFont(NULL)
	, m_State(Off)
	, m_Position(0.0f, 0.0f, 0.0f)
	, m_IsLButtonDown(false)
	, m_IsRButtonDown(false)
{
}


PopUp::~PopUp()
{
	SafeRelease(m_pFont);


}

void PopUp::Setup(char * root, char * fileName)
{
}

void PopUp::Update()
{
}

void PopUp::Render()
{
}

void PopUp::FontCreate(char * szText)
{
}

void PopUp::Text_Render()
{
}
