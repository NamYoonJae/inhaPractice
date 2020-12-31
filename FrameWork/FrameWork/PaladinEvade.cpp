#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinEvade.h"

#include "jsonManager.h"
#include "SoundManager.h"

cPaladinEvade::cPaladinEvade(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Roll;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
	PlaySound();
	PlayVoice();
}

cPaladinEvade::~cPaladinEvade()
{
}

void cPaladinEvade::StateUpdate()
{
	JSON_Object* p_Character_object = g_p_jsonManager->get_json_object_Character();

	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;

	float fAnimPeriod;
	float fAnimBlendingTime = 0.3f;

	if (m_pPaladin->GetStateIndex() == eAnimationSet::Roll)
	{
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		fAnimPeriod = (pCurAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;
		m_pPaladin->SetInvincible(true);
	}

	if (m_dAnimStartTime && pCurAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod)
		{
			m_pPaladin->SetInvincible(false);
			m_pPaladin->StateFeedback();
		}
	}
}

void cPaladinEvade::PlaySound()
{
	//int Min(Paladin_Attack_Swing1), Max(Paladin_Attack_Swing3);
	g_pSoundManager->PlaySFX((int)Paladin_Roll);
}

void cPaladinEvade::PlayVoice()
{
	//int Min(Paladin_Attack_Swing1), Max(Paladin_Attack_Swing3);
	g_pSoundManager->PlaySFX((int)Paladin_Roll_Voice);
}

