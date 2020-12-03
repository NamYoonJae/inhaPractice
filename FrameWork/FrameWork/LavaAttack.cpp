#include "stdafx.h"
#include "LavaAttack.h"
#include "SkinnedMesh.h"
#include "LavaGolem.h"
#include "TimerManager.h"
#pragma once
cLavaAttack::cLavaAttack(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)

{
}


cLavaAttack::~cLavaAttack()
{
}

void cLavaAttack::Handle()
{
	if (m_pGolem)
	{

		if (&m_pGolem->GetSkinnedMesh())
		{
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			double time = pCurAnimSet->GetPeriod() * 1000.0f;


			if ((GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
					> time - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
				&& m_pGolem->GetDist() <= 15.0f)
			{
				if (GetTickCount() - m_dwAnimStartTime > 1500.0f)
				{
					m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(1);
					m_dwAnimStartTime = GetTickCount();
				}
			}

			if (m_pGolem->GetDist() > 15.0f)
			{
				m_pGolem->Request(0);
				return;
			}
		}
		
	}


	
}
