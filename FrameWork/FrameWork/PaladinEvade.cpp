#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinEvade.h"

cPaladinEvade::cPaladinEvade(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Roll;
	pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
}

cPaladinEvade::~cPaladinEvade()
{
}

void cPaladinEvade::StateUpdate()
{
}
