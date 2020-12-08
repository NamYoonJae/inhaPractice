#pragma once
#include "SoulEaterState.h"
class SoulEater_Idle :
	public cSoulEaterState
{
public:
	SoulEater_Idle();
	~SoulEater_Idle();
	void handle() override;
};

