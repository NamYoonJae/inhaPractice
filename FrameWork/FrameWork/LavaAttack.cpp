#include "stdafx.h"
#include "LavaAttack.h"
#pragma once



cLavaAttack::cLavaAttack(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
	m_nStateIndex = 2;
	m_IsAttack = false;
}


cLavaAttack::~cLavaAttack()
{
}

void cLavaAttack::Handle()
{
	if (m_pGolem)
	{

		if (&m_pGolem->GetSkinnedMesh() && m_IsAttack == false)
		{
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			double time = pCurAnimSet->GetPeriod() * 1000.0f;

			if ((GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
					> time - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
				&& m_pGolem->GetDist() <= Distance)
			{
				if (GetTickCount() - m_dwAnimStartTime > 1500.0f)
				{
					cSkinnedMesh* pNextMesh = m_pGolem->GetAttack();
					m_pGolem->SetSkinnedMesh(pNextMesh);
					m_dwAnimStartTime = GetTickCount();
					m_IsAttack = true;
					g_pSoundManager->PlaySFX(eSoundList::Golem_Attack);

					bool IsVoice = GenerateRandomNum(0,1000) >= 501 ? true : false;
					if(IsVoice)
					{
						g_pSoundManager->PlaySFX(eSoundList::Golem_AttackVoice1);
					}
					else if(!IsVoice)
					{
						g_pSoundManager->PlaySFX(eSoundList::Golem_AttackVoice2);
					}

					m_pGolem->SetIsAttack(true);
				}
			}

		}
		else if (m_IsAttack &&
			(GetTickCount() - m_dwAnimStartTime > 1500.0f))
		{
			m_pGolem->SetIsAttack(false);
			
			float fDist = m_pGolem->GetDist();

			if (fDist > Distance)
			{
				m_pGolem->Request(1);
				return;
			}
			else if (fDist < Distance)
			{
				m_pGolem->Request(2);
				return;
			}
		}
	}


	
}
