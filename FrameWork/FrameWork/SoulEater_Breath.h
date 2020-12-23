#pragma once
#include "SoulEaterState.h"

class cSoulEater_Breath :
	public cSoulEaterState
{
private:
	DWORD m_dwStartTime;
	DWORD m_dwBreathDurationTime;
	bool m_IsAnimBlend;
public:
	cSoulEater_Breath();
	cSoulEater_Breath(cDragonSoulEater*);
	~cSoulEater_Breath();

	void handle() override;
};
