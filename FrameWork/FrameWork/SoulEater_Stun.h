#pragma once
#include "SoulEaterState.h"
class cSoulEater_Stun :
	public cSoulEaterState
{
private:
	bool	m_IsAnimBlend;
	DWORD	m_dwStunTime;
public:
	cSoulEater_Stun();
	cSoulEater_Stun(cDragonSoulEater*,DWORD);
	~cSoulEater_Stun();
	void handle() override;
};

