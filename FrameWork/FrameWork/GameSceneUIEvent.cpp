#include "stdafx.h"
#include "GameOverSceneBtnEvent.h"
#include "GameSceneUIEvent.h"
#include "EventManager.h"
#include "PopUp.h"
#include "Button.h"


// �̸� ������ ��
void Ingame_ESC_Event(EventType message, cPopUp* btn)
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
