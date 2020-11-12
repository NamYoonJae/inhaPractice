#pragma once
#include "EventManager.h"
#include "PopUp.h"
#include "TextureManager.h"

void BtnStartEvent(EventType message, cPopUp * btn)
{
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
					button->SetStateChange(enum_Hover);
					
				}
				else
				{
					button->SetStateChange(enum_Off);
				}
			}
			else
			{
				button->SetStateChange(enum_Off);
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