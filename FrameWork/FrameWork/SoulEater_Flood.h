#pragma once
#include "SoulEaterState.h"
class cSoulEater_Flood :
	public cSoulEaterState
{
private:
	D3DXVECTOR3 m_vAttackTarget;

	DWORD m_dwCoolTime;

	int m_nCntSwamp;
	RECT MapRC;
	bool m_IsTrigger;
public:
	cSoulEater_Flood();
	cSoulEater_Flood(cDragonSoulEater*);
	~cSoulEater_Flood();
	void handle() override;
};

