#pragma once
#include "PaladinState.h"

class cPaladinEvade : public cPaladinState
{
public:
	cPaladinEvade(cPaladin*);
	~cPaladinEvade();

	void StateUpdate() override;
};

