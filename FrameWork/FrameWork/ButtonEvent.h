#pragma once
#include "EventManager.h"
#include "PopUp.h"
#include "TextureManager.h"

void BtnStartEvent(EventType message, cPopUp * btn)
{
	
	/*
	cButton* button = (cButton*)btn;

	switch (message)
	{
	case EventType::EVENT_MOVE:
	{

		D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
		D3DXVECTOR3 btnPosition = button->GetPosition();
		float width = button->GetImageInfoWidth();
		float height = button->GetImageInfoHeight();

			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width)
			{
				if (btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
				{
					if (button->GetCurHoverCheck() == false)
					{
						button->ChangeHoverCheck();	//on���·� ü����
					}
				}
				else
				{
					if (button->GetCurHoverCheck() == true)
					{
						button->ChangeHoverCheck(); //off���·� ü����
					}
				}

			}
			else
			{
				if (button->GetCurHoverCheck() == true)
				{
					button->ChangeHoverCheck();	//off ���·� ü����
				}
			}


			if (button->GetPreHoverCheck() != button->GetCurHoverCheck())
			{
				if (button->GetCurHoverCheck() == true) 
				{
					button->SetStateChange(enum_Hover);
					button->ChangeSprite("data/UI/TitleScene/��ư Ȱ��ȭ ������ ����.png");
					button->SetPreHoverCheck();
				}
				else 
				{
					button->SetStateChange(enum_Off);
					button->ChangeSprite("data/UI/TitleScene/��ư ��Ȱ��ȭ ������ ����.png");
					button->SetPreHoverCheck();
				}
			}

	}//case EVENT_MOVE End
	break;

	case EventType::EVENT_LBUTTONDOWN:
	{

	}
	break;

	default:
		break;
	}
	*/
}

void BtnExitEvent(EventType message, cPopUp* btn)
{
	cButton* button = (cButton*)btn;

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
		break;

	default:
		break;
	}
}