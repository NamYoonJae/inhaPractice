#pragma once
#include "SoulEaterState.h"
#include "DragonSoulEater.h"
class cSoulEater_Sleep :
	public cSoulEaterState
{
private:
	bool m_IsSleep;
	int	 m_nliveGolem;

	float m_fDamagetaken;
	float m_fHealingAmount;

	DWORD	m_dwHealingCoolTime;
public:
	cSoulEater_Sleep();
	cSoulEater_Sleep(cDragonSoulEater*);
	~cSoulEater_Sleep();
	void handle() override;
	void SubtractGolem() { m_nliveGolem--; };
};

