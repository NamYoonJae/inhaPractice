#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "SettingUIEvent.h"

#include "BtnUIEvent.h"
#include "jsonManager.h"

//#include "SceneManager.h"
//#include "TextureManager.h"

// 반환되는 포인터는 최상단 팝업의 포인터 좌표
cPopup* Setup_Setting_popup(cPopup* btn)
{
	cout << "Setup_Setting_popup called" << endl;
	
	JSON_Object * p_json_object_UI = g_p_jsonManager->get_json_object_UI();
	JSON_Object * p_json_object_setting = g_p_jsonManager->get_json_object_Setting();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopup *pOptionBack = new cPopup;
	pOptionBack->Setup(
		"data/UI/Settings",
		"NW_InGameSetting_Back.png",
		D3DXVECTOR3(0, 0, 0),
		1,
		true, true);
	
	cPopup *pOptionBackGround = new cPopup;
	pOptionBack->cButtonPushBack(pOptionBackGround);
	pOptionBackGround->Setup(
		"data/UI/Settings",
		"NW_Setting_UI.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0),
		1,
		true, true);
	pOptionBackGround->EventProcess = Setting_popup_ReturnEvent_whitespace;

#pragma region barSilder
	// TODO 아래 바게이지는 나중에 이벤트를 따로 줄 것.
	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(137, 378, 0))->EventProcess = BarSliderMoveEvent;
	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(137, 441, 0))->EventProcess = BarSliderMoveEvent;
	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(137, 508, 0))->EventProcess = BarSliderMoveEvent;

	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(490, 119, 0))->EventProcess = BarSliderMoveEvent2;
	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(490, 196, 0))->EventProcess = BarSliderMoveEvent2;
	Setup_BarSliderPopupBtn(pOptionBackGround, D3DXVECTOR3(490, 280, 0))->EventProcess = BarSliderMoveEvent2;
#pragma endregion barSilder

#pragma region chk_Button
	// TODO json Test
	// 이미지의 크기는 23 x 23
	
	cButton *pChk_MiniMap = new cButton;
	pOptionBackGround->cButtonPushBack(pChk_MiniMap);
	// pExitButton->Setup("data/UI/Settings", "NW_Setting_ToggleButton_Off.png",
	pChk_MiniMap->Setup(
		json_Fuction::object_get_pChar(p_json_object_UI, "UI/Settings/directory"),
		json_Fuction::object_get_pChar(p_json_object_UI, "UI/Settings/ToggleButton_On/filename"),
		//D3DXVECTOR3(0, 0, 0), // 생성시 json 파싱받아보기
		pChk_MiniMap->GetUpPopUp()->GetPosition(),
		0, 0, 0,
		1, true, true); // 스케일은 임시로 10
	
	// TODO 이벤트 추가
	// pExitButton->EventProcess = Tmp_CheckEvent;
#pragma endregion chk_Button

#pragma region exit
	
	//// TODO 빈공간 클릭 이벤트 후 삭제
	//// 나가기 버튼 임시로 생성
	//cButton *pExitButton = new cButton;
	//pExitButton->Setup("data/UI/Settings", "임시 나가기 버튼.png",
	//	D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 620, -110, 0, 0.8, true, true);
	//pOptionBackGround->cButtonPushBack(pExitButton);
	//pExitButton->EventProcess = Setting_popup_ReturnEvent;
	
#pragma endregion exit

	if (!btn)
	{
		EventManager->Attach(pOptionBack);
		ObjectManager->AddUIChild(pOptionBack);
	}
	else if (btn)
	{
		pOptionBack->PowerOnOff_OnlySelf();
		btn->cButtonPushBack(pOptionBack);
	}

	return pOptionBack;
}


void Setting_popup_ReturnEvent_whitespace(EventType message, cPopup* popup)
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
				cout << "Setting Return Event Active... " << endl;

				cPopup * pPopup0 = popup->GetTopPopUp();
				for (size_t i = 0; i < pPopup0->GetPopUpListSize(); i++)
				{
					pPopup0->GetPopupBtn(i)->PowerOnOff_OnlySelf();
				}
			}
		}
	}
	break;
	};//switch End
}

void Setting_popup_ReturnEvent(EventType message, cPopup* popup)
{
	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = popup->GetPosition();
	float width = popup->GetImageInfoWidth() * popup->GetPercent();
	float height = popup->GetImageInfoHeight() *  popup->GetPercent();

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width &&
			btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
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
			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width &&
				btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				popup->SetStateChange(enum_Off);
				cout << "Exit Button Clicked" << endl;

				cPopup * pPopup0 = popup->GetTopPopUp();
				for (size_t i = 0; i < pPopup0->GetPopUpListSize(); i++)
				{
					pPopup0->GetPopupBtn(i)->PowerOnOff_OnlySelf();
				}
			}
		}
	}
	break;
	};//switch End
}


// legacy function
cPopup* Setup_OptionWindow_Legacy(cPopup* btn)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopup *pOptionBackGround = new cPopup;
	pOptionBackGround->Setup(
		"data/UI/Settings",
		"설정창 배경 사이즈조정.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 
		1,
		true, true);

	cPopup *pOptionBtnBackGround = new cPopup;
	pOptionBtnBackGround->Setup(
		"data/UI/Settings",
		"설정 내용 변경 사이즈조정.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 
		1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);

	cButton *pOption_setButton = new cButton;
	pOption_setButton->Setup("data/UI/Settings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0),
		-50, -60, 0,
		0.8, 
		true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_setButton);
	pOption_setButton->EventProcess = Option_SetBtnEvent_Legacy;
	{ // setBtnList
		cPopup *pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_setButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn_Legacy(pSetupNamePopup, D3DXVECTOR3(-100, 60, 0))->EventProcess = GaugeBarMoveEvent_Legacy;

		pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_setButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off 체크형 백그라운드 on 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 24, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_setButton->cButtonPushBack(pChkButton);
		// TO DO 이벤트 추가
		// BarButton->EventProcess = 이벤트

		pChkButton->GetUpPopUp()->PowerOnOff_List(false);
	}

	cButton *pOption_ControleButton = new cButton;
	pOption_ControleButton->Setup("data/UI/Settings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 115, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_ControleButton);
	pOption_ControleButton->EventProcess = Option_ControlBtnEvent_Legacy;

	cButton *pOption_CameraButton = new cButton;
	pOption_CameraButton->Setup("data/UI/Settings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 280, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_CameraButton);
	pOption_CameraButton->EventProcess = Option_CameraBtnEvent_Legacy;
	{ // CameraBtnList
	  // TO DO 임시로 움직인거 조정하기
	  // 시각적 확인을 위해 x축으로 10씩 밀어놨음
		cPopup *pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/Settings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 120, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_CameraButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn_Legacy(pSetupNamePopup, D3DXVECTOR3(-100, 60, 0))->EventProcess = GaugeBarMoveEvent_Legacy;

		pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/Settings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 120, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_CameraButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/Settings", "on,off 체크형 백그라운드 on 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 44, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_CameraButton->cButtonPushBack(pChkButton);
		// TO DO 이벤트 추가
		// BarButton->EventProcess = 이벤트

		pChkButton->GetUpPopUp()->PowerOnOff_List(false);
	}

	cButton *pOption_AudioButton = new cButton;
	pOption_AudioButton->Setup("data/UI/Settings", "설정창 탑버튼 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 445, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_AudioButton);
	pOption_AudioButton->EventProcess = Option_AudioBtnEvent_Legacy;
	{ // AudioBtnList
	  // TO DO 임시로 움직인거 조정하기
	  // 시각적 확인을 위해 x축으로 조금씩 밀어놨음
		cPopup *pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 130, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_AudioButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn_Legacy(pSetupNamePopup, D3DXVECTOR3(-100, 60, 0))->EventProcess = GaugeBarMoveEvent_Legacy;

		pSetupNamePopup = new cPopup;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 130, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_AudioButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off 체크형 백그라운드 on 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 54, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_AudioButton->cButtonPushBack(pChkButton);
		// TO DO 이벤트 추가
		// BarButton->EventProcess = 이벤트

		pChkButton->GetUpPopUp()->PowerOnOff_List(false);
	}
	
	// TO DO 정식으로 편입됨..?
	// 나가기 버튼 임시로 생성
	cButton *pExitButton = new cButton;
	pExitButton->Setup("data/UI/Settings", "on,off 체크형 백그라운드 off 사이즈조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 570, -110, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pExitButton);
	pExitButton->EventProcess = Setting_popup_ReturnEvent;

	if (!btn)
	{
		EventManager->Attach(pOptionBackGround);
		ObjectManager->AddUIChild(pOptionBackGround);
	}
	else if (btn)
	{
		pOptionBackGround->PowerOnOff_OnlySelf();
		btn->cButtonPushBack(pOptionBackGround);
	}

	return pOptionBackGround;
}

void Option_SetBtnEvent_Legacy(EventType message, cPopup* btn)
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


		}
		//case EVENT_MOVE End:
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->PowerOnOff_List(false);
						else cout << "NULL INDEX" << i << endl; // NULL값 인덱스 체크
					}
					button->PowerOnOff(true);

					button->SetStateChange(enum_Hover);
					cout << "Option Set Button Clicked" << endl;
					
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}
	}
	break;
	};//switch End
}

void Option_ControlBtnEvent_Legacy(EventType message, cPopup* btn)
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->PowerOnOff_List(false);
						else cout << "NULL INDEX" << i << endl; // NULL값 인덱스 체크
					}
					button->PowerOnOff(true);
					
					button->SetStateChange(enum_Hover);
					cout << "Option Control Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}
	}
	break;
	};//switch End

}

void Option_CameraBtnEvent_Legacy(EventType message, cPopup* btn)
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->PowerOnOff_List(false);
						else cout << "NULL INDEX" << i << endl; // NULL값 인덱스 체크
					}
					button->PowerOnOff(true);

					button->SetStateChange(enum_Hover);
					cout << "Option Camera Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}
	}
	break;
	};//switch End
}

void Option_AudioBtnEvent_Legacy(EventType message, cPopup* btn)
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->PowerOnOff_List(false);
						else cout << "NULL INDEX" << i << endl; // NULL값 인덱스 체크
					}
					button->PowerOnOff(true);
					
					button->SetStateChange(enum_Hover);
					cout << "Option Audio Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}
	}
	break;
	};//switch End
}
