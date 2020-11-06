#include "stdafx.h"
#include "PopUp.h"
#include "Button.h"


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
	m_pButtonHover = new cButton;
	m_pButtonHover->Setup("UI", "btn-med-over.png", D3DXVECTOR3(0, 0, 0), 0, 0, 0); //->버튼 이미지 루트와 좌표값을 가지고 셋팅
	m_pButtonClick = new cButton;
	m_pButtonClick->Setup("UI", "btn-med-down.png", D3DXVECTOR3(0, 0, 0), 0, 0, 0);


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
	if (message == "EVENT_MOVE")
	{ 
		D3DXVECTOR2 cur = EventManager->GetMouseCurrent();

		for (int i = 0; i < m_vecBtnList.size(); i++) 
		{
			D3DXVECTOR3 btnPosition = m_vecBtnList[i]->GetPosition();	//좌상단 좌표
			float width = m_vecBtnList[i]->GetImageInfoWidth();	//버튼의 가로길이
			float height = m_vecBtnList[i]->GetImageInfoHeight();	//버튼의 세로길이

			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width) 
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height) 
				{
					m_vecBtnList[i]->SetStateChange(enum_Hover);
				}
				else 
				{
					m_vecBtnList[i]->SetStateChange(enum_Off);
				}
			}
			else
			{
				m_vecBtnList[i]->SetStateChange(enum_Off);
			}

		}//for end
		

	}//if (message == "EVENT_MOVE" ) END



	
	if (message == "EVENT_LBUTTONDOWN") 
	{
		D3DXVECTOR2 cur = EventManager->GetMouseCurrent();

		for (int i = 0; i < m_vecBtnList.size(); i++) 
		{
			D3DXVECTOR3 btnPosition = m_vecBtnList[i]->GetPosition();	//좌상단 좌표
			float width = m_vecBtnList[i]->GetImageInfoWidth();	//버튼의 가로길이
			float height = m_vecBtnList[i]->GetImageInfoHeight();	//버튼의 세로길이

			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					m_vecBtnList[i]->SetStateChange(enum_On);
				}
			}

		}
		cout << "버튼 스테이트" << m_vecBtnList[0]->GetState() << endl;
	}

	if (message == "EVENT_LBUTTONUP") 
	{
		D3DXVECTOR2 cur = EventManager->GetMouseCurrent();

		for (int i = 0; i < m_vecBtnList.size(); i++)
		{
			D3DXVECTOR3 btnPosition = m_vecBtnList[i]->GetPosition();	//좌상단 좌표
			float width = m_vecBtnList[i]->GetImageInfoWidth();	//버튼의 가로길이
			float height = m_vecBtnList[i]->GetImageInfoHeight();	//버튼의 세로길이

			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					m_vecBtnList[i]->SetStateChange(enum_Hover);
				}
			}
		}
		cout << "버튼 스테이트" << m_vecBtnList[0]->GetState() << endl;
	}
	
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

	for(int i = 0; i < m_vecBtnList.size(); i++)
	{
		int state = m_vecBtnList[i]->GetState();

		if (state == enum_On) 
		{
			m_pButtonClick->Render(m_vecBtnList[i]->GetPosition());
		}
		else if(state == enum_Off)
		{
			m_vecBtnList[i]->Render();
		}
		else if (state == enum_Hover) 
		{
			m_pButtonHover->Render(m_vecBtnList[i]->GetPosition());
		}
	}


}

/*
D3DXVECTOR3 PopUp::GetPosition()
{
	return m_Position;
}
*/

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
