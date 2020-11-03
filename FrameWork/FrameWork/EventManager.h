#include <Windows.h>
#include "Subject.h"
#include "stdafx.h"
#pragma once
#include <queue>



#define InputcEventManager cEventManager::GetInstance()

//»Ÿ 107 108 19 110

class cEventManager
	:public cSubject
{
	Singletone(cEventManager);
private:
	std::queue<std::string> m_Queue;
	D3DXVECTOR2 m_Point;
	std::map<int, std::string> m_mapEvent;
public:
	void InputEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void Notify() override;
	D3DXVECTOR2 GetMousePosition();

};
