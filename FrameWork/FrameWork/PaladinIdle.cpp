#include "stdafx.h"
#include "PaladinIdle.h"

cPaladinIdle::cPaladinIdle(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Idle;
}

cPaladinIdle::~cPaladinIdle()
{
}