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
			m_IsLDrag = true;
			m_vPrev = vMousePos;
		}
		if (wParam == MK_RBUTTON)
		{
			m_IsRDrag = true;
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
		SendMessage(g_hWnd, WM_SETCURSOR, 140, NULL);
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
		if (GetKeyState('0') & 0x8000)
			m_IsOBBButten = !m_IsOBBButten;
		
		if (wParam == (int)EventType::EVENT_ARROW_UP ||
			wParam == (int)EventType::EVENT_ARROW_DOWN ||
			wParam == (int)EventType::EVENT_ARROW_LEFT ||
			wParam == (int)EventType::EVENT_ARROW_RIGHT)
		{
			return;
		}

		m_Queue.push((EventType)wParam);
		Notify();
		break;
	}
	break;
	case WM_KEYUP:
	{
		m_Queue.push((EventType)0x80);
		Notify();
	}
	case WM_LBUTTONUP:
	{
		if(m_IsLDrag)
		{
			m_IsLDrag = false;
			m_Queue.push((EventType)0x0A);	
		}
		m_Queue.push((EventType)0x07);
		SendMessage(g_hWnd, WM_SETCURSOR, 139, NULL);
	}
	case WM_RBUTTONUP:
	{
		if (m_IsRDrag)
		{
			m_IsRDrag = false;
			m_Queue.push((EventType)0x0B);
		}
		m_Queue.push(EventType::EVENT_RBUTTONUP);
		Notify();		
	}
		break;
	}
}


void cEventManager::Notify()
{
	while(!m_Queue.empty())
	{
		for (int i = 0; i < m_vecObservers.size(); ++i)
		{
			//cout << static_cast<int>(m_Queue.front()) << endl;
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

void cEventManager::PushQueue(EventType message)
{
	m_Queue.push(message);
}


void cEventManager::Update()
{

	WORD wStateSPACE = ::GetKeyState(VK_SPACE);
	WORD wStateW = ::GetKeyState('W');
	WORD wStateA = ::GetKeyState('A');
	WORD wStateS = ::GetKeyState('S');
	WORD wStateD = ::GetKeyState('D');

	if (wStateSPACE & 0x80)
	{
		if (wStateW & 0x80)
		{
			PushQueue(EventType::EVENT_WSPACE);
			Notify();
		}
		else if (wStateA & 0x80)
		{
			PushQueue(EventType::EVENT_ASPACE);
			Notify();
		}
		else if (wStateS & 0x80)
		{
			PushQueue(EventType::EVENT_SSPACE);
			Notify();
		}
		else if (wStateD & 0x80)
		{
			PushQueue(EventType::EVENT_DSPACE);
			Notify();
		}
	}
	

	if (wStateW & 0x80)
	{
		// 우측위 좌측위 W<->S
		if (wStateA & 0x80)
		{
			// 좌측위
			PushQueue(EventType::EVENT_UPLEFT);
			//cout << "A W" << endl;
		}
		else if (wStateS & 0x80)
		{
			if (wStateW & 0x01)
			{
				PushQueue(EventType::EVENT_ARROW_DOWN);
			}
			else
			{
				PushQueue(EventType::EVENT_ARROW_UP);
			}
		}
		else if (wStateD & 0x80)
		{
			// 우측위	
			PushQueue(EventType::EVENT_UPRIGHT);
			//cout << "D W" << endl;

		}
		else
		{
			PushQueue(EventType::EVENT_ARROW_UP);
		}
		
		Notify();
		return;
	}
	else if (wStateA & 0x80)
	{
		// 좌측하단 A<->D
		if (wStateD & 0x80)
		{
			if (wStateA & 0x01)
			{
				PushQueue(EventType::EVENT_ARROW_RIGHT);
			}
			else
			{
				PushQueue(EventType::EVENT_ARROW_LEFT);
			}
		}
		else if (wStateS & 0x80)
		{
			// 좌아래
			PushQueue(EventType::EVENT_DOWNLEFT);
			//cout << "A S" << endl;

		}
		else
		{
			PushQueue(EventType::EVENT_ARROW_LEFT);
		}

		Notify();
		return;
	}
	else if (wStateD & 0x80)
	{
		// 우측하단 
		if (wStateS & 0x80)
		{
			// 우아래
			//cout << "D S" << endl;
			PushQueue(EventType::EVENT_DOWNRIGHT);
		}
		else
		{
			PushQueue(EventType::EVENT_ARROW_RIGHT);
		}
		Notify();
		return;
	}
	else if (wStateS & 0x80)
	{
		PushQueue(EventType::EVENT_ARROW_DOWN);
		Notify();
		return;
	}
}


cEventManager::cEventManager()
	: m_IsLDrag(false)
	, m_IsRDrag(false)
	, m_IsOBBButten(false)
{
}

cEventManager::~cEventManager()
{
	for (int i = 0; i < m_vecObservers.size(); ++i)
	{
		m_vecObservers[i] = NULL;
	}
	m_vecObservers.clear();

}