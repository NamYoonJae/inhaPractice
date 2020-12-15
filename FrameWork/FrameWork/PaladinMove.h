#pragma once
#include "PaladinState.h"

class cPaladinMove : public cPaladinState
{
public:
	cPaladinMove(cPaladin*);
	~cPaladinMove();

	void StateUpdate() override;
};

