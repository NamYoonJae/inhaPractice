#include "stdafx.h"
#include "GameSceneUIEvent.h"
#include "EventManager.h"
#include "PopUp.h"

#include "Button.h"


//이름 수정할 것
void Opton_ESC_Event(EventType message, cPopup* btn)
{
	bool child_power = 0;
	
	switch (message)
	{
	case EventType::EVENT_ESC:
	{
		for (size_t i = 0; i < btn->GetPopUpListSize(); i++)
		{
			cPopup * pchild = btn->GetPopupBtn(i);
			if (pchild)
			{
				child_power = pchild->GetPowerState();

				if (child_power == true)
				break; // << for
			}
		}

		if (child_power)
		{
			btn->PowerOnOff_List_OnlySelf(false);
			
			//btn->GetPopupBtn(0)->PowerOnOff_OnlySelf(false);
			//btn->GetPopupBtn(1)->PowerOnOff_OnlySelf(false);
		}
		else
		{
			btn->GetPopupBtn(0)->PowerOnOff_OnlySelf(true);
			btn->GetPopupBtn(1)->PowerOnOff_OnlySelf(false);
		}

		cout << "ESC pushed" << endl;
	}
	break;
	default:
		break;
	}
}
