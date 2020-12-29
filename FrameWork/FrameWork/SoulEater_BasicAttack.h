#pragma once
#include "SoulEaterState.h"
class cSoulEater_BasicAttack :
	public cSoulEaterState
{
private:
	bool m_IsAnimBlend;

	DWORD	m_dwSoundTime;
	bool m_IsRun;
	Synthesize(float, TargetDistance, Distance);

	// 기본공격 // 패턴 1
	Synthesize(float, m_BasicAttack_Physic_Rate, PhysicsDamage);
	float				m_BasicAttack_Elemental_Rate;

public:
	cSoulEater_BasicAttack();
	cSoulEater_BasicAttack(cDragonSoulEater*);
	~cSoulEater_BasicAttack();
	void handle() override;
};

