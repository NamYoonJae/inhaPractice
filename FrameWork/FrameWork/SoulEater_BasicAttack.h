#pragma once
#include "SoulEaterState.h"
class cSoulEater_BasicAttack :
	public cSoulEaterState
{
private:
	bool m_IsAnimBlend;

	DWORD	m_dwSoundTime;
	bool m_IsRun;
public:
	cSoulEater_BasicAttack();
	cSoulEater_BasicAttack(cDragonSoulEater*);
	~cSoulEater_BasicAttack();
	void handle() override;
};

