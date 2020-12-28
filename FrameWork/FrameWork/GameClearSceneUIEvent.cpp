#include "stdafx.h"
#include "GameClearSceneUIEvent.h"
#include "EventManager.h"
#include "Popup.h"

void GameClearSceneRetryBtnEvent(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() * button->GetPercent();

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
				button->ChangeSprite("data/UI/GameClear/NW_Retry/NW_Retry_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/GameClear/NW_Retry/NW_Retry_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/GameClear/NW_Retry/NW_Retry_Idle.png");
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
				button->ChangeSprite("data/UI/GameClear/NW_Retry/NW_Retry_Pressed.png");
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
					button->ChangeSprite("data/UI/GameClear/NW_Retry/NW_Retry_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}

	}
	break;
	};//switch End
}

void GameClearSceneMainMenuBtnEvent(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() * button->GetPercent();

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
				button->ChangeSprite("data/UI/GameClear/NW_MainMenu/NW_MainMenu_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/GameClear/NW_MainMenu/NW_MainMenu_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/GameClear/NW_MainMenu/NW_MainMenu_Idle.png");
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
				button->ChangeSprite("data/UI/GameClear/NW_MainMenu/NW_MainMenu_Pressed.png");
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
					button->ChangeSprite("data/UI/GameClear/NW_MainMenu/NW_MainMenu_Over.png");
					//g_pSceneManager->ChangeScene();
				}
			}
		}

	}
	break;
	};//switch End
}

void GameClearSceneExitBtnEvent(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	float width = button->GetImageInfoWidth() * button->GetPercent();
	float height = button->GetImageInfoHeight() * button->GetPercent();

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
				button->ChangeSprite("data/UI/GameClear/NW_Exit/NW_Exit_Over.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/GameClear/NW_Exit/NW_Exit_Pressed.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/GameClear/NW_Exit/NW_Exit_Idle.png");
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
				button->ChangeSprite("data/UI/GameClear/NW_Exit/NW_Exit_Pressed.png");
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
					button->ChangeSprite("data/UI/GameClear/NW_Exit/NW_Exit_Over.png");
					exit(0);
				}
			}
		}

	}
	break;
	};//switch End
}
