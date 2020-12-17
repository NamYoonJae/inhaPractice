#include "stdafx.h"
#include "SoulEater_Scream.h"
#include "DragonSoulEater.h"

#define Radius 100

cSoulEater_Scream::cSoulEater_Scream()
	:cSoulEaterState()
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 4;
}

cSoulEater_Scream::cSoulEater_Scream(cDragonSoulEater * pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 4;
}


cSoulEater_Scream::~cSoulEater_Scream()
{
}

void cSoulEater_Scream::handle()
{
	if (m_pDragon == NULL) return;
	// 범위안에 있으면 모션블러 
	// 애니메이션이 끝나면 
	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
	}

	LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
	if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
		- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
	{
		if (m_IsAnimBlend == false)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::FireBall_Shot);
			m_IsAnimBlend = true;


			D3DXVECTOR3 pos = m_pDragon->GetPos();
			float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));
			//  
			m_dwElapsedTime = GetTickCount();
			//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "f", distance);
			if (distance <= Radius)
			{
				// 모션블러 
				//  3초 
			}

		}
		DWORD dwCurrentTime = GetTickCount();
		if (dwCurrentTime - m_dwElapsedTime >= 5000.0f
			&& m_pDragon->GetTarget()
			&& m_IsAnimBlend)
		{
			m_pDragon->Request();
			return;
		}
	}
}
