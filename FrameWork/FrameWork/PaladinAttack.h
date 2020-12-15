#pragma once
#include "PaladinState.h"

class cPaladinAttack : public cPaladinState
{
private:
	DWORD m_dAnimStartTime;
	int   m_nComboTimeLimit;
	bool  m_IsComboAttack;
public:
	cPaladinAttack(cPaladin* pPaladin);
	~cPaladinAttack();

	void StateUpdate() override;
	void ComboAttack();
};

