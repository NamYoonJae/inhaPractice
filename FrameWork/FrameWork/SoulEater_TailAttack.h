#pragma once
#include "SoulEaterState.h"
class cSoulEater_TailAttack :
	public cSoulEaterState
{
private:
	bool  m_IsAnimBlend;
public:
	cSoulEater_TailAttack();
	cSoulEater_TailAttack(cDragonSoulEater*);
	~cSoulEater_TailAttack();
	void handle() override;
};

