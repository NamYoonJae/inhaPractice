#pragma once
#include "SoulEaterState.h"
class cSoulEater_Rush :
	public cSoulEaterState
{
private:
	bool m_IsHitAnything;
	bool m_IsAnimBlend;
public:
	cSoulEater_Rush();
	cSoulEater_Rush(cDragonSoulEater*);
	~cSoulEater_Rush();
	void handle();
};

