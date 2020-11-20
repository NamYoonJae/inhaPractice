#pragma once
#include "EventManager.h"
#include "PopUp.h"
#include "TextureManager.h"
#include "SceneManager.h"

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
				button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)
			{
				button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Off);
			}
			*/

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
				button->ChangeSprite("data/UI/btn-med-down.png");
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width) 
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height) 
			{
				//���� -> enum_Off ���·� ����
				//�̹��� enum_Off�� ����
				//���� �������� �� �̵�
				button->SetStateChange(enum_Hover);
				button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
				g_pSceneManager->ChangeScene();
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
				button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
			button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
			button->SetPreState(enum_Off);
			}
			*/

		}//case EVENT_MOVE End:

		break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				//���� ���� ��
				//���� �������� �� �̵�

			}
		}
	}
	break;
	/*
	case EventType::EVENT_WHEELUP:
	break;
	case EventType::EVENT_WHEELDOWN:
	break;
	case EventType::EVENT_LBUTTONDOWN:
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
				button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
			button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
			button->SetPreState(enum_Off);
			}
			*/

		}//case EVENT_MOVE End:

		break;


	case EventType::EVENT_LBUTTONUP:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				//���� ���� ��
				//���� �������� �� �̵�

			}
		}
	}
	break;
	/*
	case EventType::EVENT_WHEELUP:
	break;
	case EventType::EVENT_WHEELDOWN:
	break;
	case EventType::EVENT_LBUTTONDOWN:
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

void EndGameBtnEvent(EventType message, cPopUp* btn)
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
				button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
				button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
			{
			button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
			button->SetPreState(enum_Off);
			}
			*/

		}//case EVENT_MOVE End:

		break;


	case EventType::EVENT_LBUTTONUP:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
		{
			if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				//���� ���� ��
				//���� �������� �� �̵�

			}
		}
	}
	break;
	/*
	case EventType::EVENT_WHEELUP:
	break;
	case EventType::EVENT_WHEELDOWN:
	break;
	case EventType::EVENT_LBUTTONDOWN:
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