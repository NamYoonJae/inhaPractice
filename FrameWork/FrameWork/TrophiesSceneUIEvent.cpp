#include "stdafx.h"
#include "TrophiesSceneUIEvent.h"
#include "Scene.h"
#include "Trophies.h"

void FirstBizzBtnEvent(EventType message, cPopup * btn)
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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_Off.png");
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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
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
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
					//팔라딘에게 TROPIES::TROPIES_Beez 전송(EVENTTYPE::TROPIES_Beez 발생 시켜 팔라딘의 Update에서 받을 생각)
					//하늘의 구슬에 관한 전리품 객체 생성
					//그후 Reset에서 전리품 선택씬에 관한 popup /button 모두 제거
					g_pSceneManager->ChangeScene(SceneType::SCENE_BOSS_1);
					EventManager->PushQueue(EventType::EVENT_SKYBEEZ);
				}
			}
		}

	}
	break;
	};//switch End
}

void SecondBizzBtnEvent(EventType message, cPopup * btn)
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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State는 On/Off이면서 m_PreState는 Hover인 경우
			{
				if (button->GetState() == enum_On)
				{
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
					button->SetPreState(enum_On);
				}
				else if (button->GetState() == enum_Off)
				{
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_Off.png");
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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
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
					button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
					//팔라딘에게 TROPIES::TROPIES_DragonFoot 전송
					g_pSceneManager->ChangeScene(SceneType::SCENE_BOSS_1);
					//선택한 전리품 가지고 보스씬으로 이동
				}
			}
		}

	}
	break;
	};//switch End
}
