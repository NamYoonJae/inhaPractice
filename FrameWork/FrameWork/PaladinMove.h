#pragma once
#include "PaladinState.h"

class cPaladinMove : public cPaladinState
{
private:
	DWORD m_dAnimStartTime;
public:
	cPaladinMove(cPaladin*);
	~cPaladinMove();

	void StateUpdate() override;
	void PlayFootstepSound();
};

