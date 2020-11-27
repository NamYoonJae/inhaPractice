#include "stdafx.h"
#include "GameSceneUIEvent.h"
#include "EventManager.h"
#include "PopUp.h"

#include "Button.h"


//이름 수정할 것
void Opton_ESC_Event(EventType message, cPopUp* btn)
{
	bool child_power = 0;
	
	switch (message)
	{
	case EventType::EVENT_ESC:
		for (size_t i = 0; i < btn->GetPopUpListSize(); i++)
		{
			cPopUp * pchild = btn->GetPopupBtn(i);
			if(pchild)
			{
				if (pchild->GetPowerState())
					child_power = true;
				break; // << for
			}
		}

		if (child_power)
		{
			btn->GetPopupBtn(0)->PowerOnOffSelf(false);
			btn->GetPopupBtn(1)->PowerOnOff(false);
		}
		else
		{
			btn->GetPopupBtn(0)->PowerOnOff(true);
		}
		
		cout << "ESC pushed" << endl;
	default:
		break;
	}
}
