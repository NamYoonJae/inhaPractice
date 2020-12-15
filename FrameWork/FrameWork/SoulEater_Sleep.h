#pragma once
#include "SoulEaterState.h"
#include "DragonSoulEater.h"
class cSoulEater_Sleep :
	public cSoulEaterState
{
private:
	bool m_IsSleep;
	int	 m_nliveGolem;
public:
	cSoulEater_Sleep();
	cSoulEater_Sleep(cDragonSoulEater*);
	~cSoulEater_Sleep();
	void handle() override;
	void SubtractGolem() { m_nliveGolem--; };
};

