#pragma once
#include "SoulEaterState.h"
class cSoulEater_BasicAttack :
	public cSoulEaterState
{
private:
	bool m_IsAnimBlend;
public:
	cSoulEater_BasicAttack();
	cSoulEater_BasicAttack(cDragonSoulEater*);
	~cSoulEater_BasicAttack();
	void handle() override;
};

