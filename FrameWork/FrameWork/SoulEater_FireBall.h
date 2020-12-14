#include "SoulEaterState.h"
#pragma once
class cSoulEater_FireBall :
	public cSoulEaterState
{
private:
	int m_nIndex;
	DWORD m_dwDelayTime;
	DWORD m_dwPrevTime;
public:
	cSoulEater_FireBall();
	cSoulEater_FireBall(cDragonSoulEater*);
	~cSoulEater_FireBall();
	void handle() override;
};

