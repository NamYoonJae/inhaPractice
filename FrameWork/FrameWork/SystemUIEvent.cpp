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
		"����â ��� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 1,
		true, true);

	cPopUp *pOptionBtnBackGround = new cPopUp;
	pOptionBtnBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"���� ���� ���� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);
	
	{ // top button
		cButton *pOption_setButton = new cButton;
		pOption_setButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), -50, -60, 0, 0.8, true, true);
		pOptionBtnBackGround->cButtonPushBack(pOption_setButton);
		pOption_setButton->EventProcess = SysWindow_OptionBtnEvent;

		cButton *pOption_ControlButton = new cButton;
		pOption_ControlButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 200, -60, 0, 0.8, true, true);
		pOptionBtnBackGround->cButtonPushBack(pOption_ControlButton);
		pOption_ControlButton->EventProcess = Option_ReturnTitle;

		cButton *pOption_CameraButton = new cButton;
		pOption_CameraButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
			D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 450, -60, 0, 0.8, true, true);
		pOptionBtnBackGround->cButtonPushBack(pOption_CameraButton);
		pOption_CameraButton->EventProcess = SysWindow_ExitGame;
	} // top button

	{ // menu popup & button
		cPopUp *pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOptionBackGround->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0,0,0))->EventProcess = Sys_TmpBarMoveEvent;

		pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOptionBackGround->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� on ����������.png",
			D3DXVECTOR3(rc.right / 2 - 24, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pSetupNamePopup->cButtonPushBack(pChkButton);
		// TODO �̺�Ʈ �߰�
		// BarButton->EventProcess = �̺�Ʈ
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
					button->SetStateChange(enum_Hover);	//on���·� ü����
				}

			}
			else
			{
				if (button->GetState() != enum_Off)
				{
					button->SetStateChange(enum_Off); //off���·� ü����
				}
			}
		}
		else
		{
			if (button->GetState() != enum_Off)
			{
				button->SetStateChange(enum_Off);	//off ���·� ü����
			}
		}

		if (button->GetPreState() != button->GetState())
		{
			if (button->GetState() == enum_Hover)//m_State�� Hover�̸鼭 m_PreState�� On/Off�� ���
			{
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
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
					button->SetStateChange(enum_Hover);	//on���·� ü����
				}

			}
			else
			{
				if (button->GetState() != enum_Off)
				{
					button->SetStateChange(enum_Off); //off���·� ü����
				}
			}
		}
		else
		{
			if (button->GetState() != enum_Off)
			{
				button->SetStateChange(enum_Off);	//off ���·� ü����
			}
		}

		if (button->GetPreState() != button->GetState())
		{
			if (button->GetState() == enum_Hover) //m_State�� Hover�̸鼭 m_PreState�� On/Off�� ���
			{
				//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
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
					// TODO exit �ִ� �κ�
					exit(0);
				}
			}
		}
	}
	break;
	};//switch End
}

// ��ȯ�Ǵ� cButton �����͸� ����Ͽ� �¾��� ��ü�� Eventprocess�� �Լ� �ֱ�, �������ڴ� �ϴ� ���̾ ��
cButton* Setup_BarGaugePopupBtn(cPopUp* popup, D3DXVECTOR3 position)
{
	cPopUp * pBarGauge = new cPopUp;
	pBarGauge->Setup(
		"data/UI/ConfigurationSettings",
		"����â �� ������ ������ ����.png",
		popup->GetPosition(),
		-100, 60, 0, // TODO json ���� �Ľ̹޾Ƽ� ��ġ���Ͱ� �־��ֱ�
		1,
		true, true);
	popup->cButtonPushBack(pBarGauge);

	// TODO UI���� �ּ� Ȯ��
	// pBarGauge�� ��ġ�� ���͸� �������� pBarButton�� ��ġ�� ������,
	// pBarGauge�� ��ġ�� pBarButton�� ��ġ�� �������� 0 ~ 100�� ���� ��ȯ�ϰ� ��
	// ��ȯ�ϴ� ������ ��Ŭ������ ���۵Ǵ� �κ�
	cButton * pBarButton = new cButton;
	pBarButton->Setup("data/UI/ConfigurationSettings", "����â �ٰ����� ���� ��ư ����������.png",
		pBarGauge->GetPosition(),
		385, -8, 0, // << x�� ��ġ�� ��ȭ�ϰ�
					// pBarButton�� x���� ���� -15 ~ 385, 4��ŭ �����϶����� �̺�Ʈ���� 1��ŭ ���� �����ϱ�
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
				// TODO json ���⼭ �ٷ� �����Ұ�
				// ���� ��ȯ�ؾ��ϳ�? �׷� ��ȯ�� ���� ���ΰ���?
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
