#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinEvade.h"

#include "jsonManager.h"

cPaladinEvade::cPaladinEvade(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
{
	m_nStateIndex = eAnimationSet::Roll;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
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
	}

	if (m_dAnimStartTime && pCurAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod)
		{
			m_pPaladin->StateFeedback();
		}
	}
}

