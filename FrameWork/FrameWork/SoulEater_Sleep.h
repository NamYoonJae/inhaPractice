#pragma once
#include "SoulEaterState.h"
#include "DragonSoulEater.h"
class cSoulEater_Sleep :
	public cSoulEaterState
{
private:
	bool m_IsSleep;
	//int	 m_nliveGolem;

	float m_fDamagetaken;
	float m_fHealingAmount;

	DWORD	m_dwHealingCoolTime;
	DWORD	m_dwSleepSoundTime;
	DWORD	m_dwSleepSoundElapsed;

	// 수면 // 체력회복 패턴
	float	m_Sleep_Duration;

public:
	cSoulEater_Sleep();
	cSoulEater_Sleep(cDragonSoulEater*);
	~cSoulEater_Sleep();
	void handle() override;
	//void SubtractGolem() { m_nliveGolem--; };
};

