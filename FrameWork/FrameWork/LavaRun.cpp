#include "stdafx.h"
#include "LavaRun.h"
#include "LavaGolem.h"
#pragma once
cLavaRun::cLavaRun(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
	m_nStateIndex = 1;
}


cLavaRun::~cLavaRun()
{
}

void cLavaRun::Handle()
{
	if (m_pGolem)
	{
		D3DXVECTOR3 goal		 = *m_pGolem->GetTarget();
		D3DXVECTOR3 currentPos   = m_pGolem->GetPos();
		D3DXVECTOR3 vUp(0, 1, 0);
		D3DXVECTOR3 vDirection = (goal - currentPos);
		m_pGolem->SetDirection(vDirection);
		D3DXMATRIXA16 matR;
		
		if (m_pGolem->GetDist() <= 30.0f)
		{
			m_pGolem->Request(2);
			return;
		}
		else
		{
			currentPos += vDirection * 0.01f;
			m_pGolem->SetPos(currentPos);
		}

		
		if(&m_pGolem->GetSkinnedMesh())
		{
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			if (GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
				 > pCurAnimSet->GetPeriod() * 1000.0f - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
			{
				m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(0);
			}
		}

	}
}
