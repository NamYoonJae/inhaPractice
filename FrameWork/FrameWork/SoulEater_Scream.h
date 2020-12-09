#pragma once
#include "SoulEaterState.h"
class cSoulEater_Scream :
	public cSoulEaterState
{
private:
	bool m_IsAnimBlend;
public:
	cSoulEater_Scream();
	cSoulEater_Scream(cDragonSoulEater* pDragon);
	~cSoulEater_Scream();

	void handle() override;
};

