#include "stdafx.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "TitleSceneBtnEvent.h"

void StartGameBtnEvent(EventType message, cPopUp* btn)
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
				button->ChangeSprite("data/UI/TitleScene/START/NW_StartButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/TitleScene/START/NW_StartButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/TitleScene/START/NW_StartButton_Idle.png");
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
				//���� -> enum_On ���·� ����
				//�̹��� enum_On���� ����
				//�̹��� ����
				button->SetStateChange(enum_On);
				button->ChangeSprite("data/UI/TitleScene/START/NW_StartButton_Pressed.png");
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
					//���� -> enum_Off ���·� ����
					//�̹��� enum_Off�� ����
					//������ ����
					//���� �������� �� �̵�
					button->SetStateChange(enum_Hover);
					button->ChangeSprite("data/UI/TitleScene/START/NW_StartButton_Over.png");
					g_pSceneManager->ChangeScene();
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

void ContinueGameBtnEvent(EventType message, cPopUp* btn)
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
				button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Idle.png");
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
				button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Pressed.png");
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
					button->SetStateChange(enum_Hover);
					button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
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

void SetupGameBtnEvent(EventType message, cPopUp* btn)
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
				button->ChangeSprite("data/UI/TitleScene/SETTING/NW_SettingButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{

				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/TitleScene/SETTING/NW_SettingButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/TitleScene/SETTING/NW_SettingButton_Idle.png");
					button->SetPreState(enum_Off);
				}

			}

		}
	}
	break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->SetStateChange(enum_On);
				button->ChangeSprite("data/UI/TitleScene/SETTING/NW_SettingButton_Pressed.png");
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
					button->SetStateChange(enum_Hover);
					button->ChangeSprite("data/UI/TitleScene/SETTING/NW_SettingButton_Over.png");

					button->GetForefather()->PowerOnOff();
					// TODO add function
					Setup_SystemWindow();
					//Setup_OptionWindow();

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

void ExitGameBtnEvent(EventType message, cPopUp* btn)
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
				button->ChangeSprite("data/UI/TitleScene/END/NW_EndButton_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/TitleScene/END/NW_EndButton_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/TitleScene/END/NW_EndButton_Idle.png");
					button->SetPreState(enum_Off);
				}

			}

		}
	}
	break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				button->SetStateChange(enum_On);
				button->ChangeSprite("data/UI/TitleScene/END/NW_EndButton_Pressed.png");
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
					button->SetStateChange(enum_Hover);
					button->ChangeSprite("data/UI/TitleScene/END/NW_EndButton_Over.png");
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


/*-- addtional funtion 20.11.21. 15:30 --*/
void Setup_OptionWindow() //
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	/*
	cPopUp *pTitleBackGround = new cPopUp;
	pTitleBackGround->Setup(
		"data/UI/TitleScene",
		"NW_Background.png",
		D3DXVECTOR3(0, 0, 0),
		2,
		true, true);
	*/
	cPopUp *pOptionBackGround = new cPopUp;
	pOptionBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"����â ��� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 1,
		true, true);
	//pTitleBackGround->cButtonPushBack(pOptionBackGround);

	cPopUp *pOptionBtnBackGround = new cPopUp;
	pOptionBtnBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"���� ���� ���� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);

	cButton *pOption_setButton = new cButton;
	pOption_setButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), -50, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_setButton);
	pOption_setButton->EventProcess = Option_SetBtnEvent;


	cButton *pOption_ControlButton = new cButton;
	pOption_ControlButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 115, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_ControlButton);
	pOption_ControlButton->EventProcess = Option_ControlBtnEvent;

	cButton *pOption_CameraButton = new cButton;
	pOption_CameraButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 280, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_CameraButton);
	pOption_CameraButton->EventProcess = Option_CameraBtnEvent;

	cButton *pOption_AudioButton = new cButton;
	pOption_AudioButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 445, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_AudioButton);
	pOption_AudioButton->EventProcess = Option_AudioBtnEvent;

	// TODO �׽�Ʈ ������ ����
	// ������ ��ư �ӽ÷� ����
	cButton *pExitButton = new cButton;
	pExitButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� off ����������.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 570, -110, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pExitButton);
	pExitButton->EventProcess = Option_ReturnTitle;

	EventManager->Attach(pOptionBackGround);
	ObjectManager->AddUIChild(pOptionBackGround);
}

void Option_SetBtnEvent(EventType message, cPopUp* btn)
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
					button->SetStateChange(enum_Hover);
					cout << "Option Set Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
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

void Option_ControlBtnEvent(EventType message, cPopUp* btn)
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
					button->SetStateChange(enum_Hover);
					cout << "Option Control Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
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

void Option_CameraBtnEvent(EventType message, cPopUp* btn)
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
					button->SetStateChange(enum_Hover);
					cout << "Option Camera Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
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

void Option_AudioBtnEvent(EventType message, cPopUp* btn)
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
					button->SetStateChange(enum_Hover);
					cout << "Option Audio Button Clicked" << endl;
					//button->ChangeSprite("data/UI/TitleScene/CONTINUE/NW_ContinueButton_Over.png");
					//g_pSceneManager->ChangeScene();
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

void Option_ReturnTitle(EventType message, cPopUp* btn)
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
					button->SetStateChange(enum_Hover);
					cout << "Exit Button Clicked" << endl;

					g_pSceneManager->LoadScene(0);
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

void Setup_SystemWindow()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	/*
	cPopUp *pTitleBackGround = new cPopUp;
	pTitleBackGround->Setup(
		"data/UI/TitleScene",
		"NW_Background.png",
		D3DXVECTOR3(0, 0, 0),
		2,
		true, true);
	*/
	cPopUp *pOptionBackGround = new cPopUp;
	pOptionBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"����â ��� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 400, rc.bottom / 2 - 256, 0), 1,
		true, true);
	//pTitleBackGround->cButtonPushBack(pOptionBackGround);

	cPopUp *pOptionBtnBackGround = new cPopUp;
	pOptionBtnBackGround->Setup(
		"data/UI/ConfigurationSettings",
		"���� ���� ���� ����������.png",
		D3DXVECTOR3(rc.right / 2 - 300, rc.bottom / 2 - 100, 0), 1,
		true, true);
	pOptionBackGround->cButtonPushBack(pOptionBtnBackGround);

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

	EventManager->Attach(pOptionBackGround);
	ObjectManager->AddUIChild(pOptionBackGround);
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
					button->GetForefather()->PowerOnOff();
					Setup_OptionWindow();
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
					// TODO exit �ִ� �κ�
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