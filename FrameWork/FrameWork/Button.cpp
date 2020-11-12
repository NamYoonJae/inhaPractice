#include "stdafx.h"
#include "Button.h"

cButton::cButton()
{
	m_State = enum_Off;
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

cButton::~cButton()
{
}

void cButton::Setup(char* root, char* fileName, D3DXVECTOR3 position, float x, float y, float z)
{

	m_Position.x = position.x + x;
	m_Position.y = position.y + y;
	m_Position.z = position.z + z;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = fileRoot + string("/") + string(fileName);

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

void cButton::Update(EventType message)
{	
	EventProcess(message, this);
}

void cButton::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rc;
	SetRect(&rc, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	D3DXMATRIXA16 matT, matS, matWorld;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);

	m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_Position.x, m_Position.y, m_Position.z), D3DCOLOR_ARGB(255, 255, 255, 255));

	matWorld = matS * matT;

	m_pSprite->End();
}

void cButton::Render(D3DXVECTOR3 position)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rc;
	SetRect(&rc, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	D3DXMATRIXA16 matT, matS, matWorld;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);

	m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(position.x, position.y, position.z), D3DCOLOR_ARGB(255, 255, 255, 255));

	matWorld = matS * matT;

	m_pSprite->End();
}

int cButton::GetState()
{
	return m_State;
}

void cButton::StateChange(int state)
{
	m_State = state;
}

D3DXVECTOR3 cButton::GetPosition()
{
	return m_Position;
}

float cButton::GetImageInfoWidth()
{
	return (float)m_ImageInfo.Width;
}

float cButton::GetImageInfoHeight()
{
	return (float)m_ImageInfo.Height;
}
