#include "stdafx.h"
#include "LavaRun.h"
#include "LavaGolem.h"
#include "SkinnedMesh.h"
#include "TimerManager.h"
#pragma once
cLavaRun::cLavaRun(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
}


cLavaRun::~cLavaRun()
{
}

void cLavaRun::Handle()
{
	if (m_pGolem)
	{
		D3DXVECTOR3 vTarget		= *m_pGolem->GetTarget();
		D3DXVECTOR3 vCurrentDir = m_pGolem->GetDirection();
		D3DXVECTOR3 vPosition   = m_pGolem->GetPos();

		D3DXVECTOR3 vDirection = vTarget - vPosition;
		m_pGolem->SetDirection(vDirection);

		D3DXVECTOR2 vT = D3DXVECTOR2(vTarget.x, vTarget.z);
		D3DXVECTOR2 vP = D3DXVECTOR2(vPosition.x, vPosition.z);
		
		float RotY = acos(D3DXVec2Dot(&vT, &vP));
		D3DXVECTOR3 vRotation = m_pGolem->GetRotation();
		vRotation.y = RotY;
		//m_pGolem->SetRotation(vRotation);



		if (m_pGolem->GetDist() <= 10.0f)
		{
			m_pGolem->Request(2);
			return;
		}
		else
		{
			vPosition += vDirection * 0.01f;
			m_pGolem->SetPos(vPosition);
		}

		
		if(&m_pGolem->GetSkinnedMesh())
		{
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			if (GetTickCount() - m_dwAnimStartTime > pCurAnimSet->GetPeriod() * 1000.0f - m_dwBlendTime * 1000.0f)
			{
				m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(0);
				m_dwAnimStartTime = GetTickCount();

				pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
				m_pGolem->GetSkinnedMesh().Update((ST_BONE*)m_pGolem->GetSkinnedMesh().GetFrame(),
					&m_pGolem->GetSkinnedMesh().m_matWorldTM);
				m_pGolem->GetSkinnedMesh().UpdateSkinnedMesh(m_pGolem->GetSkinnedMesh().GetFrame());

			}
		}

	}
}
