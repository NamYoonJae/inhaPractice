#include "stdafx.h"
#include "PopUp.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Button.h"
#include "Scene.h"

cPopup::cPopup()
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_State(enum_Off)
	, m_Position(0.0f, 0.0f, 0.0f)
	, pParent(NULL)
	, EventProcess(NULL)
	, m_Percentage(0)
	, m_Power(true)
	, m_Fixed(false)
	, m_pPaladin(NULL)
{
}


cPopup::~cPopup()
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

void cPopup::Setup(char * root, char * fileName, D3DXVECTOR3 position, float percent, bool powerOnOff, bool fixed)
{
	m_Percentage = percent;
	m_Position = position;
	m_Power = powerOnOff;
	m_Fixed = fixed;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = root + string("/") + string(fileName);
	str_filename = string(fileName);

	LoadTexture((char*)fileRoot.c_str());
}

void cPopup::Setup(char* root,char* fileName,D3DXVECTOR3 position,float x,float y,float z,float percent,bool powerOnOff,bool fixed)
{
	m_Percentage = percent;

	m_Position.x = position.x + x;
	m_Position.y = position.y + y;
	m_Position.z = position.z + z;

	m_Power = powerOnOff;
	m_Fixed = fixed;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = fileRoot + string("/") + string(fileName);
	str_filename = string(fileName);

	LoadTexture((char*)fileRoot.c_str());
}

void cPopup::Setup(char * root, char * fileName, D3DXVECTOR3 position, float percent, bool powerOnOff, bool fixed, int tag)
{
	m_Percentage = percent;
	m_Position = position;
	m_Power = powerOnOff;
	m_Fixed = fixed;
	m_nTag = tag;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = root + string("/") + string(fileName);
	str_filename = string(fileName);

	LoadTexture((char*)fileRoot.c_str());
}

void cPopup::Setup(char * root, char * fileName, D3DXVECTOR3 position, float x, float y, float z, float percent, bool powerOnOff, bool fixed, int tag)
{
	m_Percentage = percent;

	m_Position.x = position.x + x;
	m_Position.y = position.y + y;
	m_Position.z = position.z + z;

	m_Power = powerOnOff;
	m_Fixed = fixed;
	m_nTag = tag;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	string fileRoot(root);
	fileRoot = fileRoot + string("/") + string(fileName);
	str_filename = string(fileName);

	LoadTexture((char*)fileRoot.c_str());
}

void cPopup::Update(EventType message)
{
	
//#pragma region Fixed_Event
//	if (false == m_Fixed)
//	{
//		if (message == EventType::EVENT_ESC)
//		{
//			PowerOnOff_OnlySelf();
//			return; // 창을 끌 때 하위객체에 이벤트를 전달하지 않기 위함
//		}
//	}
//#pragma endregion Fixed_Event

	if (m_Power)
	{
		for (int i = 0; i < m_vecPopupBtnList.size(); i++)
		{
			m_vecPopupBtnList[i]->Update(message);
		}
	}

	
	if (m_Power)
	{
		if (EventProcess)
			EventProcess(message, this);
	}
	

}

void cPopup::Render(D3DXMATRIXA16 * pmat)
{
	// 부모객체가 없거나 부모객체의 파워가 true인 경우에 렌더하게 변경
	bool chk_parents = 0;
	if (pParent)
		chk_parents = pParent->GetState();
	
	if(chk_parents || !pParent)
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

			for (int i = 0; i < m_vecPopupBtnList.size(); i++)
			{
				m_vecPopupBtnList[i]->Render();
			}
		}
}

void cPopup::cButtonPushBack(cPopup* btn)
{
	btn->pParent = this;
	m_vecPopupBtnList.push_back(btn);
}

int cPopup::GetState()
{
	return m_State;
}

void cPopup::SetStateChange(int state)
{
	m_State = state;
}

D3DXVECTOR3 cPopup::GetPosition()
{
	return m_Position;
}

float cPopup::GetImageInfoWidth()
{
	return (float)m_ImageInfo.Width;
}

float cPopup::GetImageInfoHeight()
{
	return (float)m_ImageInfo.Height;
}

void cPopup::LoadTexture(char * szFullPath)
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
	cout << "m_ImageInfoWidth: " << m_ImageInfoWidth << endl;
	cout << "m_ImageInfoHeight: " << m_ImageInfoHeight << endl;
	SetRect(&m_Rect, 0, 0, m_ImageInfoWidth, m_ImageInfoHeight);
	
	g_pTextureManager->AddTexture(szFullPath, m_pTextureUI);
	g_pTextureManager->AddImageInfo(szFullPath, m_ImageInfo);
}

void cPopup::ChangeSprite(char * szFullPath)
{
	if (!g_pTextureManager->GetTexture(szFullPath))
	{
		LoadTexture(szFullPath);
	}

	m_pTextureUI = g_pTextureManager->GetTexture(szFullPath);
	m_ImageInfo = g_pTextureManager->GetImageInfo(szFullPath);
}

void cPopup::MovePosition(D3DXVECTOR2 distance)
{
	m_Position.x += distance.x;
	m_Position.y += distance.y;
}

void cPopup::SetPosition(D3DXVECTOR2 position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
}

float cPopup::GetPercent()
{
	return m_Percentage;
}

void cPopup::PowerOnOff()
{
	m_Power = !m_Power;

	for (int i = 0 ; i < m_vecPopupBtnList.size(); i++) 
	{
		m_vecPopupBtnList[i]->PowerOnOff();
	}
}

void cPopup::PowerOnOff(bool power)
{
	m_Power = power;

	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff(power);
	}
}

void cPopup::PowerOnOff_List()
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff();
	}
}

void cPopup::PowerOnOff_List(bool power)
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff(power);
	}
}

// 객체 자신만 power의 상태 변화
void cPopup::PowerOnOff_OnlySelf()
{
	m_Power = !m_Power;
}

// 객체 자신만 power의 상태 변화
void cPopup::PowerOnOff_OnlySelf(bool power)
{
	m_Power = power;
}

// 리스트에 등록된 객체들만 상태변화
void cPopup::PowerOnOff_List_OnlySelf()
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff_OnlySelf();
	}
}

// 리스트에 등록된 객체들만 상태변화
void cPopup::PowerOnOff_List_OnlySelf(bool power)
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->PowerOnOff_OnlySelf(power);
	}
}

// 중개자의 fixed상태를 정의하기위해 사용할 메소드
//void cPopup::SetFix(bool fixed)
//{
//	m_Fixed = fixed;
//}

void cPopup::Destroy()
{
	for (int i = 0; i < m_vecPopupBtnList.size(); i++)
	{
		m_vecPopupBtnList[i]->Destroy();
		//EventManager->Detach(*m_vecPopupBtnList[i]);
	}

	EventManager->Detach(*this);
}

// 최상단에 위치한 부모객체의 포인터 좌표를 반환
cPopup* cPopup::GetTopPopUp()
{
	cPopup* pPopup;
	if (pParent)
	{
		pPopup = pParent->GetTopPopUp();
		return pPopup;
	}
	else
		return this;
}

// 부모객체의 포인터 좌표를 반환, 없을시 NULL값을 반환한다.
cPopup* cPopup::GetUpPopUp()
{
	if (pParent)
		return pParent;
	else
		return NULL;
}

// TODO 해당 메서드 삭제 고려중
// vecList에서 0번 인덱스에 해당하는 cPopUp객체 포인터 반환
cPopup* cPopup::GetPopupBtn()
{
	if (0 < m_vecPopupBtnList.size())
		return m_vecPopupBtnList[0];
	else
		return NULL;
}

// vecList에서 index값에 해당하는 cPopUp객체 포인터 반환
cPopup* cPopup::GetPopupBtn(int index)
{
	if (index < m_vecPopupBtnList.size())
		return m_vecPopupBtnList[index];
	else
		return NULL;
}

int cPopup::GetPopUpListSize()
{
	return m_vecPopupBtnList.size();
}

bool cPopup::GetPowerState()
{
	return m_Power;
}

void cPopup::SetPaladinReference(cPaladin* paladin)
{
	m_pPaladin = paladin;
}

cPaladin * cPopup::GetPaladinReference()
{
	return m_pPaladin;
}

void cPopup::SetImageInfoWidth(float percent)
{
	float result = m_ImageInfo.Width * percent / 100;

	if (percent <= 0 || result <= 0)
	{
		m_ImageInfoWidth = 0;
		g_pSceneManager->ChangeScene(SceneType::SCENE_GAMEOVER);
	}
	else
	{
		m_ImageInfoWidth = result;
	}
	
}
