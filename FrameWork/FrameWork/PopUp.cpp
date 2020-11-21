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
	, pParent(NULL)
{
	m_Percentage = 0;
	m_Power = true;
	m_Fixed = false;
}


cPopUp::~cPopUp()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	SafeDelete(pParent);
	
	for (int i = m_vecPopupBtnList.size(); i == 0 ; i--)
	{
		delete m_vecPopupBtnList[i];
		m_vecPopupBtnList.erase(m_vecPopupBtnList.end());
	}

}

void cPopUp::Setup(char * root, char * fileName, D3DXVECTOR3 position, float percent, bool powerOnOff, bool fixed)
{
	m_Percentage = percent;
	m_Position = position;
	m_Power = powerOnOff;
	m_Fixed = fixed;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = root + string("/") + string(fileName);
	
	LoadTexture((char*)fileRoot.c_str());

}

void cPopUp::Update(EventType message)
{
	if (!m_Fixed) 
	{
		if (message == EventType::EVENT_ESC)
		{
			PowerOnOff();

			for (int i = 0; i < m_vecPopupBtnList.size(); i++)
			{
				m_vecPopupBtnList[i]->PowerOnOff();
			}

		}
	}


	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->Update(message);
	}
}

void cPopUp::Render(D3DXMATRIXA16 * pmat)
{
	if (m_Power) 
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		SetRect(&m_Rect, 0, 0, m_ImageInfo.Width, m_ImageInfo.Height);
		D3DXMATRIXA16 matT, matS, matWorld;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matS, m_Percentage, m_Percentage, m_Percentage);
		D3DXMatrixTranslation(&matT, m_Position.x, m_Position.y, 0);

		matWorld = matS * matT;
		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(m_pTextureUI, &m_Rect, &D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pSprite->End();


		for (int i = 0; i < m_vecPopupBtnList.size(); i++)
		{
			m_vecPopupBtnList[i]->Render();
		}
	}
}

void cPopUp::cButtonPushBack(cPopUp* btn)
{
	m_vecPopupBtnList.push_back(btn);
	btn->pParent = this;
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

float cPopUp::GetPercent()
{
	return m_Percentage;
}

void cPopUp::PowerOnOff()
{
	m_Power = !m_Power;

	for (int i = 0 ; i < m_vecPopupBtnList.size(); i++) 
	{
		m_vecPopupBtnList[i]->PowerOnOff();
	}
}

void cPopUp::Destroy()
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->Destroy();
		//EventManager->Detach(*m_vecPopupBtnList[i]);
	}

	EventManager->Detach(*this);
}

cPopUp* cPopUp::GetForefather()
{
	cPopUp* pPopup;
	if (pParent)
	{
		pPopup = pParent->GetForefather();
		return pPopup;
	}
	else
		return this;
}
