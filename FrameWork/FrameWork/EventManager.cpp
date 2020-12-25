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
			//cout << "space + W" << endl; 
			PushQueue(EventType::EVENT_WSPACE);
			Notify();

		}
		else if (wStateA & 0x80)
		{
			//cout << "space + A" << endl; 
			PushQueue(EventType::EVENT_ASPACE);
			Notify();
		}
		else if (wStateS & 0x80)
		{
			//cout << "space + S" << endl; 
			PushQueue(EventType::EVENT_SSPACE);
			Notify();
		}
		else if (wStateD & 0x80)
		{
			//cout << "space + D" << endl; 
			PushQueue(EventType::EVENT_DSPACE);
			Notify();
		}
	}
	else if (wStateW & 0x80)
	{
		//cout << "W stay push" << endl;
		PushQueue(EventType::EVENT_ARROW_UP);
		Notify();
	}
	else if (wStateA & 0x80)
	{
		//cout << "A stay push" << endl;
		PushQueue(EventType::EVENT_ARROW_LEFT);
		Notify();
	}
	else if (wStateS & 0x80)
	{
		//cout << "S stay push" << endl;
		PushQueue(EventType::EVENT_ARROW_DOWN);
		Notify();
	}
	else if (wStateD & 0x80)
	{
		//cout << "D stay push" << endl;
		PushQueue(EventType::EVENT_ARROW_RIGHT);
		Notify();
	}

}


cEventManager::cEventManager()
	: m_IsDrag(false)
	, m_IsOBBButten(true)
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