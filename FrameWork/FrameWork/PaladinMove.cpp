#include "stdafx.h"
#include "SkinnedMesh.h"
#include "Paladin.h"
#include "PaladinMove.h"

cPaladinMove::cPaladinMove(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Walk;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
}

cPaladinMove::~cPaladinMove()
{
}

void cPaladinMove::StateUpdate()
{
}