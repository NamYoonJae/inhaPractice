#include "stdafx.h"
#include "PaladinAttack.h"

cPaladinAttack::cPaladinAttack(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Attack1;
}

cPaladinAttack::~cPaladinAttack()
{
}
