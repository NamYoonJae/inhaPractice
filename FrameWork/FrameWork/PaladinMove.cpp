#include "stdafx.h"
#include "PaladinMove.h"

cPaladinMove::cPaladinMove(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Walk;
}

cPaladinMove::~cPaladinMove()
{
}
