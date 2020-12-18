#pragma once
#include "PaladinState.h"

class cPaladinEvade : public cPaladinState
{
private:
	DWORD m_dAnimStartTime;
public:
	cPaladinEvade(cPaladin*);
	~cPaladinEvade();

	void StateUpdate() override;
};

