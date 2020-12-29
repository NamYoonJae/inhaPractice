#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinSpecialAttack.h"

#include "SoundManager.h"

cPaladinSpecialAttack::cPaladinSpecialAttack(cPaladin* pPaladin, int AnimIndex)
	:cPaladinState(pPaladin)
	, m_dAnimStartTime(0)
	, m_IsComboAttack(false)
{
	m_nStateIndex = AnimIndex;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();

	PlayVoice();
}

cPaladinSpecialAttack::~cPaladinSpecialAttack()
{
}

void cPaladinSpecialAttack::StateUpdate()
{
	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	float fAnimPeriod;
	float fAnimBlendingTime = 0.3f;

	if (m_pPaladin->GetStateIndex() == eAnimationSet::Kick)
	{
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		fAnimPeriod = (pCurAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;
	}
	else if (m_pPaladin->GetStateIndex() == eAnimationSet::Roar)
	{
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		fAnimPeriod = (pCurAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;

		// น๖วม
	}

	if (m_dAnimStartTime && pCurAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod)
		{
			m_pPaladin->StateFeedback();
		}
	}
}

void cPaladinSpecialAttack::PlayVoice()
{
	if (m_nStateIndex == eAnimationSet::Roar)
	{
		g_pSoundManager->PlaySFX((int)Paladin_SkyBizz_Voice);
	}
	else if (m_nStateIndex == eAnimationSet::Kick)
	{
		g_pSoundManager->PlaySFX((int)Paladin_Dragon_Voice);
	}
}
