#pragma once
#include "PaladinState.h"

class cPaladinStun : public cPaladinState
{
private:
	bool m_isHardStun;
	DWORD m_dAnimStartTime;
	int   m_nComboTimeLimit;
	bool  m_IsComboAttack;
public:
	cPaladinStun(cPaladin* pPaladin, bool isHardStun);
	~cPaladinStun();

	void StateUpdate() override;
	void PlayVoice();
	void PlaySound();
};

