#include <Windows.h>
#include "Subject.h"
#include "stdafx.h"

#pragma once
#include <queue>
#include "Button.h"



#define EventManager cEventManager::GetInstance()

//»Ÿ 107 108 19 110
enum class  EventType
{
	EVENT_NULL = 9999,
	EVENT_MOVE = 0,
	EVENT_WHEELUP = 1,
	EVENT_WHEELDOWN = 2,
	EVENT_LBUTTONDOWN = 3,
	EVENT_LBUTTONDLBC = 4,
	EVENT_RBUTTONDOWN = 5,
	EVENT_RBUTTONDLBC = 6,
	EVENT_LBUTTONUP = 7,
	EVENT_RBUTTONUP = 8,

	EVENT_LDRAG = 10,
	EVENT_RDRAG = 11,

	EVENT_JUMP = 32,
	EVENT_TAP = 9,
	EVENT_ENTER = 13,
	EVENT_SHIFT = 16,
	EVENT_CTRL = 17,
	EVENT_ALT = 18,
	EVENT_ESC = 27,
	EVENT_HOME_WINDOWS = 36,

	EVENT_ARROW_LEFT = 65,
	EVENT_ARROW_UP = 87,
	EVENT_ARROW_RIGHT = 68,
	EVENT_ARROW_DOWN = 83,

	EVENT_NUMPAD_1 = 49,
	EVENT_NUMPAD_2 = 50,
	EVENT_NUMPAD_3 = 51,
	EVENT_NUMPAD_4 = 52,
	EVENT_NUMPAD_5 = 53,
	EVENT_NUMPAD_6 = 54,
	EVENT_NUMPAD_7 = 55,
	EVENT_NUMPAD_8 = 56,
	EVENT_NUMPAD_9 = 57,
	EVENT_KEYBOARD_R = 0x52,
	EVENT_KEYUP = 128, // 0x80 

	EVENT_CREATE_PALADIN = 129,

	EVENT_PLUS_HP = 130,
	EVENT_MINUS_HP = 131,
	EVENT_PLUS_STAMINA = 132,
	EVENT_MINUS_STAMINA = 133,
	
	EVENT_SKYBEEZ = 134,
	EVENT_DRAGONFOOT = 135,

	EVENT_ASPACE = 136,
	EVENT_DSPACE = 137,
	EVENT_WSPACE = 138,
	EVENT_SSPACE = 139,

	EVENT_UPLEFT	= 140,
	EVENT_UPRIGHT	= 141,
	EVENT_DOWNLEFT	= 142,
	EVENT_DOWNRIGHT = 143,

};

class cEventManager
	:public cSubject
{
	Singletone(cEventManager);

private:
	std::queue<EventType> m_Queue;
	
	//std::map<int, EventType> m_mapEvent;

	D3DXVECTOR2 m_vCur;
	D3DXVECTOR2 m_vPrev;
	bool		m_IsLDrag;
	bool		m_IsRDrag;

	std::thread *EventThread;

public:
	void InputEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void Notify() override;
	//now
	D3DXVECTOR2 GetMouseCurrent();
	D3DXVECTOR2 GetMousePrev();
	void PushQueue(EventType message);
	void Update();
	bool m_IsOBBButten;
};
