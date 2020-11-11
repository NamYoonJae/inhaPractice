#include <Windows.h>
#include "Subject.h"
#include "stdafx.h"
#pragma once
#include <queue>
#include "Button.h"



#define EventManager cEventManager::GetInstance()

//»Ÿ 107 108 19 110

class cEventManager
	:public cSubject
{
	Singletone(cEventManager);
private:
	std::queue<std::string> m_Queue;
	std::map<int, std::string> m_mapEvent;

	//
	D3DXVECTOR2 m_vCur;
	D3DXVECTOR2 m_vPrev;
	bool		m_IsDrag;

public:
	void InputEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void Notify() override;

	//now
	D3DXVECTOR2 GetMouseCurrent();
	D3DXVECTOR2 GetMousePrev();

	void ButtonEvent(string message, cPopUp*);

};
