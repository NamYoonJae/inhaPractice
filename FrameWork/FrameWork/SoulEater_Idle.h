#pragma once
#include "SoulEaterState.h"

class cSoulEater_Idle :
	public cSoulEaterState
{
protected:
	
private:
	bool  m_IsAnimBlend;
public:
	cSoulEater_Idle();
	cSoulEater_Idle(cDragonSoulEater*);
	~cSoulEater_Idle();
	void handle() override;
};

