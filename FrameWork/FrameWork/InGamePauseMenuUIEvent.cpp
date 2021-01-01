#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "InGamePauseMenuUIEvent.h"
#include "SettingUIEvent.h"
#include "BtnUIEvent.h"
#include "Scene.h"

#include "SceneManager.h"
//#include "TextureManager.h"

// 반환되는 포인터는 최상단 팝업의 포인터 좌표
cPopup* Setup_InGamePauseMenu(cPopup* btn)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//cout << "Left : " << rc.left << endl; // 0
	//cout << "Right : " << rc.right << endl; // 1584
	//cout << "Bottom : " << rc.bottom << endl; //860
	//cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopup *pSystemBack = new cPopup;
	pSystemBack->Setup(
		"data/UI/InGamePauseMenu",
		"NW_InGameSetting_Back.png",
		D3DXVECTOR3(0, 0, 0), 
		1,
		true, true);

	cPopup *pSystemBackground = new cPopup;
	pSystemBack->cButtonPushBack(pSystemBackground);
	pSystemBackground->Setup(
		"data/UI/InGamePauseMenu",
		"NW_InGameSetting_Background.png", // 362  421
		D3DXVECTOR3((rc.right - 362)/ 2 , (rc.bottom - 421 )/ 2, 0),
		//0, 0, 0,
		1, 
		true, true);
	pSystemBackground->EventProcess = InGamePauseMenu_returnEvent_whitespace;
	
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

	cPopup *pPauseImage = new cPopup;
	pPauseImage->Setup(
		"data/UI/InGamePauseMenu",
		"NW_InGameSetting_PauseText.png", // 362  421
		D3DXVECTOR3((rc.right - 200) / 2, (rc.bottom - 46) / 2, 0),
		0, -150, 0,
		1,
		true, true);
	pSystemBack->cButtonPushBack(pPauseImage);
	
	{ // button
		cButton *pSystem_continue = new cButton;
		pSystemBackground->cButtonPushBack(pSystem_continue);
		pSystem_continue->Setup("data/UI/InGamePauseMenu/CONTINUE", "NW_InGameSetting_ContinueButton_Idle.png",
			pSystem_continue->GetUpPopUp()->GetPosition(),
			30, 90, 0,
			1,
			true, true);
		pSystem_continue->EventProcess = InGamePauseMenu_returnEvent;
		
		cButton *pSystem_OptionBtn = new cButton;
		pSystemBackground->cButtonPushBack(pSystem_OptionBtn);
		pSystem_OptionBtn->Setup("data/UI/InGamePauseMenu/SETTING", "NW_InGameSetting_SettingButton_Idle.png",
			pSystem_continue->GetUpPopUp()->GetPosition(),
			30, 170, 0, 
			1, 
			true, true);
		pSystem_OptionBtn->EventProcess = InGamePauseMenu_OptionBtnEvent;

		cButton *pSystem_ToStartBtn= new cButton;
		pSystemBackground->cButtonPushBack(pSystem_ToStartBtn);
		pSystem_ToStartBtn->Setup("data/UI/InGamePauseMenu/BackToStart", "NW_InGameSetting_BackToStartButton_Idle.png",
			pSystem_continue->GetUpPopUp()->GetPosition(),
			30, 250, 0, 
			1, 
			true, true);
		pSystem_ToStartBtn->EventProcess = InGamePauseMenu_ToStartEvent;

		cButton *pSystem_END_Btn = new cButton;
		pSystemBackground->cButtonPushBack(pSystem_END_Btn);
		pSystem_END_Btn->Setup("data/UI/InGamePauseMenu/END", "NW_InGameSetting_EndButton_Idle.png",
			pSystem_END_Btn->GetUpPopUp()->GetPosition(), 
			30, 330, 0, 
			1, 
			true, true);
		pSystem_END_Btn->EventProcess = InGamePauseMenu_END_Game;
	} // top button

	// cPopup* pOptionPopUp = Setup_Setting_popup(pOptionBackGround);
	
	if (!btn)
	{
		EventManager->Attach(pSystemBack);
		ObjectManager->AddUIChild(pSystemBack);
	}
	else if (btn)
	{
		pSystemBack->PowerOnOff_OnlySelf();
		btn->cButtonPushBack(pSystemBack);
	}
	
	return pSystemBack;
}

void InGamePauseMenu_returnEvent_whitespace(EventType message, cPopup* popup)
{
	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = popup->GetPosition();
	float width = popup->GetImageInfoWidth() * popup->GetPercent();
	float height = popup->GetImageInfoHeight() *  popup->GetPercent();

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x > cur.x || cur.x > btnPosition.x + width ||
			btnPosition.y > cur.y || cur.y > btnPosition.y + height)
		{
			{
				popup->SetStateChange(enum_On);
			}
		}
	}

	break;
	case EventType::EVENT_LBUTTONUP:
	{
		if (popup->GetState() == enum_On)
		{
			if (btnPosition.x > cur.x || cur.x > btnPosition.x + width ||
				btnPosition.y > cur.y || cur.y > btnPosition.y + height)
			{
				popup->SetStateChange(enum_Off);
				popup->GetTopPopUp()->PowerOnOff_List_OnlySelf(false);
				updateblock = false;
			}
		}
	}
	break;
	};//switch End
}

void InGamePauseMenu_returnEvent(EventType message, cPopup* btn)
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

		if (button->GetState() == enum_Hover)//m_State는 Hover이면서 m_PreState는 On/Off일 경우
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/CONTINUE/NW_InGameSetting_ContinueButton_Over.png");
			button->SetPreState(enum_Hover);
		}
		if (button->GetState() == enum_On)
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/CONTINUE/NW_InGameSetting_ContinueButton_Pressed.png");
			button->SetPreState(enum_On);
		}
		else if (button->GetState() == enum_Off)
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/CONTINUE/NW_InGameSetting_ContinueButton_Idle.png");
			button->SetPreState(enum_Off);
		}
		//case EVENT_MOVE End:
	}
	break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/CONTINUE/NW_InGameSetting_ContinueButton_Pressed.png");
				button->SetStateChange(enum_On);
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
					button->ChangeSprite("data/UI/InGamePauseMenu/CONTINUE/NW_InGameSetting_ContinueButton_Idle.png");
					button->SetStateChange(enum_Off);

					button->GetTopPopUp()->PowerOnOff_List_OnlySelf(false);
					updateblock = false;
				}
			}
		}
	}
	break;
	};//switch End
}

void InGamePauseMenu_OptionBtnEvent(EventType message, cPopup* btn)
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


		if (button->GetState() == enum_Hover)//m_State는 Hover이면서 m_PreState는 On/Off일 경우
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/SETTING/NW_InGameSetting_SettingButton_Over.png");
		}
		else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
		{
			if (button->GetState() == enum_On)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/SETTING/NW_InGameSetting_SettingButton_Pressed.png");
			}
			if (button->GetState() == enum_Off)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/SETTING/NW_InGameSetting_SettingButton_Idle.png");
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
				button->ChangeSprite("data/UI/InGamePauseMenu/SETTING/NW_InGameSetting_SettingButton_Pressed.png");
				button->SetStateChange(enum_On);
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
					button->ChangeSprite("data/UI/InGamePauseMenu/SETTING/NW_InGameSetting_SettingButton_Idle.png");
					button->SetStateChange(enum_Off);
					
					button->GetTopPopUp()->PowerOnOff_List_OnlySelf();
				}
			}
		}
	}
	break;
	};//switch End
}

void InGamePauseMenu_ToStartEvent(EventType message, cPopup* btn)
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

		
		if (button->GetState() == enum_Hover)//m_State는 Hover이면서 m_PreState는 On/Off일 경우
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/BackToStart/NW_InGameSetting_BackToStartButton_Over.png");
		}
		else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
		{
			if (button->GetState() == enum_On)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/BackToStart/NW_InGameSetting_BackToStartButton_Pressed.png");
			}
			if (button->GetState() == enum_Off)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/BackToStart/NW_InGameSetting_BackToStartButton_Idle.png");
			}
		}//case EVENT_MOVE End:

		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/BackToStart/NW_InGameSetting_BackToStartButton_Pressed.png");
				button->SetStateChange(enum_On);
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
					button->ChangeSprite("data/UI/InGamePauseMenu/BackToStart/NW_InGameSetting_BackToStartButton_Idle.png");
					button->SetStateChange(enum_Off);
					button->GetUpPopUp()->GetUpPopUp()->PowerOnOff_OnlySelf(false);
					
					g_pSceneManager->ChangeScene(SceneType::SCENE_TITLE);
				}
			}
		}
	}
	break;
	};//switch End
}

void InGamePauseMenu_END_Game(EventType message, cPopup* btn)
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

		if (button->GetState() == enum_Hover)//m_State는 Hover이면서 m_PreState는 On/Off일 경우
		{
			button->ChangeSprite("data/UI/InGamePauseMenu/END/NW_InGameSetting_EndButton_Over.png");
		}
		else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
		{
			if (button->GetState() == enum_On)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/END/NW_InGameSetting_EndButton_Pressed.png");
			}
			if (button->GetState() == enum_Off)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/END/NW_InGameSetting_EndButton_Idle.png");
			}
		}//case EVENT_MOVE End:

		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->ChangeSprite("data/UI/InGamePauseMenu/END/NW_InGameSetting_EndButton_Pressed.png");
				button->SetStateChange(enum_On);
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
					button->ChangeSprite("data/UI/InGamePauseMenu/END/NW_InGameSetting_EndButton_Idle.png");
					button->SetStateChange(enum_Off);
					
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
