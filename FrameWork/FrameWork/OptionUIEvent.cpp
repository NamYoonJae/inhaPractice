#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "OptionUIEvent.h"

#include "BtnUIEvent.h"

//#include "SceneManager.h"
//#include "TextureManager.h"


void Setup_OptionWindow(cPopUp* btn)
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

	cButton *pOption_setButton = new cButton;
	pOption_setButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), -50, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_setButton);
	pOption_setButton->EventProcess = Option_SetBtnEvent;
	{ // setBtnList
		cPopUp *pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_setButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0, 0, 0))->EventProcess = GaugeBarMoveEvent;

		pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 100, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_setButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� on ����������.png",
			D3DXVECTOR3(rc.right / 2 - 24, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_setButton->cButtonPushBack(pChkButton);
		// TODO �̺�Ʈ �߰�
		// BarButton->EventProcess = �̺�Ʈ

		pChkButton->GetUpPopUp()->vecListPowerOnOff(false);
	}

	cButton *pOption_ControleButton = new cButton;
	pOption_ControleButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 115, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_ControleButton);
	pOption_ControleButton->EventProcess = Option_ControlBtnEvent;
	{ // ControleList
		//// TODO �ӽ÷� �����ΰ� �����ϱ�
		//// �ð��� Ȯ���� ���� x������ 10�� �о����
		//cPopUp *pSetupNamePopup = new cPopUp;
		//pSetupNamePopup->Setup(
		//	"data/UI/ConfigurationSettings",
		//	"�����׸� ����������.png",
		//	D3DXVECTOR3(rc.right / 2 - 110, rc.bottom / 2 - 50, 0), 1,
		//	true, true);
		//pOption_ControleButton->cButtonPushBack(pSetupNamePopup);

		//Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0, 0, 0))->EventProcess = GaugeBarMoveEvent;

		//pSetupNamePopup = new cPopUp;
		//pSetupNamePopup->Setup(
		//	"data/UI/ConfigurationSettings",
		//	"�����׸� ����������.png",
		//	D3DXVECTOR3(rc.right / 2 - 110, rc.bottom / 2 + 50, 0), 1,
		//	true, true);
		//pOption_ControleButton->cButtonPushBack(pSetupNamePopup);

		//cButton * pChkButton = new cButton;
		//pChkButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� on ����������.png",
		//	D3DXVECTOR3(rc.right / 2 - 34, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		//pOption_ControleButton->cButtonPushBack(pChkButton);
		//// TODO �̺�Ʈ �߰�
		//// BarButton->EventProcess = �̺�Ʈ

		//pChkButton->GetUpPopUp()->vecListPowerOnOff(false);
	}

	cButton *pOption_CameraButton = new cButton;
	pOption_CameraButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 280, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_CameraButton);
	pOption_CameraButton->EventProcess = Option_CameraBtnEvent;
	{ // CameraBtnList
	  // TODO �ӽ÷� �����ΰ� �����ϱ�
	  // �ð��� Ȯ���� ���� x������ 10�� �о����
		cPopUp *pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 120, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_CameraButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0, 0, 0))->EventProcess = GaugeBarMoveEvent;

		pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 120, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_CameraButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� on ����������.png",
			D3DXVECTOR3(rc.right / 2 - 44, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_CameraButton->cButtonPushBack(pChkButton);
		// TODO �̺�Ʈ �߰�
		// BarButton->EventProcess = �̺�Ʈ

		pChkButton->GetUpPopUp()->vecListPowerOnOff(false);
	}

	cButton *pOption_AudioButton = new cButton;
	pOption_AudioButton->Setup("data/UI/ConfigurationSettings", "����â ž��ư ������ ����.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 445, -60, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pOption_AudioButton);
	pOption_AudioButton->EventProcess = Option_AudioBtnEvent;
	{ // AudioBtnList
	  // TODO �ӽ÷� �����ΰ� �����ϱ�
	  // �ð��� Ȯ���� ���� x������ 10�� �о����
		cPopUp *pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 130, rc.bottom / 2 - 50, 0), 1,
			true, true);
		pOption_AudioButton->cButtonPushBack(pSetupNamePopup);

		Setup_BarGaugePopupBtn(pSetupNamePopup, D3DXVECTOR3(0, 0, 0))->EventProcess = GaugeBarMoveEvent;

		pSetupNamePopup = new cPopUp;
		pSetupNamePopup->Setup(
			"data/UI/ConfigurationSettings",
			"�����׸� ����������.png",
			D3DXVECTOR3(rc.right / 2 - 130, rc.bottom / 2 + 50, 0), 1,
			true, true);
		pOption_AudioButton->cButtonPushBack(pSetupNamePopup);

		cButton * pChkButton = new cButton;
		pChkButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� on ����������.png",
			D3DXVECTOR3(rc.right / 2 - 54, rc.bottom / 2 + 120, 0), 0, 0, 0, 1, true, true);
		pOption_AudioButton->cButtonPushBack(pChkButton);
		// TODO �̺�Ʈ �߰�
		// BarButton->EventProcess = �̺�Ʈ

		pChkButton->GetUpPopUp()->vecListPowerOnOff(false);
	}
	
	// TODO �׽�Ʈ ������ ����
	// ������ ��ư �ӽ÷� ����
	cButton *pExitButton = new cButton;
	pExitButton->Setup("data/UI/ConfigurationSettings", "on,off üũ�� ��׶��� off ����������.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 570, -110, 0, 0.8, true, true);
	pOptionBtnBackGround->cButtonPushBack(pExitButton);
	pExitButton->EventProcess = Option_ReturnTitle;

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
							button->GetUpPopUp()->GetPopupBtn(i)->vecListPowerOnOff(false);
						else cout << "NULL INDEX" << i << endl; // NULL�� �ε��� üũ
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->vecListPowerOnOff(false);
						else cout << "NULL INDEX" << i << endl; // NULL�� �ε��� üũ
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->vecListPowerOnOff(false);
						else cout << "NULL INDEX" << i << endl; // NULL�� �ε��� üũ
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
					for (int i = 0; i < button->GetUpPopUp()->GetPopUpListSize() - 1; i++)
					{
						if (button->GetUpPopUp()->GetPopupBtn(i))
							button->GetUpPopUp()->GetPopupBtn(i)->vecListPowerOnOff(false);
						else cout << "NULL INDEX" << i << endl; // NULL�� �ε��� üũ
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

					cPopUp * pPopup0 = button->GetTopPopUp();
					if(pPopup0)
					pPopup0->vecListPowerOnOff();
				}
			}
		}
	}
	break;
	};//switch End
}
