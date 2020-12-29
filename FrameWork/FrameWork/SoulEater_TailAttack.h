#pragma once
#include "SoulEaterState.h"
class cSoulEater_TailAttack :
	public cSoulEaterState
{
private:
	bool  m_IsAnimBlend;
	bool  m_IsRun;
	// 꼬리치기 // 패턴 1
	Synthesize(float, m_TailAttack_Physic_Rate, PhysicsDamage);
	float				m_TailAttack_Elemental_Rate;

	Synthesize(float, TargetDistance, Distance);

public:
	cSoulEater_TailAttack();
	cSoulEater_TailAttack(cDragonSoulEater*);
	~cSoulEater_TailAttack();
	void handle() override;
};

