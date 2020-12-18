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
	PlayFootstepSound();
}

cPaladinMove::~cPaladinMove()
{
}

void cPaladinMove::StateUpdate()
{
	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	float fFootstepDelay = 365.0f;

	if (m_dAnimStartTime && m_pPaladin->GetStateIndex() == eAnimationSet::Run)
	{
		DWORD dCurrentTime = GetTickCount();
		DWORD dElapsedTime = dCurrentTime - m_dAnimStartTime;

		if(dElapsedTime >= fFootstepDelay)
		{
			PlayFootstepSound();
			m_dAnimStartTime = dCurrentTime;
		}
	}
}

void cPaladinMove::PlayFootstepSound()
{
	int Min(Paladin_Move1), Max(Paladin_Move8);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}
