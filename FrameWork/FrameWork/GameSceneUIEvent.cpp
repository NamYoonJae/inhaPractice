#include "stdafx.h"
//#include "GameScene.h"
//#include "SceneManager.h"
#include "EventManager.h"
#include "PopUp.h"
#include "Button.h"
#include "GameSceneUIEvent.h"
//#include "TitleSceneBtnEvent.h"

#pragma once

// 이름 수정할 것
void OnOff_Event(EventType message, cPopUp* btn)
{
	switch (message)
	{
	case EventType::EVENT_ESC:
		btn->GetForefather()->GetPopupBtn()->PowerOnOff();
		cout << "ESC pushed" << endl;
		
	default:
		break;
	}
}
