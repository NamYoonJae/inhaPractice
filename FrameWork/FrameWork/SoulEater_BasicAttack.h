#pragma once
#include "SoulEaterState.h"
class cSoulEater_BasicAttack :
	public cSoulEaterState
{
public:
	cSoulEater_BasicAttack();
	cSoulEater_BasicAttack(cDragonSoulEater*);
	~cSoulEater_BasicAttack();
	void handle() override;
};

