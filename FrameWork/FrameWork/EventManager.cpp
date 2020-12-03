#include "stdafx.h"
#include "basic.h"
#include "EventManager.h"
#include "Observer.h"


void cEventManager::InputEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// MOUSE EVENT
	case WM_MOUSEWHEEL:
	{
		bool zDelta = GET_WHEEL_DELTA_WPARAM(wParam) / 120 == 1 ?
			true : false;
		if (zDelta)
			m_Queue.push((EventType)0x01);
		else
			m_Queue.push((EventType)0x02);
		Notify();
		//Notify();
	}
	break;
	case WM_MOUSEMOVE:
	{
		D3DXVECTOR2 vMousePos;
		vMousePos.x = LOWORD(lParam);
		vMousePos.y = HIWORD(lParam);

		if (wParam == MK_LBUTTON)
		{
			m_IsDrag = true;
			m_vPrev = vMousePos;
		}
		
		m_vCur = vMousePos;
			
		m_Queue.push((EventType)0x00);
		Notify();
		return;
	}
	break;
	case WM_LBUTTONDBLCLK:
		m_Queue.push((EventType)0x04);
		Notify();
		break;
	case WM_LBUTTONDOWN:
		m_Queue.push((EventType)0x03);
		Notify();
		break;
	case WM_RBUTTONDBLCLK:
		m_Queue.push(EventType(0x06));
		Notify();
		break;
	case WM_RBUTTONDOWN:
		m_Queue.push(EventType(0x05));
		Notify();
		break;
	case WM_KEYDOWN:
	{
		m_Queue.push((EventType)wParam);
		Notify();
	}
	break;
	case WM_KEYUP:
	{
		m_Queue.push((EventType)0x80);
		Notify();
		if (GetAsyncKeyState(wParam) & 0x81)
		{
			cout << "Stay";
		}

	}
	case WM_LBUTTONUP:
	{
		if(m_IsDrag)
		{
			m_IsDrag = false;
			m_Queue.push((EventType)0x0A);	
		}
		m_Queue.push((EventType)0x07);

	}
	case WM_RBUTTONUP:
		Notify();		
		break;
	}
}


void cEventManager::Notify()
{
	while(!m_Queue.empty())
	{
		for (int i = 0; i < m_vecObservers.size(); ++i)
		{
			m_vecObservers.at(i)->Update(m_Queue.front());
		}
		m_Queue.pop();	
	}
}


D3DXVECTOR2 cEventManager::GetMouseCurrent()
{
	return m_vCur;
}

D3DXVECTOR2 cEventManager::GetMousePrev()
{
	return m_vPrev;
}




cEventManager::cEventManager()
	: m_IsDrag(false)
{
	//for (int i = 0x00; i < 0xFF; i++)
	//{
	//	m_mapEvent[i] = EventType::EVENT_NULL;
	//}
	//
	//m_mapEvent[0x00] = EventType::EVENT_MOVE;
	//m_mapEvent[0x01] = EventType::EVENT_WHEELUP;
	//m_mapEvent[0x02] = EventType::EVENT_WHEELDOWN;
	//m_mapEvent[0x03] = EventType::EVENT_LBUTTONDOWN;  
	//m_mapEvent[0x04] = EventType::EVENT_LBUTTONDLBC;
	//m_mapEvent[0x05] = EventType::EVENT_RBUTTONDOWN;  
	//m_mapEvent[0x06] = EventType::EVENT_RBUTTONDLBC;
	//m_mapEvent[0x07] = EventType::EVENT_LBUTTONUP;
	//m_mapEvent[0x08] = EventType::EVENT_RBUTTONUP;

	//m_mapEvent[0x0A] = EventType::EVENT_DRAG;

	//m_mapEvent[0x20] = EventType::EVENT_JUMP;
	//m_mapEvent[0x09] = EventType::EVENT_TAP;
	//m_mapEvent[0x0D] = EventType::EVENT_ENTER;
	//m_mapEvent[0x10] = EventType::EVENT_SHIFT;
	//m_mapEvent[0x11] = EventType::EVENT_CTRL;
	//m_mapEvent[0x12] = EventType::EVENT_ALT;
	//m_mapEvent[0x1B] = EventType::EVENT_ESC;
	//m_mapEvent[0x24] = EventType::EVENT_HOME_WINDOWS;

	//m_mapEvent[0x25] = EventType::EVENT_ARROW_LEFT;
	//m_mapEvent[0x26] = EventType::EVENT_ARROW_UP;
	//m_mapEvent[0x27] = EventType::EVENT_ARROW_RIGHT;
	//m_mapEvent[0x28] = EventType::EVENT_ARROW_DOWN;
	//
	//m_mapEvent[0x41] = EventType::EVENT_ARROW_LEFT;
	//m_mapEvent[0x57] = EventType::EVENT_ARROW_UP;
	//m_mapEvent[0x44] = EventType::EVENT_ARROW_RIGHT;
	//m_mapEvent[0x53] = EventType::EVENT_ARROW_DOWN;

	//m_mapEvent[0x31] = EventType::EVENT_NUMPAD_1;
	//m_mapEvent[0x32] = EventType::EVENT_NUMPAD_2;
	//m_mapEvent[0x33] = EventType::EVENT_NUMPAD_3;
	//m_mapEvent[0x34] = EventType::EVENT_NUMPAD_4;
	//m_mapEvent[0x35] = EventType::EVENT_NUMPAD_5;
}

cEventManager::~cEventManager()
{
	for (int i = 0; i < m_vecObservers.size(); ++i)
	{
		m_vecObservers[i] = NULL;
	}
	m_vecObservers.clear();

}