#pragma once
#include "SoulEaterState.h"
class SoulEater_Idle :
	public SoulEaterState
{
public:
	SoulEater_Idle();
	~SoulEater_Idle();
	void Update() override;
};

