#include "stdafx.h"
#include "PopUp.h"
#include "Button.h"
#include "TextureManager.h"
#include "EventManager.h"

cPopUp::cPopUp()
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_State(enum_Off)
	, m_Position(0.0f, 0.0f, 0.0f)
	, m_pButton(NULL)
{
}


cPopUp::~cPopUp()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);

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
	
	LoadTexture((char*)fileRoot.c_str());

}

void cPopUp::Update(EventType message)
{
	
	for (int i = 0; i < m_vecBtnList.size(); i++) 
	{
		m_vecBtnList[i]->Update(message);
	}

}

void cPopUp::Render(D3DXMATRIXA16 * pmat)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	SetRect(&m_Rect, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	D3DXMATRIXA16 matT, matS, matWorld;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);

	m_pSprite->Draw(m_pTextureUI, &m_Rect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(m_Position.x, m_Position.y, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	matWorld = matS * matT;

	m_pSprite->End();


	for(int i = 0; i < m_vecBtnList.size(); i++)
	{
		m_vecBtnList[i]->Render();
	}


}

void cPopUp::cButtonPushBack(cButton* btn)
{
	m_vecBtnList.push_back(btn);
}

int cPopUp::GetState()
{
	return m_State;
}

void cPopUp::SetStateChange(int state)
{
	m_State = state;
}

D3DXVECTOR3 cPopUp::GetPosition()
{
	return m_Position;
}

float cPopUp::GetImageInfoWidth()
{
	return (float)m_ImageInfo.Width;
}

float cPopUp::GetImageInfoHeight()
{
	return (float)m_ImageInfo.Height;
}

void cPopUp::LoadTexture(char * szFullPath)
{

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		szFullPath,
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
		&m_pTextureUI
	);

	SetRect(&m_Rect, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
	g_pTextureManager->AddTexture(szFullPath, m_pTextureUI);
	g_pTextureManager->AddImageInfo(szFullPath, m_ImageInfo);

}

void cPopUp::ChangeSprite(char * szFullPath)
{
	if (!g_pTextureManager->GetTexture(szFullPath))
	{
		LoadTexture(szFullPath);
	}

	m_pTextureUI = g_pTextureManager->GetTexture(szFullPath);
	m_ImageInfo = g_pTextureManager->GetImageInfo(szFullPath);
}
