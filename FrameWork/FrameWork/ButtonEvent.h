#pragma once
#include "EventManager.h"

void BtnStartEvent(EventType message, cPopUp * btn)
{
	cout << "���� ��ư Ŭ��" << endl;
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
	cout << "�����ư Ŭ��" << endl;
	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
		break;

	default:
		break;
	}
}