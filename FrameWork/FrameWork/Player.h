#pragma once
#include "Observer.h"
#include "stdafx.h"

class Player :
	public cObserver
{
private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	float m_fRotY;
public:
	Player();
	~Player();
public:
	void Update(std::string) override;
};

