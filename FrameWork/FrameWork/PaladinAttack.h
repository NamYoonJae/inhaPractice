#pragma once
#include "PaladinState.h"

class cPaladinAttack : public cPaladinState
{
public:
	cPaladinAttack(cPaladin* pPaladin);
	~cPaladinAttack();

	void StateUpdate() override;
};

