#include "stdafx.h"
#include "SkinnedMesh.h"
#include "Paladin.h"
#include "SoundManager.h"
#include "basic.h"

#include "PaladinMove.h"

cPaladinMove::cPaladinMove(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Run;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
}

cPaladinMove::~cPaladinMove()
{
}

void cPaladinMove::StateUpdate()
{
	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	float fAnimPeriod;
	float fAnimBlendingTime = 0.0f;

	if (m_pPaladin->GetStateIndex() == eAnimationSet::Run)
	{
		pAnimController->GetTrackAnimationSet(0, &pNextAnimSet);
		fAnimPeriod = (pNextAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;
	}

	if (m_dAnimStartTime && pNextAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod * 0.5f)
		{
			m_dAnimStartTime = GetTickCount();
			int Min(Paladin_Move1), Max(Paladin_Move8);
			g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
		}
	}
}