#include "stdafx.h"
#include "Trophies.h"
#include "TextureManager.h"


cTrophies::cTrophies()
{
	m_MaxGauge = 0;
	m_Gauge = 0;
	m_pSprite = NULL;
	m_pTextureUI = NULL;
	m_State = enum_Off;
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pParent = NULL;
	EventProcess = NULL;
	m_Percentage = 0;
	m_Power = true;
	m_Fixed = true;
	m_pPaladin = NULL;

}


cTrophies::~cTrophies()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	SafeDelete(pParent);
}


void cTrophies::Setup(char* root, char* fileName, D3DXVECTOR3 position, float percent, bool powerOnOff, bool fixed, int tag, int maxGauge, int gauge)
{
	m_Percentage = percent;
	m_Position = position;
	m_Power = powerOnOff;
	m_Fixed = fixed;
	m_nTag = tag;
	m_MaxGauge = maxGauge;
	m_Gauge = gauge;
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = root + string("/") + string(fileName);
	str_filename = string(fileName);

	LoadTexture((char*)fileRoot.c_str());
}


void cTrophies::Update()
{
}

void cTrophies::Update(EventType message)
{
	if (m_Power)
	{
		if (EventProcess)
			EventProcess(message, this);
	}
}

void cTrophies::Render(D3DXMATRIXA16* pmat)
{
	bool chk_parents = 0;
	if (pParent)
		chk_parents = pParent->GetState();

	if (chk_parents || !pParent)
		if (m_Power)
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

			SetRect(&m_Rect, 0, 0, m_ImageInfoWidth, m_ImageInfoHeight);
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
		}
}

int cTrophies::GetState()
{
	return m_State;
}

void cTrophies::SetStateChange(int state)
{
	m_State = state;
}

D3DXVECTOR3 cTrophies::GetPosition()
{
	return m_Position;

}

float cTrophies::GetImageInfoWidth()
{
	return (float)m_ImageInfo.Width;
}

float cTrophies::GetImageInfoHeight()
{
	return (float)m_ImageInfo.Height;
}

void cTrophies::LoadTexture(char* szFullPath)
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
	m_ImageInfoWidth = m_ImageInfo.Width;
	m_ImageInfoHeight = m_ImageInfo.Height;
	SetRect(&m_Rect, 0, 0, m_ImageInfoWidth, m_ImageInfoHeight);

	g_pTextureManager->AddTexture(szFullPath, m_pTextureUI);
	g_pTextureManager->AddImageInfo(szFullPath, m_ImageInfo);
}

void cTrophies::ChangeSprite(char* szFullPath)
{
	if (!g_pTextureManager->GetTexture(szFullPath))
	{
		LoadTexture(szFullPath);
	}

	m_pTextureUI = g_pTextureManager->GetTexture(szFullPath);
	m_ImageInfo = g_pTextureManager->GetImageInfo(szFullPath);
}

float cTrophies::GetPercent()
{
	return m_Percentage;
}

void cTrophies::PowerOnOff()
{
	m_Power = !m_Power;
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff();
	}
}
int cTrophies::GetMaxGauge()
{
	return m_MaxGauge;
}
int cTrophies::GetGauge()
{
	return m_Gauge;
}
/*
void cTrophies::PowerOnOff(bool power)
{
}

void cTrophies::PowerOnOff_List()
{
}

void cTrophies::PowerOnOff_List(bool power)
{
}

void cTrophies::PowerOnOff_OnlySelf()
{
}

void cTrophies::PowerOnOff_OnlySelf(bool power)
{
}

void cTrophies::PowerOnOff_List_OnlySelf()
{
}

void cTrophies::PowerOnOff_List_OnlySelf(bool power)
{
}

void cTrophies::Destroy()
{
}

cPopup* cTrophies::GetTopPopUp()
{
	return nullptr;
}

cPopup* cTrophies::GetUpPopUp()
{
	return nullptr;
}

cPopup* cTrophies::GetPopupBtn()
{
	return nullptr;
}

cPopup* cTrophies::GetPopupBtn(int index)
{
	return nullptr;
}
*/