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
			double time = pCurAnimSet->GetPeriod() * 0.001;


			if ((GetTickCount() - m_dwAnimStartTime > time - m_dwBlendTime * 1000.0f)
				&& m_pGolem->GetDist() <= 15.0f)
			{
				m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(1);
				m_dwAnimStartTime = GetTickCount();

				pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
				m_pGolem->GetSkinnedMesh().Update((ST_BONE*)m_pGolem->GetSkinnedMesh().GetFrame(), 
					&m_pGolem->GetSkinnedMesh().m_matWorldTM);
				m_pGolem->GetSkinnedMesh().UpdateSkinnedMesh(m_pGolem->GetSkinnedMesh().GetFrame());
			}

			if (m_pGolem->GetDist() > 15.0f)
			{
				m_pGolem->Request(0);
				return;
			}
		}
		
	}


	
}
