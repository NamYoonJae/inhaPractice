#pragma once
#include "EventManager.h"

void BtnStartEvent(EventType message, cPopUp * btn)
{
	cout << "시작 버튼 클릭" << endl;
	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
		break;

	default:
		break;
	}
}

void BtnExitEvent(EventType message, cPopUp* btn)
{
	cout << "종료버튼 클릭" << endl;
	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
		break;

	default:
		break;
	}
}