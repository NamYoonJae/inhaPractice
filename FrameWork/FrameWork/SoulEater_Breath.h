#pragma once
#include "SoulEaterState.h"

class cSoulEater_Breath :
	public cSoulEaterState
{
private:
	DWORD m_dwStartTime;
	DWORD m_Breath_Duration;
	bool m_IsAnimBlend;
	D3DMATERIAL9 PrevMstl;
	// 브레스 // 패턴 4
//	float				m_Breath_Duration;
	float				m_Breath_Physic_Rate;
	float				m_Breath_Elemental_Rate;

public:
	cSoulEater_Breath();
	cSoulEater_Breath(cDragonSoulEater*);
	~cSoulEater_Breath();

	void handle() override;
};

