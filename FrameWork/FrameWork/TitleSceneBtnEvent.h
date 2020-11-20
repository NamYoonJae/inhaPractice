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
				button->ChangeSprite("data/UI/TitleScene/버튼 활성화 사이즈 조정.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)
			{
				button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
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
				//상태 -> enum_On 상태로 변경
				//이미지 enum_On으로 변경
				//이미지 변경
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
				//상태 -> enum_Off 상태로 변경
				//이미지 enum_Off로 변경
				//게임 시작으로 씬 이동
				button->SetStateChange(enum_Hover);
				button->ChangeSprite("data/UI/TitleScene/버튼 활성화 사이즈 조정.png");
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
				button->ChangeSprite("data/UI/TitleScene/버튼 활성화 사이즈 조정.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
			button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
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
				//상태 변경 후
				//게임 시작으로 씬 이동

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
				button->ChangeSprite("data/UI/TitleScene/버튼 활성화 사이즈 조정.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
			button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
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
				//상태 변경 후
				//게임 시작으로 씬 이동

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
				button->ChangeSprite("data/UI/TitleScene/버튼 활성화 사이즈 조정.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
				button->SetPreState(enum_Off);
			}
			/*
			else if (button->GetState() == enum_Off && button->GetPreState() == enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
			button->ChangeSprite("data/UI/TitleScene/버튼 비활성화 사이즈 조정.png");
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
				//상태 변경 후
				//게임 시작으로 씬 이동

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