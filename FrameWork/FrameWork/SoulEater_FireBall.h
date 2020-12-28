#include "SoulEaterState.h"
#pragma once
class cSoulEater_FireBall :
	public cSoulEaterState
{
private:
	int m_nIndex;
	int m_nSoundIndex;
	DWORD m_dwDelayTime;
	DWORD m_dwPrevTime;
	D3DMATERIAL9 m_PrevMstl;

public:
	cSoulEater_FireBall();
	cSoulEater_FireBall(cDragonSoulEater*);
	~cSoulEater_FireBall();
	void handle() override;
};

