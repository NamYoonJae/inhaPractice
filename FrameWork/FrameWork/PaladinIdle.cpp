#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinIdle.h"

cPaladinIdle::cPaladinIdle(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Idle;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
}

cPaladinIdle::~cPaladinIdle()
{
}

void cPaladinIdle::StateUpdate()
{
}
