#include "stdafx.h"
#include "UI.h"
#include "EventManager.h"

UI::UI(RECT rc) : m_Rc(rc)
{

}

UI::~UI()
{
}

void UI::Update(std::string message)
{
	using namespace std;
	if (message.compare("EVENT_MENU") == 0)
	{
		cout << "MENU Message UI Listen" << endl;
	}
	else if (message.compare("EVENT_MOVE") == 0)
	{
		D3DXVECTOR2 CurMouse = InputcEventManager->GetMousePosition();
		POINT Pt = { (long)CurMouse.x,(long)CurMouse.y };
		if (PtInRect(&m_Rc,Pt))
		{
			cout << "Mouse Position in UI ["<< CurMouse.x << ", "
				<< CurMouse.y << "]"<< endl;
		}

		m_PrevPos = CurMouse;
	}
	else if (message.compare("EVENT_NUMPAD_1") == 0)
	{
		cout << "KeyBoard 1" << endl;
	}
	else if (message.compare("EVENT_NUMPAD_2") == 0)
	{
		cout << "KeyBoard 2" << endl;
	}
	else if (message.compare("EVENT_LBUTTONDOWN") == 0)
	{
		cout << "MouseLB" << endl;
	}
	else if (message.compare("EVENT_LBUTTONDLBC") == 0)
	{
		cout << "Mouse LButton Double Click" << endl;
	}
	else if (message.compare("EVENT_RBUTTONDOWN") == 0)
	{
		cout << "MouseRB" << endl;
	}
}
