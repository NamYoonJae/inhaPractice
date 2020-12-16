#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinAttack.h"

cPaladinAttack::cPaladinAttack(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
	,m_dAnimStartTime(0)
	,m_nComboTimeLimit(1000)
	,m_IsComboAttack(false)
{
	m_nStateIndex = eAnimationSet::Attack1;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
}

cPaladinAttack::~cPaladinAttack()
{
}

void cPaladinAttack::StateUpdate()
{
	if (m_pPaladin == NULL) return;

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pPaladin->GetSkinnedMesh()->GetAnimationController();
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	float fAnimPeriod;
	float fAnimBlendingTime = 0.3f;

	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);

	if(m_IsComboAttack)
	{
		float _time = GetTickCount();
		float AnimStartTime = m_pPaladin->GetSkinnedMesh()->GetAnimStartTime();
		float PassedTime = m_pPaladin->GetSkinnedMesh()->GetPassedBlendTime() * 1000.0f;
		float CurAnimPeriod = pCurAnimSet->GetPeriod() * 1000.0f;

		_time -= AnimStartTime - PassedTime;

		if (_time >= CurAnimPeriod)
		{
			m_dAnimStartTime = GetTickCount();
			m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
			m_IsComboAttack = false;
		}
	}

	if (m_pPaladin->GetStateIndex() >= eAnimationSet::Attack3)
	{
		pAnimController->GetTrackAnimationSet(0, &pNextAnimSet);
		fAnimPeriod = (pNextAnimSet->GetPeriod() - fAnimBlendingTime) * 1000.0f;
	}

	if(m_dAnimStartTime && pNextAnimSet)
	{
		if (GetTickCount() - m_dAnimStartTime >= fAnimPeriod)
		{
			m_pPaladin->StateFeedback();
		}
	}
}

void cPaladinAttack::ComboAttack()
{
	//cout << GetTickCount() - m_dAnimStartTime << endl;
	if(GetTickCount() - m_dAnimStartTime <= m_nComboTimeLimit)
	{
		if (m_nStateIndex > eAnimationSet::Attack3 && !m_IsComboAttack)
		{
			m_nStateIndex--;
			m_IsComboAttack = true;
		}
		else if (m_nStateIndex == eAnimationSet::Attack3)
		{
			m_nStateIndex = eAnimationSet::Attack1;
			
		}
		
		//cout << m_nStateIndex << endl;
		
	}
}
