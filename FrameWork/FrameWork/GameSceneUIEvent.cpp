#include "stdafx.h"
#include "GameSceneUIEvent.h"
#include "EventManager.h"
#include "PopUp.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"


//이름 수정할 것
void Opton_ESC_Event(EventType message, cPopup* btn)
{
	bool child_power = 0;
	int currentSceneType = g_pSceneManager->GetCurrentSceneType();

	// TODO 디버깅용 코드
	
	switch (message)
	{
	case EventType::EVENT_ESC:
	{
		if (currentSceneType == SceneType::SCENE_BOSS_1 || currentSceneType == SceneType::SCENE_BOSS_2)
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

			cout << "GameScene Event ESC pushed" << endl;
		}
	}
	break;
		
	default:
		break;
	}
}
