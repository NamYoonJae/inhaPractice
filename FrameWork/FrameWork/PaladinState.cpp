#include "stdafx.h"
#include "Paladin.h"
#include "PaladinState.h"


cPaladinState::cPaladinState(cPaladin* pPaladin)
	:m_pPaladin(pPaladin)
	,m_nStateIndex(eAnimationSet::Idle)
{
}


cPaladinState::~cPaladinState()
{
}
