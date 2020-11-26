#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "SystemUIEvent.h"
#include "OptionUIEvent.h"

//#include "SceneManager.h"
//#include "TextureManager.h"



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

	cPopUp *pOptionBtnBackGround = new cPopUp;
	pOptionBtnBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"설정 내용 변경 사이즈조정.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);
	
	{ // top button
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
	} // top button

	{ // menu popup & button
		cPopUp *pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOptionBackGround->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0,0,0))->EventProcess = Sys_TmpBarMoveEvent;

		pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"설정항목 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOptionBackGround->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off 체크형 백그라운드 on 사이즈조정.png",
			D3DXVECTOR3(rc.right / 2 - 24, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pSetupNamePopup->cButtonPushBack(pChkButton);
		// TODO 이벤트 추가
		// BarButton->EventProcess = 이벤트
	} // menu popup & button
	

	Setup_OptionWindow(pOptionBackGround);
	
	if (!btn)
	{
		EventManager->Attach(pOptionBackGround);
		ObjectManager->AddUIChild(pOptionBackGround);
	}
	else
	{
		pOptionBackGround->PowerOnOff();
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
					button->GetUpPopUp()->GetUpPopUp()->vecListPowerOnOff();
				}
			}
		}
	}
	break;
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
cButton* Setup_BarGaugePopupBtn(cPopUp* popup, D3DXVECTOR3 position)
{
	cPopUp * pBarGauge = new cPopUp;
	pBarGauge->Setup(
		"data/UI/ConfigurationSettings",
		"설정창 바 게이지 사이즈 조정.png",
		popup->GetPosition(),
		-100, 60, 0, // TODO json 파일 파싱받아서 위치벡터값 넣어주기
		1,
		true, true);
	popup->cButtonPushBack(pBarGauge);

	// TODO UI관련 주석 확인
	// pBarGauge의 위치를 벡터를 기준으로 pBarButton의 위치를 제한함,
	// pBarGauge의 위치와 pBarButton의 위치를 기준으로 0 ~ 100의 값을 반환하게 함
	// 반환하는 시점은 좌클릭업이 시작되는 부분
	cButton * pBarButton = new cButton;
	pBarButton->Setup("data/UI/ConfigurationSettings", "설정창 바게이지 조절 버튼 사이즈조정.png",
		pBarGauge->GetPosition(),
		385, -8, 0, // << x의 위치만 변화하게
					// pBarButton의 x값의 범위 -15 ~ 385, 4만큼 움직일때마다 이벤트에서 1만큼 값을 변경하기
		1, 
		true, true);
	pBarGauge->cButtonPushBack(pBarButton);

	return pBarButton;
}

void Sys_TmpBarMoveEvent(EventType message, cPopUp* btn)
{
	cButton* button = (cButton*)btn;

	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();

	D3DXVECTOR3 btnPosition = button->GetPosition();
	float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	float btn_height = button->GetImageInfoHeight() *  button->GetPercent();

	switch (message)
	{
	case EventType::EVENT_MOVE:
		if(button->GetState() == enum_On)
		{
			if (crnt_cur.x >= btn->GetUpPopUp()->GetPosition().x &&
				crnt_cur.x <= btn->GetUpPopUp()->GetPosition().x + btn->GetUpPopUp()->GetImageInfoWidth())
			{
				D3DXVECTOR2 vec2distance = crnt_cur - prev_cur;
				vec2distance.y = 0;
				btn->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json 여기서 바로 저장할것
				// 값을 반환해야하나? 그럼 반환한 값은 어디로가지?
			}
		}
	  //case EVENT_MOVE End:
		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				prev_cur = EventManager->GetMouseCurrent();
				button->SetStateChange(enum_On);
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		button->SetStateChange(enum_Off);
	}
	break;
	};//switch End
}
