#pragma once

class cPaladin;

class cPaladinState
{
protected:
	cPaladin* m_pPaladin;
	Synthesize(int, m_nStateIndex, StateIndex);
public:
	cPaladinState(cPaladin*);
	virtual ~cPaladinState();

	virtual void StateUpdate() = 0;
	
	enum eAnimationSet
	{
		Die = 0,
		Walk,
		BodyHit,
		BigAttack,
		Run,
		Roll,
		Roar,
		Kick,
		SeeWatch,
		Idle,
		HeadHit,
		Casting,
		Attack3,
		Attack2,
		Attack1,
	};
};

