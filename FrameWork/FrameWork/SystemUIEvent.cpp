#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "SystemUIEvent.h"
#include "OptionUIEvent.h"
#include "BtnUIEvent.h"
#include "Scene.h"

#include "SceneManager.h"
//#include "TextureManager.h"



// 반환되는 포인터는 최상단 팝업의 포인터 좌표
cPopup* Setup_SystemWindow(cPopup* btn)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopup *pSystemBack = new cPopup;
	pSystemBack->Setup(
		"data/UI/InGameSettingUI",
		"NW_InGameSetting_Back.png",
		D3DXVECTOR3(0, 0, 0), 1,
		true, true);

	cPopup *pSystemBackground = new cPopup;
	pSystemBackground->Setup(
		"data/UI/InGameSettingUI",
		"NW_InGameSetting_Background.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 1,
		true, true);
	pSystemBack->cButtonPushBack(pSystemBackground);
	
	//cPopup *pOptionBtnBackGround = new cPopup;
	//pOptionBtnBackGround->Setup(
	//	"data/UI/ConfigurationSettings",
	//	"설정 내용 변경 사이즈조정.png",
	//	D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
	//	true, true);
	//pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);

	//Setup_BarGaugePopupBtn_Legacy(pSystemBackground, D3DXVECTOR3(230, 150, 0))->EventProcess = GaugeBarMoveEvent_Legacy;
	//Setup_BarGaugePopupBtn_Legacy(pSystemBackground, D3DXVECTOR3(230, 200, 0))->EventProcess = GaugeBarMoveEvent_Legacy;
	//Setup_BarGaugePopupBtn_Legacy(pSystemBackground, D3DXVECTOR3(230, 250, 0))->EventProcess = GaugeBarMoveEvent_Legacy;

	{ // top button

		cButton *pSystem_continue = new cButton;
		pSystem_continue->Setup("data/UI/InGameSettingUI", "설정창 탑버튼 사이즈 조정.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0),
			200, 200, 0,
			0.8, true, true);
		pSystemBackground->cButtonPushBack(pSystem_continue);
		pSystem_continue->EventProcess = SysWindow_ContinueBtnEvent;
		
		cButton *pSystem_OptionBtn = new cButton;
		pSystem_OptionBtn->Setup("data/UI/InGameSettingUI", "설정창 탑버튼 사이즈 조정.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 
			200, 200, 0, 
			0.8, true, true);
		pSystemBackground->cButtonPushBack(pSystem_OptionBtn);
		pSystem_OptionBtn->EventProcess = SysWindow_OptionBtnEvent;

		cButton *pSystem_ToTitleBtn= new cButton;
		pSystem_ToTitleBtn->Setup("data/UI/InGameSettingUI", "설정창 탑버튼 사이즈 조정.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 
			200, 250, 0, 
			0.8, true, true);
		pSystemBackground->cButtonPushBack(pSystem_ToTitleBtn);
		pSystem_ToTitleBtn->EventProcess = SysWindow_ToTitleEvent;

		cButton *pSystem_ExitBtn = new cButton;
		pSystem_ExitBtn->Setup("data/UI/InGameSettingUI", "설정창 탑버튼 사이즈 조정.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 
			200, 300, 0, 
			0.8, true, true);
		pSystemBackground->cButtonPushBack(pSystem_ExitBtn);
		pSystem_ExitBtn->EventProcess = SysWindow_ExitGame;
	} // top button

	// cPopup* pOptionPopUp = Setup_OptionWindow(pOptionBackGround);
	
	if (!btn)
	{
		EventManager->Attach(pSystemBack);
		ObjectManager->AddUIChild(pSystemBack);
	}
	else if (btn)
	{
		pSystemBackground->PowerOnOff_OnlySelf();
		btn->cButtonPushBack(pSystemBack);
	}
	
	return pSystemBack;
}

void SysWindow_OptionBtnEvent(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();
	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() *  button->GetPercent();

	switch (message)
	{
	case EventType::EVENT_MOVE:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				if (button->GetState() == enum_Off)
				{
					button->SetStateChange(enum_Hover);	//on상태로 체인지
				}

			}
			else
			{
				if (button->GetState() != enum_Off)
				{
					button->SetStateChange(enum_Off); //off상태로 체인지
				}
			}
		}
		else
		{
			if (button->GetState() != enum_Off)
			{
				button->SetStateChange(enum_Off);	//off 상태로 체인지
			}
		}

		if (button->GetPreState() != button->GetState())
		{
			if (button->GetState() == enum_Hover)//m_State는 Hover이면서 m_PreState는 On/Off일 경우
			{
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Idle.png");
					button->SetPreState(enum_Off);
				}
			}


		}//case EVENT_MOVE End:
	}
	break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->SetStateChange(enum_On);
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (button->GetState() == enum_On)
		{
			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					button->SetStateChange(enum_Off);
					button->GetTopPopUp()->PowerOnOff_List_OnlySelf();
					
					cout << "SysWindow_OptionBtnEvent is Clicked" << endl;
				}
			}
		}
	}
	break;
	};//switch End
}

void SysWindow_ToTitleEvent(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();
	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() *  button->GetPercent();

	switch (message)
	{
	case EventType::EVENT_MOVE:

		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				if (button->GetState() == enum_Off)
				{
					button->SetStateChange(enum_Hover);	//on상태로 체인지
				}
			}
			else
			{
				if (button->GetState() != enum_Off)
				{
					button->SetStateChange(enum_Off); //off상태로 체인지
				}
			}
		}
		else
		{
			if (button->GetState() != enum_Off)
			{
				button->SetStateChange(enum_Off);	//off 상태로 체인지
			}
		}

		if (button->GetPreState() != button->GetState())
		{
			if (button->GetState() == enum_Hover) //m_State는 Hover이면서 m_PreState는 On/Off일 경우
			{
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Idle.png");
					button->SetPreState(enum_Off);
				}
			}


		}//case EVENT_MOVE End:

		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->SetStateChange(enum_On);
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (button->GetState() == enum_On)
		{
			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					cout << "SysWindow_ToTitleEvent Clicked" << endl;
					g_pSceneManager->ChangeScene(SceneType::SCENE_TITLE);
				}
			}
		}
	}
	break;
	};//switch End
}

void SysWindow_ExitGame(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();
	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() *  button->GetPercent();

	switch (message)
	{
	case EventType::EVENT_MOVE:

		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				if (button->GetState() == enum_Off)
				{
					button->SetStateChange(enum_Hover);	//on상태로 체인지
				}

			}
			else
			{
				if (button->GetState() != enum_Off)
				{
					button->SetStateChange(enum_Off); //off상태로 체인지
				}
			}
		}
		else
		{
			if (button->GetState() != enum_Off)
			{
				button->SetStateChange(enum_Off);	//off 상태로 체인지
			}
		}

		if (button->GetPreState() != button->GetState())
		{
			if (button->GetState() == enum_Hover) //m_State는 Hover이면서 m_PreState는 On/Off일 경우
			{
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Idle.png");
					button->SetPreState(enum_Off);
				}
			}


		}//case EVENT_MOVE End:

		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->SetStateChange(enum_On);
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (button->GetState() == enum_On)
		{
			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					// TODO exit 있는 부분
					exit(0);
				}
			}
		}
	}
	break;
	};//switch End
}

// 반환되는 cButton 포인터를 사용하여 셋업한 객체의 Eventprocess에 함수 넣기, 벡터인자는 일단 빈값이어도 됨
