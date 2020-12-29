#include "stdafx.h"
#include "Paladin.h"
#include "SkinnedMesh.h"
#include "PaladinAttack.h"

#include "jsonManager.h"
#include "SoundManager.h"

cPaladinAttack::cPaladinAttack(cPaladin* pPaladin)
	:cPaladinState(pPaladin)
	,m_dAnimStartTime(0)
	,m_IsComboAttack(false)
{
	JSON_Object* p_rootObject = g_p_jsonManager->get_json_object_Character();

	m_nComboTimeLimit = json_Function::object_get_double(p_rootObject, "Character/Attack/Combo time limit");

	m_nStateIndex = eAnimationSet::Attack1;
	m_pPaladin->GetSkinnedMesh()->SetAnimationIndexBlend(m_nStateIndex);
	m_dAnimStartTime = GetTickCount();
	PlaySound();
	PlayVoice();
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
			PlaySound();
			PlayVoice();
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
	if (m_pPaladin->GetStamina() <= 5) 
	{
		//m_pPaladin->SetStamina(0);
		return;
	};
	if(GetTickCount() - m_dAnimStartTime <= m_nComboTimeLimit)
	{
		if (m_nStateIndex > eAnimationSet::Attack3 && !m_IsComboAttack)
		{
			m_nStateIndex--;
			m_IsComboAttack = true;
			
			float stamina = m_pPaladin->GetStamina();
			if (stamina > 0)
			{
				stamina -= 50.0f;
				if (stamina < 0)
				{
					stamina = 0;
					m_pPaladin->SetStamina(stamina);
				}
				else
				{
					m_pPaladin->SetStamina(stamina);
				}

			}
			
		}
		else if (m_nStateIndex == eAnimationSet::Attack3)
		{
			m_nStateIndex = eAnimationSet::Attack1;
			
			float stamina = m_pPaladin->GetStamina();
			if (stamina > 0)
			{
				stamina -= 50.0f;
				if (stamina < 0)
				{
					stamina = 0;
					m_pPaladin->SetStamina(stamina);
				}
				else
				{
					m_pPaladin->SetStamina(stamina);
				}

			}
			
		}
		//cout << m_nStateIndex << endl;
	}
}

void cPaladinAttack::PlaySound()
{
	int Min(Paladin_Attack_Swing1), Max(Paladin_Attack_Swing3);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}

void cPaladinAttack::PlayVoice()
{
	int Min(Paladin_Attack_Voice1), Max(Paladin_Attack_Voice4);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}
