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
		if(GetKeyState((int)EventType::EVENT_ARROW_RIGHT) & 0x8001 ||
			GetKeyState((int)EventType::EVENT_ARROW_LEFT) & 0x8001 ||
			GetKeyState((int)EventType::EVENT_ARROW_UP) & 0x8001 || 
			GetKeyState((int)EventType::EVENT_ARROW_DOWN) & 0x8001)
		{
			if(GetKeyState((int)EventType::EVENT_JUMP) & 0x8000)
			{
				m_Queue.push(EventType::EVENT_JUMP);
				Notify();
				break;
			}
		}
		//else if(GetKeyState((int)EventType::EVENT_ARROW_RIGHT) & 0x8001 ||
		//	GetKeyState((int)EventType::EVENT_ARROW_LEFT) & 0x8001 ||
		//	GetKeyState((int)EventType::EVENT_ARROW_UP) & 0x8001 ||
		//	GetKeyState((int)EventType::EVENT_ARROW_DOWN) & 0x01)
		//{
		//	g_pLogger->ValueLog(__FUNCTION__, __LINE__, "f", wParam);
		//	m_Queue.push((EventType)wParam);
		//	Notify();
		//	break;
		//}

		m_Queue.push((EventType)wParam);
		Notify();
		break;

			
		if (GetKeyState('0') & 0x8000)
			m_IsOBBButten = !m_IsOBBButten;
		
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
	// TEST
	return;
	WORD wStateW	 = ::GetKeyState('W');
	WORD wStateA	 = ::GetKeyState('A');
	WORD wStateS	 = ::GetKeyState('S');
	WORD wStateD	 = ::GetKeyState('D');
	WORD wStateSPACE = ::GetKeyState(VK_SPACE);

	BYTE byW = LOBYTE(wStateW);
	BYTE byA = LOBYTE(wStateA);
	BYTE byS = LOBYTE(wStateS);
	BYTE byD = LOBYTE(wStateD);
	BYTE bySPACE = HIBYTE(wStateSPACE);

	//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "W ", (float)byW);
	//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "A ", (float)byA);
	//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "S ", (float)byS);
	//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "D ", (float)byD);

	if(bySPACE & 0x01)
	{
		if (byW & 0x01)
		{
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "W ", (float)byW);
		}
		else if (byA & 0x01)
		{
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "A ", (float)byA);
		}
		else if (byS & 0x01)
		{
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "S ", (float)byS);
		}
		else if (byD & 0x01)
		{
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "D ", (float)byD);
		}
	}
	

	//https://startcoding.tistory.com/81
	//https://www.google.com/search?newwindow=1&sxsrf=ALeKk01mlMgS5LTkovLL6tMARuNEjutFfQ%3A1608796684793&ei=DErkX7D6L5KFr7wPq82goAI&q=api+%ED%82%A4%EB%B3%B4%EB%93%9C+%EB%8F%99%EC%8B%9C+%EC%9E%85%EB%A0%A5&oq=API+%EB%8F%99%EC%8B%9C+&gs_lcp=CgZwc3ktYWIQAxgBMgIIADIGCAAQCBAeOgcIIxDqAhAnOgQIABAeOgYIABAKEB46BQgAELEDOggIABCxAxCDAToECCMQJzoECAAQCjoECAAQQzoHCAAQFBCHAjoGCAAQBRAeOgUIIRCgAVCsg5gBWKymmAFg4a-YAWgJcAB4AoAB-AKIAe8ckgEIMC4xNC4zLjKYAQCgAQGqAQdnd3Mtd2l6sAEKwAEB&sclient=psy-ab
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