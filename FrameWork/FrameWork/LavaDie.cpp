#include "stdafx.h"
#include "LavaDie.h"

cLavaDie::cLavaDie(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
	m_nStateIndex = 3;
	IsDead = false;
}


cLavaDie::~cLavaDie()
{
}

void cLavaDie::Handle()
{
	if (&m_pGolem->GetSkinnedMesh())
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
				 > pCurAnimSet->GetPeriod() * 1000.0f - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			if (IsDead == false)
			{
				//m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(2);
				m_pGolem->GetSkinnedMesh().SetAnimationIndex(2);
				IsDead = true;
			}
			else
			{
				m_pGolem->Request(4);
				return;
			}
		}
	}

}
