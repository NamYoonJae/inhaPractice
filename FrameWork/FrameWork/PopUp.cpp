#include "stdafx.h"
#include "PopUp.h"
#include "Button.h"


cPopUp::cPopUp()
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	//, m_pFont(NULL)
	, m_State(enum_Off)
	, m_Position(0.0f, 0.0f, 0.0f)
	, m_pButton(NULL)
{
}


cPopUp::~cPopUp()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	//SafeRelease(m_pFont);

	for (int i = m_vecBtnList.size(); i == 0 ; i--)
	{
		delete m_vecBtnList[i];
		m_vecBtnList.erase(m_vecBtnList.end());
	}

	SafeDelete(m_pButton);
}

void cPopUp::Setup(char * root, char * fileName, D3DXVECTOR3 position)
{
	m_Position = position;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = root + string("/") + string(fileName);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		fileRoot.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_ImageInfo,
		NULL,
		&m_pTextureUI);
	
}

void cPopUp::Update(std::string message)
{
	/*
	if ()
	{
		
	}
	*/
	
	InputcEventManager->GetMouseCurrent();
	InputcEventManager->GetMousePrev();



	for (int i = 0; i < m_vecBtnList.size(); i++) 
	{
		m_vecBtnList[i]->Update(message);
	}

	
	


}

void cPopUp::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rc;
	SetRect(&rc, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	D3DXMATRIXA16 matT, matS, matWorld;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);

	//m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_ptPrevMouse.x, m_ptPrevMouse.y, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_Position.x, m_Position.y, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	matWorld = matS * matT;
	m_pSprite->End();
}


/*
void PopUp::FontCreate(char * text)
{
	m_Text = text;
	D3DXFONT_DESC fd;

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	wcscpy_s(fd.FaceName, L"±¼¸²Ã¼");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void PopUp::Text_Render()
{

}
*/

/*
D3DXVECTOR3 PopUp::GetPosition()
{
	return m_Position;
}
*/

void cPopUp::cButtonPushBack(cButton& btn)
{
	m_vecBtnList.push_back(&btn);
}

int cPopUp::GetState()
{
	return m_State;
}

void cPopUp::StateChange(int state)
{
	m_State = state;
}
