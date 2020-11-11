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
			m_Queue.push(m_mapEvent[0x01]);
		else
			m_Queue.push(m_mapEvent[0x02]);

		Notify();
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
			
		m_Queue.push(m_mapEvent[0x00]);
		Notify();
		
		return;
	}
	break;
	case WM_LBUTTONDBLCLK:
		m_Queue.push(m_mapEvent[0x04]);
		break;
	case WM_LBUTTONDOWN:
		m_Queue.push(m_mapEvent[0x03]);
		Notify();
		break;
	case WM_RBUTTONDBLCLK:
		m_Queue.push(m_mapEvent[0x06]);
		break;
	case WM_RBUTTONDOWN:
		m_Queue.push(m_mapEvent[0x05]);
		break;
	
	case WM_KEYDOWN:
	{
		// MK_SHIF , MK_CONTROL not yet
		m_Queue.push(m_mapEvent[wParam]);

		Notify();
		break;
	}
	break;

	case WM_LBUTTONUP:
	{
		if(m_IsDrag)
		{
			m_IsDrag = false;
			m_Queue.push(m_mapEvent[0x0A]);	
		}
		m_Queue.push(m_mapEvent[0x07]);

	}
	case WM_RBUTTONUP:
		Notify();		
		break;
	
	}
}


void cEventManager::Notify()
{
	while (!m_Queue.empty())
	{
		std::string Message = m_Queue.front();

		for (int i = 0; i < m_vecObservers.size(); ++i)
		{
			if(m_vecObservers[i] != NULL)
			{
				m_vecObservers.at(i)->Update(Message);
			}
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

void cEventManager::ButtonEvent(string message, cPopUp * btn)
{
	/*
	if (message == "EVENT_LBUTTONDOWN")
	{
		cout << "���콺 ��Ŭ��" << endl;
	}
	*/
}


cEventManager::cEventManager()
	: m_IsDrag(false)
{
	for (int i = 0x00; i < 0xFF; i++)
	{
		m_mapEvent[i] = " ";
	}
	
	m_mapEvent[0x00] = "EVENT_MOVE";  
	m_mapEvent[0x01] = "EVENT_WHEELUP";
	m_mapEvent[0x02] = "EVENT_WHEELDOWN";
	m_mapEvent[0x03] = "EVENT_LBUTTONDOWN";  
	m_mapEvent[0x04] = "EVENT_LBUTTONDLBC";
	m_mapEvent[0x05] = "EVENT_RBUTTONDOWN";  
	m_mapEvent[0x06] = "EVENT_RBUTTONDLBC";
	m_mapEvent[0x07] = "EVENT_LBUTTONUP";
	m_mapEvent[0x08] = "EVENT_RBUTTONUP";

	m_mapEvent[0x0A] = "EVENT_DRAG";
	
	m_mapEvent[0x10] = "EVENT_NULL";
	m_mapEvent[0x20] = "EVENT_JUMP";
	m_mapEvent[0x09] = "EVENT_TAP";
	m_mapEvent[0x0D] = "EVENT_ENTER";
	m_mapEvent[0x10] = "EVENT_SHIFT";
	m_mapEvent[0x11] = "EVENT_CTRL";
	m_mapEvent[0x12] = "EVENT_ALT";
	m_mapEvent[0x1B] = "EVENT_MENU"; //esc
	m_mapEvent[0x24] = "EVENT_HOME_WINDOWS";

	m_mapEvent[0x25] = "EVENT_ARROW_LEFT";
	m_mapEvent[0x26] = "EVENT_ARROW_UP";
	m_mapEvent[0x27] = "EVENT_ARROW_RIGHT";
	m_mapEvent[0x28] = "EVENT_ARROW_DOWN";
	
	m_mapEvent[0x41] = "EVENT_ARROW_LEFT";
	m_mapEvent[0x57] = "EVENT_ARROW_UP";
	m_mapEvent[0x44] = "EVENT_ARROW_RIGHT";
	m_mapEvent[0x53] = "EVENT_ARROW_DOWN";

	m_mapEvent[0x31] = "EVENT_NUMPAD_1";
	m_mapEvent[0x32] = "EVENT_NUMPAD_2";
	m_mapEvent[0x33] = "EVENT_NUMPAD_3";
	m_mapEvent[0x34] = "EVENT_NUMPAD_4";
	m_mapEvent[0x35] = "EVENT_NUMPAD_5";
}

cEventManager::~cEventManager()
{
	for (int i = 0; i < m_vecObservers.size(); ++i)
	{
		m_vecObservers[i] = NULL;
	}
	m_vecObservers.clear();

}