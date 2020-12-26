#include "SoulEaterState.h"
#pragma once
class cSoulEater_Die :
	public cSoulEaterState
{
private:
	DWORD m_dwStartTime;
public:
	cSoulEater_Die();
	cSoulEater_Die(cDragonSoulEater*);
	~cSoulEater_Die();
	void handle() override;
};

