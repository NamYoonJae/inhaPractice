#pragma once
#include "SoulEaterState.h"
class SoulEater_BasicAttack :
	public SoulEaterState
{
public:
	SoulEater_BasicAttack();
	~SoulEater_BasicAttack();
	void Update() override;
};

