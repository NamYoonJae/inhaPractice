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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
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
					//�ȶ�򿡰� TROPIES::TROPIES_Beez ����(EVENTTYPE::TROPIES_Beez �߻� ���� �ȶ���� Update���� ���� ����)
					//�ϴ��� ������ ���� ����ǰ ��ü ����
					//���� Reset���� ����ǰ ���þ��� ���� popup /button ��� ����
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
				button->ChangeSprite("data/UI/Trophies/NW_Attriselect_Backgound_On.png");
				button->SetPreState(enum_Hover);
			}
			else if (button->GetState() != enum_Hover)//m_State�� On/Off�̸鼭 m_PreState�� Hover�� ���
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
					//�ȶ�򿡰� TROPIES::TROPIES_DragonFoot ����
					g_pSceneManager->ChangeScene(SceneType::SCENE_BOSS_1);
					//������ ����ǰ ������ ���������� �̵�
				}
			}
		}

	}
	break;
	};//switch End
}
