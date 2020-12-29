#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "SoundManager.h"
#include "PaladinStun.h"

cPaladinStun::cPaladinStun(cPaladin* pPaladin, bool isHardStun)
	:cPaladinState(pPaladin)
	, m_dAnimStartTime(0)
	, m_IsComboAttack(false)
	, m_isHardStun(isHardStun)
{
	if(isHardStun) 
		m_nStateIndex = eAnimationSet::BodyHit;
	else 
		m_nStateIndex = eAnimationSet::HeadHit;
	
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
	m_pPaladin->SetStun(true);

	PlaySound();
	PlayVoice();
}

cPaladinStun::~cPaladinStun()
{
}

void cPaladinStun::StateUpdate()
{
	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	float fAnimPeriod;
	float fAnimBlendingTime = 0.3f;

	if (m_pPaladin->GetStateIndex() == eAnimationSet::BodyHit ||
		m_pPaladin->GetStateIndex() == eAnimationSet::HeadHit)
	{
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		fAnimPeriod = (pCurAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;
	}

	if (m_dAnimStartTime && pCurAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod)
		{
			m_pPaladin->SetStun(false);
			m_pPaladin->StateFeedback();
		}
	}
}

void cPaladinStun::PlayVoice()
{
	int Min(Paladin_Hit_Voice1), Max(Paladin_Hit_Voice4);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}

void cPaladinStun::PlaySound()
{
	int Min(Paladin_Hit1), Max(Paladin_Hit4);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}
