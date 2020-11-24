#include "stdafx.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "OptionUIEvent.h"
#include "SystemUIEvent.h"

// 시스템윈도를 띄울때 버튼이 있다면 맨 위객체에 붙이기
void Setup_SystemWindow(cPopUp* btn)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	
	cPopUp *pOptionBackGround = new cPopUp;
	pOptionBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"설정창 배경 사이즈조정.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 1,
		true, true);
	if(btn)
	btn->cButtonPushBack(pOptionBackGround);

	cPopUp *pOptionBtnBackGround = new cPopUp;
	pOptionBtnBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"설정 내용 변경 사이즈조정.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);

	cButton *pOption_setButton = new cButton;
	pOption_setButton->Setup("data/UI/ConfigurationSettings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), -50, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_setButton);
	pOption_setButton->EventProcess = SysWindow_OptionBtnEvent;


	cButton *pOption_ControlButton = new cButton;
	pOption_ControlButton->Setup("data/UI/ConfigurationSettings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 200, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_ControlButton);
	pOption_ControlButton->EventProcess = Option_ReturnTitle;

	cButton *pOption_CameraButton = new cButton;
	pOption_CameraButton->Setup("data/UI/ConfigurationSettings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 450, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_CameraButton);
	pOption_CameraButton->EventProcess = SysWindow_ExitGame;

	if (!btn)
	{
		EventManager->Attach(pOptionBackGround);
		ObjectManager->AddUIChild(pOptionBackGround);
	}
	else
	{
		pOptionBackGround->PowerOnOff(false);
		btn->cButtonPushBack(pOptionBackGround);
	}

}

void SysWindow_OptionBtnEvent(EventType message, cPopUp* btn)
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
					button->GetForefather()->PowerOnOff();
					Setup_OptionWindow(btn);
				}
			}
		}
	}
	break;
	/*
	case EventType::EVENT_WHEELUP:
	break;
	case EventType::EVENT_WHEELDOWN:
	break;
	case EventType::EVENT_LBUTTONDLBC:
	break;
	case EventType::EVENT_RBUTTONDOWN:
	break;
	case EventType::EVENT_RBUTTONDLBC:
	break;
	case EventType::EVENT_RBUTTONUP:
	break;
	case EventType::EVENT_DRAG:
	break;
	case EventType::EVENT_JUMP:
	break;
	case EventType::EVENT_TAP:
	break;
	case EventType::EVENT_ENTER:
	break;
	case EventType::EVENT_SHIFT:
	break;
	case EventType::EVENT_CTRL:
	break;
	case EventType::EVENT_ALT:
	break;
	case EventType::EVENT_MENU:
	break;
	case EventType::EVENT_HOME_WINDOWS:
	break;
	case EventType::EVENT_ARROW_LEFT:
	break;
	case EventType::EVENT_ARROW_UP:
	break;
	case EventType::EVENT_ARROW_RIGHT:
	break;
	case EventType::EVENT_ARROW_DOWN:
	break;
	case EventType::EVENT_NUMPAD_1:
	break;
	case EventType::EVENT_NUMPAD_2:
	break;
	case EventType::EVENT_NUMPAD_3:
	break;
	case EventType::EVENT_NUMPAD_4:
	break;
	case EventType::EVENT_NUMPAD_5:
	break;
	default:
	break;
	*/
	};//switch End
}

void SysWindow_ExitGame(EventType message, cPopUp* btn)
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
	/*
	case EventType::EVENT_WHEELUP:
	break;
	case EventType::EVENT_WHEELDOWN:
	break;
	case EventType::EVENT_LBUTTONDLBC:
	break;
	case EventType::EVENT_RBUTTONDOWN:
	break;
	case EventType::EVENT_RBUTTONDLBC:
	break;
	case EventType::EVENT_RBUTTONUP:
	break;
	case EventType::EVENT_DRAG:
	break;
	case EventType::EVENT_JUMP:
	break;
	case EventType::EVENT_TAP:
	break;
	case EventType::EVENT_ENTER:
	break;
	case EventType::EVENT_SHIFT:
	break;
	case EventType::EVENT_CTRL:
	break;
	case EventType::EVENT_ALT:
	break;
	case EventType::EVENT_MENU:
	break;
	case EventType::EVENT_HOME_WINDOWS:
	break;
	case EventType::EVENT_ARROW_LEFT:
	break;
	case EventType::EVENT_ARROW_UP:
	break;
	case EventType::EVENT_ARROW_RIGHT:
	break;
	case EventType::EVENT_ARROW_DOWN:
	break;
	case EventType::EVENT_NUMPAD_1:
	break;
	case EventType::EVENT_NUMPAD_2:
	break;
	case EventType::EVENT_NUMPAD_3:
	break;
	case EventType::EVENT_NUMPAD_4:
	break;
	case EventType::EVENT_NUMPAD_5:
	break;
	default:
	break;
	*/
	};//switch End
}

