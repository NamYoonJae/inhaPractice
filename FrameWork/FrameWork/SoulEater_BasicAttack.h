#pragma once
#include "SoulEaterState.h"
class SoulEater_BasicAttack :
	public cSoulEaterState
{
public:
	SoulEater_BasicAttack();
	~SoulEater_BasicAttack();
	void handle() override;
};

