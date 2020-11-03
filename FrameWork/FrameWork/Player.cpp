#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player()
	:m_vPos(0, 0, 0) 
	,m_vDir(0, 0, -1)
	,m_fRotY(0.0f)
{

}
Player::~Player()
{
}

void Player::Update(std::string message)
{
	using namespace std;
	bool isDirRotation = false;
	bool isPosTanslation = false;

	if (message.compare("EVENT_ARROW_UP") == 0)
	{
		m_vPos += m_vDir * 0.1f;
		isPosTanslation = true;
	}
	else if (message.compare("EVENT_ARROW_DOWN") == 0)
	{
		m_vPos -= m_vDir * 0.1f;
		isPosTanslation = true;
	}
	else if (message.compare("EVENT_ARROW_LEFT") == 0)
	{
		m_fRotY += -0.1f; 
		isDirRotation = true;
	}
	else if (message.compare("EVENT_ARROW_RIGHT") == 0)
	{
		m_fRotY += +0.1f;
		isDirRotation = true;
	}
	else if (message.compare("Jump") == 0)
	{
		cout << "Jump" << endl;
	}

	if (isDirRotation)
	{
		D3DXMATRIXA16 matRy;
		D3DXMatrixRotationY(&matRy, m_fRotY);
		D3DXVec3TransformCoord(&m_vDir, &D3DXVECTOR3(0, 0, -1), &matRy);
		cout << "Direction [" << m_vDir.x << ", "
			<< m_vDir.y << ", " << m_vDir.z
			<< "]" << endl;
	}

	if (isPosTanslation)
	{
		cout << "Position [" << m_vPos.x << ", "
			<< m_vPos.y << ", " << m_vPos.z
			<< "]" << endl;

	}

}
