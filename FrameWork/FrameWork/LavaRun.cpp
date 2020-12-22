#include "stdafx.h"
#include "LavaRun.h"
#include "LavaGolem.h"
#pragma once
cLavaRun::cLavaRun(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
	m_nStateIndex = 1;
	m_IsAnimBlend = false;

}


cLavaRun::~cLavaRun()
{
}

void cLavaRun::Handle()
{
	if (m_pGolem)
	{

		{
			D3DXVECTOR3 vPos = m_pGolem->GetPos();
			vPos += m_pGolem->GetDirection() * 0.3f;
			m_pGolem->SetPos(vPos);
		}

		if(&m_pGolem->GetSkinnedMesh() && m_IsAnimBlend == false)
		{
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			if (GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
				 > pCurAnimSet->GetPeriod() * 1000.0f - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
			{
				//m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(0);
				//m_pGolem->GetSkinnedMesh().SetAnimationIndex(0);

				//cSkinnedMesh& pCurrentMesh = m_pGolem->GetSkinnedMesh();
				cSkinnedMesh* pNextMesh = m_pGolem->GetRun();
				//pCurrentMesh = *pNextMesh;
				m_pGolem->SetSkinnedMesh(pNextMesh);
				m_IsAnimBlend = true;
			}
		}
		
		if (m_IsAnimBlend && m_pGolem->GetDist() < Distance)
		{
			m_pGolem->Request(2);
			return;
			
		}
	}
}
