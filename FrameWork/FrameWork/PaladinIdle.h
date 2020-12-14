#pragma once
#include "PaladinState.h"

class cPaladinIdle : public cPaladinState
{
public:
	cPaladinIdle(cPaladin*);
	~cPaladinIdle();

	void StateUpdate() override;
};

