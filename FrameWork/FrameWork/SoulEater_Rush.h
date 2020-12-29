#pragma once
#include "SoulEaterState.h"
class cSoulEater_Rush :
	public cSoulEaterState
{
private:
	bool m_IsHitAnything;
	bool m_IsAnimBlend;

	DWORD m_dwPreparationTime;
	DWORD m_dwStateStartTime;

	float m_RushAttack_Physic_Rate;
	Synthesize(float, m_RushAttack_Elemental_Rate, ElementalDamage);

	Synthesize(bool, m_IsRush, Rush);
	//Synthesize(D3DXVECTOR3, m_vRushDir, Direction);	
	D3DXMATRIXA16 m_matRot;

public:
	cSoulEater_Rush();
	cSoulEater_Rush(cDragonSoulEater*);
	~cSoulEater_Rush();
	void handle();
	//D3DXMATRIXA16* GetMatRot() { return &m_matRot; }
};
