#pragma once
#include "PaladinState.h"

class cPaladinSpecialAttack : public cPaladinState
{
private:
	DWORD m_dAnimStartTime;
	int   m_nComboTimeLimit;
	bool  m_IsComboAttack;
public:
	cPaladinSpecialAttack(cPaladin* pPaladin, int AnimIndex);
	~cPaladinSpecialAttack();

	void StateUpdate() override;
	void PlayVoice();
};

