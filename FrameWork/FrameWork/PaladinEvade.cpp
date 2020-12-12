#include "stdafx.h"
#include "PaladinEvade.h"

cPaladinEvade::cPaladinEvade(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Roll;
}

cPaladinEvade::~cPaladinEvade()
{
}
