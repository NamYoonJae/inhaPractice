#include<Windows.h>
#include<iostream>
#pragma once
#include "Observer.h"
#include "stdafx.h"

class UI :
	public cObserver
{
private:
	D3DXVECTOR2 m_PrevPos;
	RECT  m_Rc;
public:
	UI(RECT rc);
	~UI();
	void Update(std::string) override;
	bool isEscape() { return true; }
};

